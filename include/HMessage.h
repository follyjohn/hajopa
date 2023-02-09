#include "../include/Message.h"
#include "../include/Channel.h"
#include <iostream>

#ifndef HMESSAGE_H
#define HMESSAGE_H

class HMessage
{
    public:
        HMessage();
        HMessage(string content, Channel *senderChannel);
        HMessage(string content);
        ~HMessage();
        virtual void run_payload();
        virtual string get_content();
        virtual Channel* get_sender_channel();

    private:
        string content;
        Channel *senderChannel;
};

#endif
