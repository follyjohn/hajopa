#include <iostream>
#include "../include/HMessage.h"
#include "../include/Channel.h"
#include "../include/Subscriber.h"
#include "../include/Issuer.h"
#include "../include/MessageBus.h"

using namespace std;

int main()
{
    MessageBus* messageBus = new MessageBus();
    Channel *johnChannel = new Channel("c-john", "John Inbox Channel");
    Channel *samantaChannel = new Channel("c-samanta", "Samanta Inbox Channel");
    messageBus->addChannel(samantaChannel);
    messageBus->addChannel(johnChannel);

    Issuer *is_samanta = new Issuer(messageBus, "is-samanta", "Samanta");
    Issuer *is_john = new Issuer(messageBus, "is-john", "Samanta");

    Subscriber *sub_samanta = new Subscriber("sub-samanta", "Samanta");
    Subscriber *sub_john = new Subscriber("sub-john", "John");
    messageBus->addSubscriber(sub_samanta);
    messageBus->addSubscriber(sub_john);

    sub_samanta->subscribe(samantaChannel);
    sub_john->subscribe(johnChannel);

    is_john->publish(new HMessage("123", "Hello World"), samantaChannel);
    is_john->notify();

    return 0;
}
