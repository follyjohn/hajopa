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

    this->outputFile = ofstream(this->intermediary_file);
    while (this->status != WorkerStatus::Finished)
    {
        // tous les appels de run_task sont fait dans le thread du broker
        if (this->current_task.get_content() != "")
        {
            //cout << "HWorker is running task: " << this->current_task.get_content() << endl;
            this->run_task(this->current_task.get_content());
            this->current_task = HMessage();
            this->status = WorkerStatus::Stopped;
            // this->publish(new HMessage("finished", this->get_primmary_channel()), this->current_task.get_sender_channel());
            // this->notify();
        }
    }
}


void HWorker::finish()
{
    this->status = WorkerStatus::Finished;
    this->outputFile.close();
    cout << this->get_sub_name() << " finished" << endl;
}

void HWorker::update(HMessage *message)
{
    this->status = WorkerStatus::Running;
    this->current_task = *message;
}

void HWorker::run_task(string task)
{
    ifstream fileReader(task, ios::app);
    string s;
    string currentLine;
    string sender;
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
}
