#include <iostream>
#ifndef MESSAGE_H
#define MESSAGE_H
using namespace std;
class Message
{

    public:
        Message(string uid);
        Message();
        ~Message();
        virtual void run_payload();
        virtual string get_uid();
        virtual void set_uid(string uid);

    protected:
        string uid;
};

#endif
