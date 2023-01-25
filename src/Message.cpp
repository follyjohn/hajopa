#include "../include/Message.h"
#include <iostream>

using namespace std;


void Message::set_uid(string uid)
{
    this->uid = uid;
}

string Message::get_uid()
{
    return this->uid;
}

void Message::run_payload()
{
    cout << "Message::run_payload()" << endl;
}

Message::Message(string uid)
{
    this->uid = uid;
}

Message::Message()
{
}

Message::~Message()
{
}
