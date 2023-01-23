#include "../include/Message.h"
#include <iostream>

#ifndef HMESSAGE_H
#define HMESSAGE_H

class HMessage :public Message
{
    public:
        HMessage();
        HMessage(string uid, string content);
        ~HMessage();
        virtual void run_payload();

    private:
        string content;
};

#endif
