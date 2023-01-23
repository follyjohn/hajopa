#include <iostream>
#include "../include/Issuer.h"
using namespace std;

Issuer::Issuer(MessageBus* messageBus, string uid, string name)
{
    this->uid = uid;
    this->name = name;
    this->messageBus = messageBus;
}

Issuer::Issuer(MessageBus* messageBus)
{
    this->messageBus = messageBus;
}

Issuer::Issuer()
{
}

Issuer::~Issuer()
{
}

string Issuer::get_uid()
{
    return this->uid;
}

void Issuer::set_uid(string uid)
{
    this->uid = uid;
}


string Issuer::get_name()
{
    return this->name;
}

void Issuer::set_name(string name)
{
    this->name = name;
}

void Issuer::publish(Message* message, Channel* chanel)
{
    cout << "Issuer::notify()" << endl;
    this->messageBus->onGetMessage(message, chanel);
}

void Issuer::notify()
{
    cout << "Issuer::notify()" << endl;
    this->messageBus->notify();
}
