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
    void join_intermediary_files(vector<string> intermediry_files, string final_file);
    void test_genereate_interfile();
    int get_tasks_size();
    string get_task();
    void reduce_intermediary_file(string intermediry_file, string final_file);
};
#endif
