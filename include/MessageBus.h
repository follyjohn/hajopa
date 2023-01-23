#include "Chanel.h"
#include <iostream>
#include <queue>
#include <vector>

class MessageBus {

    public:
        MessageBus();
        ~MessageBus();
        virtual void addChanel(Chanel* chanel);
        virtual void removeChanel(Chanel* chanel);
        virtual void onGetMessage(Chanel* chanel, Message* message);

    private:
        string uid;
        string name;
        vector<Chanel*> chanels;
        std::queue<std::tuple<Chanel, Message>> messages;
};
