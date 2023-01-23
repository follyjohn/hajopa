#include "../include/Message.h"
#include <iostream>


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
