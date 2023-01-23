#include "../include/Subscriber.h"

#include <iostream>
using namespace std;

Subscriber::Subscriber()
{
}

Subscriber::Subscriber(string uid, string name);
{
    this->uid = uid;
    this->name = name;
    this->chanels = vector<Channel*>();
}

Subscriber::Subscriber()
{
    this->chanels = vector<Channel*>();
}



Subscriber::~Subscriber()
{
}

string Subscriber::get_uid()
{
    return this->uid;
}

void Subscriber::set_uid(string uid)
{
    this->uid = uid;
}

string Subscriber::get_name()
{
    return this->name;
}

void Subscriber::set_name(string name)
{
    this->name = name;
}

void Subscriber::subscribe(Channel *chanel)
{
    cout << "Subscriber: " << this->get_name() << " subscribed to Channel: " << chanel->get_name() << endl;
    this->chanels.push_back(chanel);
}

void Subscriber::unsubscribe(Channel* chanel)
{
    for (int i = 0; i < this->chanels.size(); i++) {
        if (this->chanels[i] == chanel) {
            this->chanels.erase(this->chanels.begin() + i);
        }
    }

    cout << "Subscriber: " << this->get_name() << " unsubscribed from Channel: " << chanel->get_name() << endl;
}


void Subscriber::update(Message* message)
{
    cout << "Subscriber: " << this->get_name() << " received message: " << message->get_uid() << endl;
    message->run_payload();
}

vector<Channel*> Subscriber::get_channels()
{
    return this->chanels;
}
