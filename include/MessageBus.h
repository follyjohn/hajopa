#include <iostream>
#include <queue>
#include <vector>
#include "Channel.h"
#include "Message.h"
#include "Subscriber.h"

#ifndef MESSAGE_BUS_H
#define MESSAGE_BUS_H
class MessageBus {

    public:
        MessageBus();
        ~MessageBus();
        virtual void addChannel(Channel* chanel);
        virtual void removeChannel(Channel* chanel);
        virtual void addSubscriber(Subscriber* subscriber);
        virtual void removeSubscriber(Subscriber* subscriber);
        virtual void onGetMessage(Message *message, Channel *chanel);
        virtual void onNotify();

    private:
        string uid;
        string name;
        vector<Subscriber*> subscribers;
        vector<Channel*> channels;
        queue<std::tuple<Channel*, Message*>> messagesQueue;
};

#endif
