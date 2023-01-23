#include <iostream>
#include <vector>
#include "Message.h"
#include "MessageBus.h"
using namespace std;

#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

class Subscriber {
public:
    Subscriber(MessageBus* messageBus);
    Subscriber(MessageBus* messageBus, string uid, string name);
    Subscriber();
    ~Subscriber();
    virtual void update(Message* message);
    virtual void subscribe(Channel* chanel);
    virtual void unsubscribe(Channel* chanel);
    virtual void set_uid(string uid);
    virtual void set_name(string name);
    virtual string get_uid();
    virtual string get_name();

private:
    string uid;
    string name;
    MessageBus* messageBuses;
    vector<Channel*> chanels;
};

#endif
