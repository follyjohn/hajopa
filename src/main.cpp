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
    Issuer *is_john = new Issuer(messageBus, "is-john", "Samanta")
    messageBus->addIssuer(is_john);
    messageBus->addIssuer(is_samanta);

    Subscriber *sub_samanta = new Subscriber(messageBus, "sub-samanta", "Samanta");
    Subscriber *sub_john = new Subscriber(messageBus, "sub-john", "John");
    messageBus->addSubscriber(sub_samanta);
    messageBus->addSubscriber(sub_john);

    sub_samanta->subscribe(samataChannel);
    sub_john->subscribe(johnChannel);

    is_john->publish(samataChannel, new HMessage("123", "Hello World"));
    is_john->notify();

    return 0;
}
