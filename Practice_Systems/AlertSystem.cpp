#include <bits/stdc++.h>
using namespace std;

struct AlertConfig{
    string id;
    string metricName;
    double threshhold;
    string comparator; // GT or LT
    string alertMessage;
};

// structure of metric data
struct MetricData{
string metricName;
double value;
long timestamp;
};

//AlertStore
class AlertStore{
private:
unordered_map<string,vector<AlertConfig>> alertMap;
public:
    void addAlert(AlertConfig& altcng){
        alertMap[altcng.metricName].push_back(altcng);
    }

    vector<AlertConfig> getAlertsForMetric(string& metricName){
        if(alertMap.find(metricName)!=alertMap.end()){
            return alertMap[metricName];
        }
        return {};
    }
};

// alertEvaluator 
class AlertEvaluator{
public:
static bool evaluate(const MetricData& metric,const AlertConfig& config){
    if(config.comparator == "GT"){
        return metric.value > config.threshhold;
    }
    else if(config.comparator == "LT"){
        return metric.value < config.threshhold;
    }
    else
    return false;
}
};

// alertDispatcher
class AlertDispatcher{
  public:
  static void dispatch(const AlertConfig& config, const MetricData& metric){
    cout<<" ALERT: "<<config.alertMessage<<" -METRIC: "<<config.metricName<<" Value: "<<metric.value<<endl;
  }  
};

// metric push service
class MetricPushService{
private:
AlertStore& alertStore;
public:
MetricPushService(AlertStore& store) : alertStore(store){}

void pushMetric(MetricData& data){
    auto alerts = alertStore.getAlertsForMetric(data.metricName);
    for(auto& alert: alerts){
        if(AlertEvaluator::evaluate(data,alert)){
            AlertDispatcher::dispatch(alert,data);
        }
    }
}
};

int main() {
    AlertStore store;
    AlertConfig config{"1", "CPU_Usage", 80.0, "GT", "CPU usage exceeded!"};
    store.addAlert(config);

    MetricPushService service(store);
    MetricData data{"CPU_Usage", 85.0, 1698600000};
    service.pushMetric(data);

    return 0;
}



// struct MetricEvent{
//     string metricName;
//     double value;
//     long timestamp;
// };

// class MetricService{
// public:
// void pusblishEvent(MetricEvent& event){
//     MessageQueue::publish("metric_topic",event);
// }
// };

// class AlertService{
//     // this service would listen and evaluate the event
// };