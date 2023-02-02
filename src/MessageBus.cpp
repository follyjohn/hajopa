#include "../include/MessageBus.h"
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;
#include <condition_variable>
#include <mutex>
#include <thread>

MessageBus::MessageBus()
{
    this->channels = vector<Channel *>();
    this->subscribers = vector<Subscriber *>();
    this->messagesQueue = queue<std::tuple<Channel*, Message*>>();

}

MessageBus::MessageBus(string uid, string name)
{
    this->uid = uid;
    this->name = name;
    this->channels = vector<Channel *>();
    this->subscribers = vector<Subscriber *>();
    this->messagesQueue = queue<std::tuple<Channel*, Message*>>();
}

MessageBus::~MessageBus()
{
}

void MessageBus::addChannel(Channel *channel)
{
    this->channels.push_back(channel);
}


void MessageBus::addSubscriber(Subscriber *subscriber)
{
    this->subscribers.push_back(subscriber);
}

void MessageBus::removeChannel(Channel *channel)
{
    for (long unsigned int i = 0; i < this->channels.size(); i++)
    {
        if (this->channels[i] == channel) {
            this->channels.erase(this->channels.begin() + i);
        }
    }
}


void MessageBus::removeSubscriber(Subscriber *subscriber)
{
    for (long unsigned int i = 0; i < this->subscribers.size(); i++)
    {
        if (this->subscribers[i] == subscriber) {
            this->subscribers.erase(this->subscribers.begin() + i);
        }
    }
}

string MessageBus::getName()
{
    return this->name;
}

void MessageBus::onGetMessage(Message *message, Channel * channel)
{
    this->messagesQueue.push(make_tuple(channel, message));
}

void MessageBus::onNotify()
{
    while (!this->messagesQueue.empty()) {
        tuple<Channel*, Message*> message = this->messagesQueue.front();
        this->messagesQueue.pop();
        for (long unsigned int i = 0; i < this->subscribers.size(); i++)
        {
            for (long unsigned int j = 0; j < this->subscribers[i]->get_channels().size(); j++)
            {
                if (this->subscribers[i]->get_channels()[j] == std::get<0>(message)) {
                    this->subscribers[i]->update(std::get<1>(message));
                }
            }
        }
    }
}
