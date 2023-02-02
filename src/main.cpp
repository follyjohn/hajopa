#include "../include/Channel.h"
#include "../include/HMessage.h"
#include "../include/Issuer.h"
#include "../include/MessageBus.h"
#include "../include/Subscriber.h"
#include "../include/Worker.h"
#include <iostream>
#include <thread>


using namespace std;


void sayHello(Issuer *iss, Channel *chan){
    iss->publish(new HMessage("My first message from thread", "Hello everyone"), chan);
    iss->notify();
}


int main()
{
    MessageBus* messageBus = new MessageBus("mb-1", "Message Box");
    Channel *johnChannel = new Channel("c-john", "John Inbox Channel");
    Channel *samantaChannel = new Channel("c-samanta", "Samanta Inbox Channel");
    messageBus->addChannel(samantaChannel);
    messageBus->addChannel(johnChannel);

    Issuer *is_samanta = new Issuer(messageBus, "is-samanta", "Samanta");
    Issuer *is_john = new Issuer(messageBus, "is-john", "Samanta");

    Subscriber *sub_samanta = new Subscriber("sub-samanta", "Samanta");
    Subscriber *sub_john = new Subscriber("sub-john", "John");
    Subscriber *sub_tintin = new Subscriber("sub-tintin", "Tintin");

    Worker *worker = new Worker(WorkerStatus::Stopped, messageBus, "w-1", "Worker 1");

    messageBus->addSubscriber(sub_samanta);
    messageBus->addSubscriber(sub_john);
    messageBus->addSubscriber(sub_tintin);
    messageBus->addSubscriber(worker);

    sub_samanta->subscribe(samantaChannel);
    sub_john->subscribe(johnChannel);
    sub_tintin->subscribe(samantaChannel);
    worker->subscribe(samantaChannel);

    thread tone(sayHello, is_john, samantaChannel);
    thread ttwo(sayHello, is_samanta, johnChannel);
    thread tthree(sayHello, is_samanta, johnChannel);
    thread tfour(sayHello, is_samanta, johnChannel);
    thread tfive(sayHello, is_samanta, johnChannel);
    is_samanta->publish(new HMessage("My second message", "Hello John"), johnChannel);
    is_john->notify();
    worker->publish(new HMessage("Worker message", "Hello totto"), samantaChannel);
    worker->notify();
    tone.join();
    ttwo.join();
    tthree.join();
    tfour.join();
    tfive.join();
    // vector worjer = vector();

    // for(int i = 0; i < 10; i++)
    // {
    //     worjer.push_back(new Worker(WorkerStatus::Stopped, messageBus, "w-" + to_string(i), "Worker " + to_string(i)));
    // }

    // vecort worker = vector();

    // for (file in boo)
    // {
    //     select worker = worelr;
    //     dispater->pubish(new HMessage(runfunction, file, channnel))
    // }

    return 0;
}
