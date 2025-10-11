#include <bits/stdc++.h>
using namespace std;

// assets are stock, option, futures etc. They will have price, volatility and calculateRisk methods
class Asset{
    public:
    virtual double getPrice()=0;
    virtual double getVolatility(vector<double>prices={}) = 0;
    // virtual double calculateRisk()=0;
    virtual ~Asset(){}
};

class Stock: public Asset{
private:
double price, volatility;
double quantity;
public:
Stock(double price,double quantity, double volatility=11): price(price), quantity(quantity), volatility(volatility) {}

double getPrice() override{
    return price;
}

std::vector<double> calculateReturns(const std::vector<double>& prices) {
    std::vector<double> returns;
    for (size_t i = 1; i < prices.size(); ++i) {
        double ret = (prices[i] - prices[i - 1]) / prices[i - 1];
        returns.push_back(ret);
    }
    return returns;
}

// Function to calculate mean of a vector
double mean(const std::vector<double>& data) {
    double sum = 0.0;
    for (double val : data) {
        sum += val;
    }
    return sum / data.size();
}

// Function to calculate standard deviation
double standardDeviation(const std::vector<double>& data) {
    double avg = mean(data);
    double sumSquares = 0.0;
    for (double val : data) {
        sumSquares += (val - avg) * (val - avg);
    }
    return std::sqrt(sumSquares / data.size());
}
double getVolatility(vector<double> prices={}) override{ // annualized volatility
    if (prices.size() < 2) return 0.0; // Not enough data
    std::vector<double> returns = calculateReturns(prices);
    double dailyStdDev = standardDeviation(returns);
    double annualVol = dailyStdDev * std::sqrt(252);
    return annualVol;
}
};

class Option: public Asset{
private:
double price, volatility;
double quantity;
double delta, theta, vega, gamma;
double strikePrice; double mainAsset;
public:

Option(double price,double quantity,double strikePrice, double mainAsset){
    this->strikePrice = strikePrice;
    this->mainAsset = mainAsset;
    double percentValue = strikePrice/100;
    this->price = price;
    this->quantity = quantity;
    if(strikePrice >= mainAsset-2*percentValue && strikePrice <= mainAsset+2*percentValue){
        this->delta = 0.5;
        this->theta = 0.1;
        this->vega = 11;
    }
    else if(strikePrice <mainAsset - 2*percentValue){
        this->delta = 0.75;
        this->theta = 0.07;
        this->vega = 3;
    }
    else{
        this->delta = 0.3;
        this->theta = 0.3;
        this->vega = 3.5;
    }
}

double getPrice() override{
    return price;
}

vector<double> getGreeks(){
    vector<double> greeks={delta, theta, vega, gamma};
    return greeks;
}

double getVolatility(vector<double>prices) override{
    return vega;
}
};

class Future: public Asset{
private:
double price, volatility;
double quantity;
double leverage;
public:
Future(double price, double leverage, double quantity, double volatility=0) {
    this->price = price;
    this->quantity =quantity;
    this->leverage = leverage;
    this->volatility = volatility;
}

double getPrice() override{
    return price;
}

std::vector<double> calculateReturns(const std::vector<double>& prices) {
    std::vector<double> returns;
    for (size_t i = 1; i < prices.size(); ++i) {
        double ret = (prices[i] - prices[i - 1]) / prices[i - 1];
        returns.push_back(ret);
    }
    return returns;
}
// Function to calculate mean of a vector
double mean(const std::vector<double>& data) {
    double sum = 0.0;
    for (double val : data) {
        sum += val;
    }
    return sum / data.size();
}

// Function to calculate standard deviation
double standardDeviation(const std::vector<double>& data) {
    double avg = mean(data);
    double sumSquares = 0.0;
    for (double val : data) {
        sumSquares += (val - avg) * (val - avg);
    }
    return std::sqrt(sumSquares / data.size());
}
// Returns volatility as a decimal (e.g. 0.2 for 20%)
double getVolatility(vector<double> prices) override{
    if (prices.size() < 2) return 0.0; // Not enough data
    std::vector<double> returns = calculateReturns(prices);
    double dailyStdDev = standardDeviation(returns);
    double annualVol = dailyStdDev * std::sqrt(252);
    return annualVol;
}

double getLeverage(){
    return leverage;
}
};

class RiskEngine{
public:
virtual double calculateRisk(vector<Asset*>asset)=0;
virtual ~RiskEngine(){}
};

class VaRStrategy : public RiskEngine {
    private:
    double risk;
    public:
    VaRStrategy(double risk=0): risk(risk){}
    
    double calculateRisk(vector<Asset*> assets) override{
        risk=0;
        for (auto& a : assets) {
           double sigma = a->getVolatility();
           double value = a->getPrice();
           risk += 1.65 * sigma * value; // 95% Z-score
        }
        return risk;
    }
};

class CVaR: public RiskEngine{
private:
double risk;
public:
CVaR(double risk=0): risk(risk){}
 double calculateRisk(vector<Asset*> assets) override{
     for (auto& a : assets) {
           double sigma = a->getVolatility();
           double value = a->getPrice();
           risk += 1.65 * sigma * value; // 95% Z-score
        }
        return risk + 5 ;
    }

};

int main(){
    Asset* relianceStock = new Stock(2600, 10);
    vector<double>reliancePrices = {2500, 2600, 2550, 2700};
    cout<<" volatility of stock is "<<relianceStock->getVolatility(reliancePrices)<<endl;
    Asset* niftyFuture = new Future(35000, 7, 2);
    vector<Asset*> asset = {relianceStock, new Option(400, 75, 24900, 25000), niftyFuture};
    RiskEngine* re = new CVaR();
    double riskwaa = re->calculateRisk(asset);
    cout<<" portfolio risk is "<<riskwaa<<endl;
}