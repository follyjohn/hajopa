#include "Issuer.h"
#include "Subscriber.h"
#include "Broker.h"
#include <iostream>
#include <string>

#ifndef HBROKER_H
#define HBROKER_H

using namespace std;


class HBroker : public Broker
{

private:
    vector<string> tasks;
public:
    HBroker();
    HBroker(MessageBus *messageBus, string uid, string name);
    ~HBroker();
    void generate_tasks(string maildir);
    void join_intermediary_files(vector<string> intermediary_files, string final_file);
    int get_tasks_size();
    string get_task();
};
#endif
