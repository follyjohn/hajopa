#include "Channel.h"
#include "Message.h"
#include "Subscriber.h"
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#ifndef MESSAGE_BUS_H
#define MESSAGE_BUS_H
class MessageBus {

    public:
        MessageBus();
        MessageBus(string uid, string name);
        ~MessageBus();
        virtual string getName();
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
        mutex message_queu_mutex;
        condition_variable cv;
        bool ready = false;
};

#endif
