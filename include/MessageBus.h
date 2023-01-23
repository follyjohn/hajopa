#include <iostream>
#include <queue>
#include <vector>

#ifndef MESSAGE_BUS_H
#define MESSAGE_BUS_H
class MessageBus {

    public:
        MessageBus();
        ~MessageBus();
        virtual void addChanel(Channel* chanel);
        virtual void removeChanel(Channel* chanel);
        virtual void addIssuer(Issuer* issuer);
        virtual void removeIssuer(Issuer* issuer);
        virtual void addSubscriber(Subscriber* subscriber);
        virtual void removeSubscriber(Subscriber* subscriber);
        virtual void onGetMessage(Channel* chanel, Message* message);
        virtual void onNotify();

    private:
        string uid;
        string name;
        vector<Issuer*> issuers;
        vector<Subscriber*> subscribers;
        vector<Channel*> chanels;
        queue<std::tuple<Channel*, Message*>> messagesQueue;
};

#endif
