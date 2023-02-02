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
    this->channels.clear();
    this->subscribers.clear();
    while (!this->messagesQueue.empty()) {
        this->messagesQueue.pop();
    }
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
    std::unique_lock<std::mutex> lck(this->message_queu_mutex);
    this->ready = true;
    this->cv.wait(lck, [this] { return this->ready; });
    this->messagesQueue.push(make_tuple(channel, message));
    this->ready = false;
    lck.unlock();
    this->cv.notify_one();
}

void MessageBus::onNotify()
{
    std::unique_lock<std::mutex> lck(message_queu_mutex);
    this->ready = true;
    this->cv.wait(lck, [this] { return this->ready; });
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
    this->ready = false;
    lck.unlock();
    this->cv.notify_one();
}
