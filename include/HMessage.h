#include "../include/Message.h"
#include "../include/Channel.h"
#include <iostream>

#ifndef HMESSAGE_H
#define HMESSAGE_H

class HMessage :virtual public Message
{
    public:
        HMessage();
        HMessage(string uid, string content);
        HMessage(string uid, string content, Channel *senderChannel);
        ~HMessage();
        virtual void run_payload();

    private:
        string content;
        Channel *senderChannel;
};

#endif
