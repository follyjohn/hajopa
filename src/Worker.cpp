#include <iostream>
#include "../include/Worker.h"
using namespace std;

Worker::Worker()
{
    this->status = WorkerStatus::Unknown;
}

Worker::Worker(WorkerStatus status, MessageBus * messageBus, string uid, string name) : Issuer(messageBus, uid, name), Subscriber( uid, name)
{
    this->status = status;
}

Worker::~Worker()
{
}

void Worker::run()
{
    this->status = WorkerStatus::Running;
    cout << "Worker is running" << endl;

}

void Worker::stop()
{
    this->status = WorkerStatus::Stopped;
    cout << "Worker is stopped" << endl;
}


void Worker::pause()
{
    this->status = WorkerStatus::Paused;
    cout << "Worker is paused" << endl;
}

void Worker::resume()
{
    this->status = WorkerStatus::Running;
    cout << "Worker is resumed" << endl;
}

WorkerStatus Worker::get_status()
{
    return this->status;
}

void Worker::set_status(WorkerStatus status)
{
    this->status = status;
}
