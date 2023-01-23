#include "../include/Channel.h"
#include <iostream>

using namespace std;

Channel::Channel(string uid, string name)
{
    this->uid = uid;
    this->name = name;
}


Channel::Channel()
{
}

Channel::~Channel()
{
}

string Channel::get_uid()
{
    return this->uid;
}

void Channel::set_uid(string uid)
{
    this->uid = uid;
}

string Channel::get_name()
{
    return this->name;
}

void Channel::set_name(string name)
{
    this->name = name;
}
