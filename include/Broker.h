#include "Issuer.h"
#include "Subscriber.h"
#include <iostream>

#ifndef BROKER_H
#define BROKER_H

using namespace std;


class Broker : public Issuer, public Subscriber
{
public:
    Broker();
    Broker(MessageBus *messageBus, string uid, string name);
    ~Broker();
    virtual void generate_tasks(string maildir) = 0;
    virtual int get_tasks_size() = 0;
    virtual string get_task() = 0;
};
#endif
