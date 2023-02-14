#include "../include/Worker.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>
using namespace std;

Worker::Worker(): Issuer(), Subscriber()
{
    this->status = WorkerStatus::Unknown;
}

Worker::Worker(WorkerStatus status, MessageBus *messageBus, string uid, string name)
    : Issuer(messageBus, uid, name), Subscriber(uid, name)
{
    this->status = status;
}

Worker::~Worker()
{
}


void Worker::stop()
{
    this->status = WorkerStatus::Stopped;
}


void Worker::pause()
{
    this->status = WorkerStatus::Paused;
}

void Worker::resume()
{
    this->status = WorkerStatus::Running;
}

WorkerStatus Worker::get_status()
{
    return this->status;
}

void Worker::set_status(WorkerStatus status)
{
    this->status = status;
}

void Worker::finish()
{
    this->status = WorkerStatus::Finished;
    cout << this->get_sub_name() << " finished" << endl;
}
