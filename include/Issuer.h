#include <iostream>
#include <vector>
#include "HMessage.h"
#include "MessageBus.h"
#include "Channel.h"

#ifndef ISSUER_H
#define ISSUER_H
using namespace std;
class Issuer {

    public:
        Issuer();
        Issuer(MessageBus* messageBus);
        Issuer(MessageBus* messageBus, string uid, string name);
        ~Issuer();
        virtual void publish(HMessage* message, Channel* chanel);
        virtual void notify();
        virtual void set_uid(string uid);
        virtual void set_name(string name);
        virtual string get_uid();
        virtual string get_name();

    private:
        string uid;
        string name;
        MessageBus* messageBus;

};

#endif
