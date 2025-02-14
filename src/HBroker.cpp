#include "../include/HBroker.h"
#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>

using namespace std;

HBroker::HBroker()
{
    this->tasks = vector<string>();
}

HBroker::HBroker(MessageBus *messageBus, string uid, string name) : Broker(messageBus, uid, name)
{
    this->tasks = vector<string>();
}

HBroker::~HBroker()
{
}


int HBroker::get_tasks_size()
{
    return this->tasks.size();
}

string HBroker::get_task()
{
    if(this->tasks.empty()){
        return "";
    }
    string task = this->tasks.back();
    this->tasks.pop_back();
    return task;
}


void HBroker::generate_tasks(string maildir)
{
    cout << "Broker starts generating tasks" << endl;
    // list recursively all files in maildir
    for (const auto &p : std::filesystem::recursive_directory_iterator(maildir))
    {
        if (!std::filesystem::is_directory(p))
        {
            this->tasks.push_back(p.path().string());
        }
    }

    cout << "Broker finishes generating tasks" << endl;
}

void HBroker::join_intermediary_files(vector<string> intermediary_files, string final_file)
{
    cout << "Broker starts joining intermediary files" << endl;

    ofstream outputFile(final_file);
    unordered_map<string, unordered_map<string, int>> emailMap;

    for (const string &intermediate_file : intermediary_files)
    {
        ifstream inputFile(intermediate_file);
        string from, to;

        while (inputFile >> from >> to)
        {
            emailMap[from][to]++;
        }

        inputFile.close();
    }

    for (const auto &emailCount : emailMap)
    {
        const string &key = emailCount.first;
        const unordered_map<string, int> &value = emailCount.second;

        outputFile << key << " ";
        for (const auto &emailCnt : value)
        {
            outputFile << emailCnt.second << ":" << emailCnt.first << " ";
        }
        outputFile << endl;
    }

    outputFile.close();
    cout << "Broker finishes joining intermediary files" << endl;
}

void HBroker::update(HMessage *message)
{
    cout << "Broker receives message from worker" << endl;
    if(message->get_content() == "finished"){
        this->publish(new HMessage(this->get_task(), this->get_primmary_channel()), message->get_sender_channel());
        this->notify();
    }
}
