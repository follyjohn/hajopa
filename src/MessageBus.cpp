#include "Chanel.h"
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class MessageBus {

    public:
        MessageBus();
        ~MessageBus();
        virtual void addChanel(Chanel* chanel);
        virtual void removeChanel(Chanel* chanel);
        virtual void onGetMessage(Chanel* chanel, Message<string> message);

    private:
        string uid;
        string name;
        vector<Chanel*> chanels;
        std::queue<std::tuple<Chanel, Message<string>>> messages;
};
