#include <iostream>
#include <vector>
#include "MessageBus.h"
#include "Message.h"
using namespace std;



class Issuer {

    public:
        Issuer(MessageBus* messageBus);
        ~Issuer();
        virtual void notify(MessageBus* messageBus, Message<string> message);

    private:
        string uid;
        string name;

};
