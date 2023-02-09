#include "../include/HMessage.h"
#include "../include/Channel.h"
#include <iostream>

using namespace std;

HMessage::HMessage(string content, Channel *senderChannel)
{
    this->content = content;
    this->senderChannel = senderChannel;
}

HMessage::HMessage(string content)
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

HMessage::~HMessage()
{
}

string HMessage::get_content()
{
    return this->content;
}

Channel* HMessage::get_sender_channel()
{
    return this->senderChannel;
}

// https://stackoverflow.com/questions/266168/simple-example-of-threading-in-c
