#include <iostream>
#include "../include/HMessage.h"

using namespace std;

int main()
{
    HMessage* w = new HMessage("123", "Hello World");
    w->run_payload();
    return 0;
}
