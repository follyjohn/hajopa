#ifndef CHANNEL_H
#define CHANNEL_H

using namespace std;

class Channel {

    public:
        Channel();
        Channel(string uid, string name);
        ~Channel();
        virtual string get_uid();
        virtual string get_name();
        virtual void set_uid(string uid);
        virtual void set_name(string name);

    private:
        string uid;
        string name;
};

#endif
