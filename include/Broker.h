#include "Issuer.h"
#include "Subscriber.h"
#include <iostream>

#ifndef BROKER_H
#define BROKER_H

using namespace std;


class Broker : public Issuer, public Subscriber
{

private:
    vector<string> tasks;

public:
    Broker();
    Broker(MessageBus *messageBus, string uid, string name);
    ~Broker();
    void generate_tasks(string maildir);
    void test_genereate_interfile();
    void reduce_intermediary_file(vector<string> intermediry_files, string final_file);
};
#endif
