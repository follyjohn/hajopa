#include "../include/Worker.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
using namespace std;

Worker::Worker(): Issuer(), Subscriber()
{
    this->current_task = HMessage();
    this->status = WorkerStatus::Unknown;
}

Worker::Worker(WorkerStatus status, MessageBus *messageBus, string uid, string name, string intermediary_file)
    : Issuer(messageBus, uid, name), Subscriber(uid, name)
{
    this->current_task = HMessage();
    this->intermediary_file = intermediary_file;
    this->status = status;

}

Worker::~Worker()
{
}

void Worker::run()
{

    //cout << "Worker is running" << endl;
    while (this->status != WorkerStatus::Finished)
    {
        // tous les appels de run_task sont fait dans le thread du broker
        if(this->current_task.get_content() != "")
        {
            //cout << "Worker is running task: " << this->current_task.get_content() << endl;
            this->run_task(this->current_task.get_content());
            this->current_task = HMessage();
            // this->publish(new HMessage("task finished"), this->current_task.get_sender_channel());
            // this->notify();
            this->status = WorkerStatus::Stopped;
            //cout << "Worker is stopped" << endl;
        }
    }
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

void Worker::update(HMessage *message)
{
    this->status = WorkerStatus::Running;
    //cout << "Worker: " << this->get_sub_name() << " received message: " << message->get_content() << endl;
    this->current_task = *message;
    // wait for new call from broker
}

void Worker::run_task(string task)
{
    //cout << "Worker " << this->get_sub_name() <<" starts running task" << endl;
    ofstream fileWriter(this->intermediary_file, ios::app);
    ifstream fileReader(task, ios::app);
    string s;
    string currentLine;
    string sender;
    // //cout << "Broker is processing n: " << i << " - "<< filename << endl;
    while (s != "X-From:")
    {
        fileReader >> s;
        if (s == "From:")
        {

            fileReader >> currentLine; // currentLine = sender
            sender = currentLine;
        }
        if (s == "Cc:" || s == "Bcc:" || s == "To:")
        {
            fileReader >> currentLine; // currentLine = receiver

            while (currentLine[currentLine.length() - 1] == ',')
            {
                currentLine.pop_back();

                fileWriter << sender << ": " << currentLine + "\n";
                fileReader >> currentLine;
            }
            if (currentLine[currentLine.length() - 1] != ',')
            {
                fileWriter << sender << ": " << currentLine + "\n";
            }
        }
    }
    fileReader.close();
    fileWriter.close();
    //cout << "Worker " << this->get_sub_name() << " finishes running task" << endl;
}
