#include "../include/MessageBus.h"

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

MessageBus::MessageBus()
{
    this->channels = vector<Channel *>();
    this->issuers = vector<Issuer *>();
    this->subscribers = vector<Subscriber *>();
    this->messagesQueue = queue<std::tuple<Channel*, Message*>>();
}

MessageBus::~MessageBus()
{
}

void MessageBus::add_channel(Channel *channel)
{
    this->channels.push_back(channel);
}

void MessageBus::add_issuer(Issuer *issuer)
{
    this->issuers.push_back(issuer);
}

void MessageBus::add_subscriber(Subscriber *subscriber)
{
    this->subscribers.push_back(subscriber);
}

void MessageBus::remove_channel(Channel *channel)
{
    for (int i = 0; i < this->channels.size(); i++) {
        if (this->channels[i] == channel) {
            this->channels.erase(this->channels.begin() + i);
        }
    }
}

void MessageBus::remove_issuer(Issuer *issuer)
{
    for (int i = 0; i < this->issuers.size(); i++) {
        if (this->issuers[i] == issuer) {
            this->issuers.erase(this->issuers.begin() + i);
        }
    }
}

void MessageBus::remove_subscriber(Subscriber *subscriber)
{
    for (int i = 0; i < this->subscribers.size(); i++) {
        if (this->subscribers[i] == subscriber) {
            this->subscribers.erase(this->subscribers.begin() + i);
        }
    }
}

void MessageBus::onGetMessage(Channel *channel, Message *message)
{
    this->messagesQueue.push(std::make_tuple(channel, message));
}

void MessageBus::onNotify()
{
    while (!this->messagesQueue.empty()) {
        std::tuple<Channel*, Message*> message = this->messagesQueue.front();
        this->messagesQueue.pop();
        for (int i = 0; i < this->subscribers.size(); i++) {
            for (int j = 0; j < this->subscribers[i]->get_channels().size(); j++) {
                if (this->subscribers[i]->get_channels()[j] == std::get<0>(message)) {
                    this->subscribers[i]->update(std::get<1>(message));
                }
            }
        }
    }
}
