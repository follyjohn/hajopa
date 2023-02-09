#include <iostream>
#ifndef MESSAGE_H
#define MESSAGE_H
using namespace std;
class Message
{

    public:
        Message();
        ~Message();
        virtual void run_payload() = 0;
};

#endif
