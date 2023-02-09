#include "../include/Broker.h"
#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

using namespace std;

Broker::Broker()
{
    this->tasks = vector<string>();
}

Broker::Broker(MessageBus *messageBus, string uid, string name) : Issuer(messageBus, uid, name), Subscriber(uid, name)
{
    this->tasks = vector<string>();
}

Broker::~Broker()
{
}

void Broker::generate_tasks(string maildir)
{
    cout << "Broker starts generating tasks" << endl;
    // list recursively all files in maildir
    for (const auto &p : std::filesystem::recursive_directory_iterator(maildir))
    {
        if (!std::filesystem::is_directory(p))
        {
            this->tasks.push_back(p.path());
        }
    }

    cout << "Broker finishes generating tasks" << endl;
}

void Broker::join_intermediary_files(vector<string> intermediry_files, string final_file){
    cout << "Broker starts joining intermediary files" << endl;
    ofstream outputFile(final_file);
    for (const auto &intermediry_file : intermediry_files)
    {
        ifstream inputFile(intermediry_file);
        outputFile << inputFile.rdbuf();
    }
    cout << "Broker finishes joining intermediary files" << endl;
}


void Broker::test_genereate_interfile(){
    cout << "Broker starts generating intermediary files" << endl;
    ofstream fileWriter("./inter.txt", ios::app);
    for (int i = 0; i < this->tasks.size(); i++)
    {
        string filename = this->tasks[i];
        ifstream fileReader(filename, ios::app);
        string s;
        string currentLine;
        string sender;
        // cout << "Broker is processing n: " << i << " - "<< filename << endl;
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
    }
    fileWriter.close();
    cout << "Broker finishes generating intermediary files" << endl;
}

int Broker::get_tasks_size(){
    return this->tasks.size();
}

string Broker::get_task(){
    string task = this->tasks.back();
    this->tasks.pop_back();
    return task;
}


void Broker::reduce_intermediary_file(string intermediry_file, string final_file){
    map<string, vector<string>> emailMap;
    ifstream inputFile(intermediry_file);
    ofstream outputFile(final_file);

    // Read the input file line by line
    string from, to;
    while (inputFile >> from >> to)
    {
        emailMap[from].push_back(to);
    }

    // Write the map to the output file
    for (const auto &emailCount : emailMap)
    {
        const string &key = emailCount.first;
        const vector<string> &value = emailCount.second;
        outputFile << key << " ";
        map<string, int> count;
        for (const string &email : value)
        {
            ++count[email];
        }
        for (const auto &emailCnt : count)
        {
            outputFile << emailCnt.second << ":" << emailCnt.first << " ";
        }
        outputFile << endl;
    }
}
