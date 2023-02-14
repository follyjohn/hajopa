#include "../include/Broker.h"
#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

using namespace std;

Broker::Broker()
{
}

Broker::Broker(MessageBus *messageBus, string uid, string name) : Issuer(messageBus, uid, name), Subscriber(uid, name)
{
}

Broker::~Broker()
{
}
