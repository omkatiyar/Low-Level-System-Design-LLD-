#include <bits/stdc++.h>
#include <fstream>
using namespace std;

// ===== Abstract Base Class =====
class DocumentElement {
public:
    virtual void render() = 0;
    virtual string toString() = 0;
    virtual ~DocumentElement() {}
};

// ===== Concrete Classes =====
class TextElement : public DocumentElement {
private:
    string text;
public:
    TextElement(string tex) : text(tex) {}
    void render() override {
        cout << text << endl;
    }
    string toString() override {
        return "Text: " + text;
    }
};

class ImgElement : public DocumentElement {
private:
    string path;
public:
    ImgElement(string path) : path(path) {}
    void render() override {
        cout << "The path of image is " << path << endl;
    }
    string toString() override {
        return "Image: " + path;
    }
};

// ===== Document Class =====
class Document {
private:
    vector<DocumentElement*> elements;
public:
    void addElement(DocumentElement* de) {
        elements.push_back(de);
    }

    const vector<DocumentElement*>& getElements() const {
        return elements;
    }

    string render() {
        cout << "Rendering the Document now:" << endl;
        string s = "";
        for (auto el : elements) {
            s += el->toString() + "\n";
            el->render();
        }
        cout << "Done." << endl;
        return s;
    }

    ~Document() {
        for (auto el : elements) delete el;
    }
};

// ===== Abstract Persistence =====
class Persistence {
public:
    virtual void save(Document* doc, const string& filename) = 0;
    virtual ~Persistence() {}
};

// ===== FileSave Class =====
class FileSave : public Persistence {
public:
    void save(Document* doc, const string& filename) override {
        ofstream outfile(filename);
        if (!outfile.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        for (auto el : doc->getElements()) {
            outfile << el->toString() << endl;
        }

        outfile.close();
        cout << "Document saved to " << filename << endl;
    }
};

// ===== DocEditor Class =====
class DocEditor {
private:
    Document doc;
    FileSave db; // concrete object instead of abstract
    string rendered_string;

public:
    void addText(string text) {
        doc.addElement(new TextElement(text));
    }

    void addImg(string path) {
        doc.addElement(new ImgElement(path));
    }

    void render() {
        rendered_string = doc.render();
    }

    void save(const string& filename) {
        db.save(&doc, filename);
    }
};

// ===== Main Function =====
int main() {
    DocEditor editor;
    editor.addText("Hello GPT!");
    editor.addImg("img/cat.png");
    editor.addText(" New line added to the text file");
    editor.addImg("Downloads/parasf.jpg");
    editor.addImg("Downloads/Om.jpg");
    editor.render();
    editor.save("final_doc.txt");

    return 0;
}
