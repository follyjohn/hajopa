#include <iostream>
#include <vector>
#include "Message.h"
#include "Channel.h"
using namespace std;

#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

class Subscriber {

    public:
        Subscriber();
        Subscriber(string uid, string name);
        ~Subscriber();
        virtual void update(Message* message);
        virtual void subscribe(Channel* chanel);
        virtual void unsubscribe(Channel* chanel);
        virtual vector<Channel*> get_channels();
        virtual void set_uid(string uid);
        virtual void set_name(string name);
        virtual string get_uid();
        virtual string get_name();

    private:
        string uid;
        string name;
        vector<Channel*> channels;
};

#endif
