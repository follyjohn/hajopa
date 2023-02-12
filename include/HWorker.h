#include "Issuer.h"
#include "Worker.h"
#include "Subscriber.h"
#include "MessageBus.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

#ifndef HWORKER_H
#define HWORKER_H

using namespace std;

class HWorker: public Worker
{

private:
    string intermediary_file;
    HMessage current_task;
    ofstream outputFile;

public:
    HWorker();
    HWorker(WorkerStatus status, MessageBus *messageBus, string uid, string name, string intermediary_file);
    ~HWorker();
    void run();
    void finish();
    void update(HMessage* message);
    void run_task(string task);
    void join_intermediary_files(vector<string> intermediary_files, string final_file);
};

#endif
