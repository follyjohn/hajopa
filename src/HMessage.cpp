#include "../include/HMessage.h"
#include <iostream>

using namespace std;
HMessage::HMessage(string uid, string content) : Message(uid)
{
    this->content = content;
}


void HMessage::run_payload()
{
    cout << "Running: payload -> " << this->content << endl;
}


HMessage::HMessage()
{
}

// https: //stackoverflow.com/questions/266168/simple-example-of-threading-in-c
