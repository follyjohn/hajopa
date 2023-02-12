#include "../include/HWorker.h"
#include "../include/Worker.h"
#include "../include/HMessage.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
using namespace std;

HWorker::HWorker() : Worker()
{
    this->current_task = HMessage();
}

HWorker::HWorker(WorkerStatus status, MessageBus *messageBus, string uid, string name, string intermediary_file)
    : Worker(status, messageBus, uid, name)
{
    this->current_task = HMessage();
    this->intermediary_file = intermediary_file;
}

HWorker::~HWorker()
{
}

void HWorker::run()
{

    //cout << "HWorker is running" << endl;
    this->outputFile = ofstream(this->intermediary_file);
    while (this->status != WorkerStatus::Finished)
    {
        // tous les appels de run_task sont fait dans le thread du broker
        if (this->current_task.get_content() != "")
        {
            //cout << "HWorker is running task: " << this->current_task.get_content() << endl;
            this->run_task(this->current_task.get_content());
            this->current_task = HMessage();
            // this->publish(new HMessage("task finished"), this->current_task.get_sender_channel());
            // this->notify();
            this->status = WorkerStatus::Stopped;
            //cout << "HWorker is stopped" << endl;
        }
    }
}


void HWorker::finish()
{
    this->status = WorkerStatus::Finished;
    this->outputFile.close();
    //cout << "HWorker is finished" << endl;
}

void HWorker::update(HMessage *message)
{
    this->status = WorkerStatus::Running;
    //cout << "HWorker: " << this->get_sub_name() << " received message: " << message->get_content() << endl;
    this->current_task = *message;
    // wait for new call from broker
}

void HWorker::run_task(string task)
{
    //cout << "HWorker " << this->get_sub_name() <<" starts running task" << endl;
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

                this->outputFile << sender << ": " << currentLine + "\n";
                fileReader >> currentLine;
            }
            if (currentLine[currentLine.length() - 1] != ',')
            {
                this->outputFile << sender << ": " << currentLine + "\n";
            }
        }
    }
    fileReader.close();
    //cout << "HWorker " << this->get_sub_name() << " finishes running task" << endl;
}
