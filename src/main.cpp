#include "../include/Channel.h"
#include "../include/HMessage.h"
#include "../include/Issuer.h"
#include "../include/MessageBus.h"
#include "../include/Subscriber.h"
#include "../include/Worker.h"
#include "../include/Broker.h"
#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include "./utils.cpp"


using namespace std;


int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        cout << "Invalid number of arguments" << endl;
        cout << "Usage: ./hajopa <number of threads> <mails directory path>" << endl;
        return 1;
    }
    time_t start, end;
    time(&start);

    MessageBus *messageBus = new MessageBus("mb-1", "Message Box");

    int number_of_threads = atoi(argv[1]);
    string maildir = argv[2];

    Broker *broker = new Broker(messageBus , "broker-1", "Broker 1");
    Channel *bkchannel = new Channel("c-bk", "Broker Inbox Channel");
    messageBus->addSubscriber(broker);
    broker->subscribe(bkchannel);

    broker->generate_tasks(maildir);
    int total_tasks = broker->get_tasks_size();

    map<Worker *, Channel*> worker_map;

    for (int i = 0; i < number_of_threads; i++)
    {
        Worker *worker = new Worker(WorkerStatus::Stopped, messageBus, "w-" + to_string(i), "Worker " + to_string(i), "inter_file_" + to_string(i) + ".txt");
        messageBus->addSubscriber(worker);
        Channel *workerChannel = new Channel("c-w-" + to_string(i), "Worker " + to_string(i) + " Inbox Channel");
        worker->subscribe(workerChannel);
        worker_map[worker] = workerChannel;
    }

    vector<thread> threads;

    for (auto &pair : worker_map)
    {
        threads.push_back(thread(&Worker::run, pair.first));
    }

    cout << "Workers started processing tasks" << endl;
    while (broker->get_tasks_size() > 0)
    {
        // display progress bar
        cout << "Processing : " << 100 - ((broker->get_tasks_size() * 100) / total_tasks) << "% ["
             << string(100 - ((broker->get_tasks_size() * 100) / total_tasks), '#')
             << string((broker->get_tasks_size() * 100) / total_tasks, ' ') << "]"
             << " [" << total_tasks - broker->get_tasks_size() + 1 << "/" << total_tasks << "] files"
             << "\r";
        cout.flush();

        for (auto &pair : worker_map)
        {
            if (pair.first->get_status() == WorkerStatus::Stopped)
            {
                string task = broker->get_task();
                if(task!=""){
                    broker->publish(new HMessage(task, bkchannel), pair.second);
                    broker->notify();
                }

            }
        }
    }

    cout << endl;

    // wait for workers to finish
    while (true)
    {
        bool all_workers_stopped = true;
        for (auto &pair : worker_map)
        {
            if (pair.first->get_status() == WorkerStatus::Running)
            {
                all_workers_stopped = false;
                break;
            }
        }
        if (all_workers_stopped)
        {
            break;
        }
    }

    for (auto &pair : worker_map)
    {
        pair.first->finish();
    }

    for (auto &t : threads)
    {
        t.detach();
    }


    cout << "All workers finished processing tasks" << endl;

    vector<string> intermediary_files;
    for (int i = 0; i < number_of_threads; i++)
    {
        intermediary_files.push_back("inter_file_" + to_string(i) + ".txt");
    }

    // join intermediary files
    broker->join_intermediary_files(intermediary_files, "mega_file.txt");

    // reduce intermediary file
    broker->reduce_intermediary_file("mega_file.txt", "final_file.txt");

    time(&end);
    double time_taken = double(end - start);
    cout << "Time taken by program is : " << fixed << time_taken << setprecision(2) << " secs \n";

    return 0;
}
