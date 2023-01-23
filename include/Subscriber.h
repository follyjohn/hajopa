#include "Message.h"
#include "MessageBus.h"
#include <iostream>
#include <vector>
using namespace std;

class Subscriber {
public:
    Subscriber(MessageBus* messageBus);
    ~Subscriber();
    virtual void onNotify(Message<string> message);
    virtual void subscribe(Chanel* chanel);
    virtual void unsubscribe(Chanel *chanel);

private:
    string uid;
    string name;
    MessageBus* messageBuses;
    vector<Chanel*> chanels;
};
