#include "../include/Subscriber.h"

#include <iostream>
#include <thread>
using namespace std;



Subscriber::Subscriber()
{
    this->channels = vector<Channel*>();
    // start a new thread for this subscriber
    // this->thread = new thread();

}

Subscriber::Subscriber(string uid, string name)
{
    this->uid = uid;
    this->name = name;
    this->channels = vector<Channel*>();
}


Subscriber::~Subscriber()
{
}

string Subscriber::get_sub_uid()
{
    return this->uid;
}

void Subscriber::set_uid(string uid)
{
    this->uid = uid;
}

string Subscriber::get_sub_name()
{
    return this->name;
}

void Subscriber::set_name(string name)
{
    this->name = name;
}

void Subscriber::subscribe(Channel *chanel)
{
    cout << "Subscriber: " << this->get_sub_name() << " subscribed to Channel: " << chanel->get_name() << endl;
    this->channels.push_back(chanel);
}

void Subscriber::unsubscribe(Channel* chanel)
{
    for (long unsigned int i = 0; i < this->channels.size(); i++)
    {
        if (this->channels[i] == chanel) {
            this->channels.erase(this->channels.begin() + i);
        }
    }

    cout << "Subscriber: " << this->get_sub_name() << " unsubscribed from Channel: " << chanel->get_name() << endl;
}


void Subscriber::update(HMessage* message)
{
    cout << "Subscriber: " << this->get_sub_name() << " received message: " << message->get_content() << endl;
}

vector<Channel*> Subscriber::get_channels()
{
    return this->channels;
}
