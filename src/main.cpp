#include <iostream>
#include "../include/HMessage.h"
#include "../include/Channel.h"
#include "../include/Subscriber.h"
#include "../include/Issuer.h"
#include "../include/MessageBus.h"

using namespace std;

int main()
{
    HMessage* w = new HMessage("123", "Hello World");
    w->run_payload();
    Channel* c = new Channel("123", "My Channel");
    Subscriber* s = new Subscriber("123", "My Subscriber");
    Issuer* i = new Issuer("123", "My Issuer")
    s->subscribe(c);
    return 0;
}
