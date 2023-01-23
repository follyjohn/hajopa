#include "../include/HMessage.h"
#include <iostream>

using namespace std;
HMessage::HMessage(string uid, string content) : Message(uid)
{
    this->content = content;
}


void HMessage::run_payload()
{
    cout << "HMessage::run_payload " << this->content << endl;
}


HMessage::HMessage()
{
}
