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
        cout << "Broker is processing n: " << i << " - "<< filename << endl;
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
