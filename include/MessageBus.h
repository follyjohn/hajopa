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
        virtual void onGetMessage(Channel* chanel, Message* message);

    private:
        string uid;
        string name;
        vector<Channel*> chanels;
        std::queue<std::tuple<Channel, Message>> messages;
};

#endif
