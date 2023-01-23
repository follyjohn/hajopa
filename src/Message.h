#include <iostream>

using namespace std;

template <typename PAYLOAD>
class Message
{

public:
    virtual void print();

private:
    PAYLOAD payload;
    string uid;
};
