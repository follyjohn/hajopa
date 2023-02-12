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
    //cout << "Worker is stopped" << endl;
}


void Worker::pause()
{
    this->status = WorkerStatus::Paused;
    //cout << "Worker is paused" << endl;
}

void Worker::resume()
{
    this->status = WorkerStatus::Running;
    //cout << "Worker is resumed" << endl;
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
    //cout << "Worker is finished" << endl;
}
