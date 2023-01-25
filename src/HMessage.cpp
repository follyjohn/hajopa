#include "../include/HMessage.h"
#include "../include/Channel.h"
#include <iostream>

using namespace std;
HMessage::HMessage(string uid, string content) : Message(uid)
{
    this->content = content;
    this->senderChannel = NULL;
}

HMessage::HMessage(string uid, string content, Channel *senderChannel) : Message(uid)
{
    this->content = content;
    this->senderChannel = senderChannel;
}


void HMessage::run_payload()
{
    cout << "Running: payload -> " << this->content << endl;
    if(this->senderChannel != NULL)
    {

    }

}


HMessage::HMessage()
{
}

// https: //stackoverflow.com/questions/266168/simple-example-of-threading-in-c
