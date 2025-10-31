#include <bits/stdc++.h>
using namespace std;

// ===============================
// 1️⃣ File Operation Abstraction
// ===============================
class IFileManager {
public:
    virtual void upload(const string& name, int size) = 0;
    virtual void download(const string& name) = 0;
    virtual void deleteFile(const string& name) = 0;
    virtual void listFiles() const = 0;
    virtual ~IFileManager() {}
};

// ===============================
// 2️⃣ Authentication Abstraction
// ===============================
class IAuthProvider {
public:
    virtual void setToken(const string& token) = 0;
    virtual string getToken() const = 0;
    virtual bool authenticate(const string& token) = 0;
    virtual string getSDKVersion() const = 0;
    virtual ~IAuthProvider() {}
};

// ===============================
// 3️⃣ Concrete File Manager (SRP)
// ===============================
class LocalFileManager : public IFileManager {
    unordered_map<string, int> files;
public:
    void upload(const string& name, int size) override {
        if (files.find(name) == files.end())
            cout << "📤 Uploading new file: " << name << " (" << size << "MB)\n";
        else
            cout << "✏️  Updating existing file: " << name << " (" << size << "MB)\n";
        files[name] = size;
    }

    void download(const string& name) override {
        auto it = files.find(name);
        if (it != files.end())
            cout << "📥 Downloaded " << name << " (" << it->second << "MB)\n";
        else
            cout << "❌ File not found: " << name << "\n";
    }

    void deleteFile(const string& name) override {
        if (files.erase(name))
            cout << "🗑️  Deleted file: " << name << "\n";
        else
            cout << "❌ File not found: " << name << "\n";
    }

    void listFiles() const override {
        cout << "\n📂 Current Files:\n";
        if (files.empty()) cout << "(no files)\n";
        for (const auto& f : files)
            cout << " - " << f.first << " (" << f.second << "MB)\n";
    }
};

// ===============================
// 4️⃣ Concrete Authentication Providers (OCP)
// ===============================
class AWSAuthProvider : public IAuthProvider {
    string token;
public:
    AWSAuthProvider(const string& t = "") : token(t) {}

    void setToken(const string& t) override { token = t; }
    string getToken() const override { return token; }
    bool authenticate(const string& t) override {
        bool success = (t == token);
        cout << (success ? "✅ AWS Auth Success\n" : "❌ AWS Auth Failed\n");
        return success;
    }
    string getSDKVersion() const override { return "AWS SDK v3.2.1"; }
};

class GDriveAuthProvider : public IAuthProvider {
    string token;
public:
    GDriveAuthProvider(const string& t = "") : token(t) {}

    void setToken(const string& t) override { token = t; }
    string getToken() const override { return token; }
    bool authenticate(const string& t) override {
        bool success = (t == token);
        cout << (success ? "✅ GDrive Auth Success\n" : "❌ GDrive Auth Failed\n");
        return success;
    }
    string getSDKVersion() const override { return "Google Drive SDK v2.5"; }
};

// ===============================
// 5️⃣ Cloud Storage: Composition (DIP, LSP, ISP)
// ===============================
class CloudStorage {
    unique_ptr<IFileManager> fileMgr;
    unique_ptr<IAuthProvider> authProvider;
public:
    CloudStorage(IFileManager* fm, IAuthProvider* ap)
        : fileMgr(fm), authProvider(ap) {}

    void uploadFile(const string& name, int size) {
        if (authProvider->authenticate(authProvider->getToken()))
            fileMgr->upload(name, size);
    }

    void downloadFile(const string& name) {
        if (authProvider->authenticate(authProvider->getToken()))
            fileMgr->download(name);
    }

    void listFiles() const { fileMgr->listFiles(); }

    void setToken(const string& t) { authProvider->setToken(t); }
    string getToken() const { return authProvider->getToken(); }
    string getSDKVersion() const { return authProvider->getSDKVersion(); }
};

// ===============================
// 6️⃣ Factory (OCP + DIP)
// ===============================
class CloudFactory {
public:
    static CloudStorage* getCloud(const string& type) {
        static unordered_map<string, function<CloudStorage*()>> registry = {
            {"AWS", []() {
                return new CloudStorage(new LocalFileManager(),
                                        new AWSAuthProvider("aws-token-123"));
            }},
            {"GDrive", []() {
                return new CloudStorage(new LocalFileManager(),
                                        new GDriveAuthProvider("gdrive-token-789"));
            }}
        };

        auto it = registry.find(type);
        if (it != registry.end()) return it->second();
        cout << "⚠️ Unknown cloud provider, defaulting to AWS.\n";
        return registry["AWS"]();
    }
};

// ===============================
// 7️⃣ Demo
// ===============================
int main() {
    unique_ptr<CloudStorage> cloud(CloudFactory::getCloud("GDrive"));

    cout << "🔑 Current SDK: " << cloud->getSDKVersion() << "\n";
    cloud->setToken("gdrive-token-789");

    cloud->uploadFile("Report.pdf", 5);
    cloud->uploadFile("Photo.png", 2);
    cloud->downloadFile("Report.pdf");
    cloud->listFiles();
}
