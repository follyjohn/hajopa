#include "../include/Channel.h"
#include "../include/HMessage.h"
#include "../include/Issuer.h"
#include "../include/MessageBus.h"
#include "../include/Subscriber.h"
#include "../include/Worker.h"
#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>


using namespace std;


void LPSArray(std::string pattern, int M, std::vector<int> lps)
{

    int len = 0;

    lps[0] = 0;
    int i = 1;
    while (i < M)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {

            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int KMPSearch(std::string pattern, std::string txt)
{
    int M = pattern.length();
    int N = txt.length();

    std::vector<int> lps(M);

    LPSArray(pattern, M, lps);

    int i = 0;
    int j = 0;
    int count = 0;
    vector<int> indexes;
    while ((N - i) >= (M - j))
    {
        if (pattern[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == M)
        {
            count++;
            j = lps[j - 1];
        }

        else if (i < N && pattern[j] != txt[i])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return count;
}

void reduceIntermediaryFile(string filename, string newfile)
{
    ifstream bufferReader(filename, ios::app);
    string fileContent = "";
    stringstream buffer;
    buffer << bufferReader.rdbuf();
    fileContent = buffer.str();
    bufferReader.close();

    string s;
    ifstream fileReader(filename, ios::app);
    ofstream fileWriter(newfile, ios::app);
    string sender;
    int count;
    while (getline(fileReader, s))
    {
        count = KMPSearch(s, fileContent);
        if (count != 0)
        {
            if ((s.find(" ")) != std::string::npos)
            {
                sender = s.substr(0, s.find(" "));
            }
            for (int i = 0; i < count; i++)
            {
                fileContent.erase(fileContent.find(s), s.length());
            }
            //cout << sender << " " << count << ":" << s.erase(s.find(sender), sender.length() + 1) << endl;
            fileContent += sender + " " + to_string(count) + ":" + s.erase(s.find(sender), sender.length() + 1) + "\n";
        }
    }
    std::string finalText;
    std::istringstream ss(fileContent);
    std::string line;

    std::map<std::string, std::vector<std::string>> sender_map;
    while (std::getline(ss, line))
    {
        std::istringstream line_ss(line);
        std::string sender;
        std::string data;
        line_ss >> sender >> data;
        sender_map[sender].push_back(data);
    }

    for (const auto &pair : sender_map)
    {
        finalText += pair.first + " ";
        for (const auto &data : pair.second)
        {
            finalText += data + " ";
        }
        finalText += "\n";
    }
    std::string firstline;
    std::getline(std::istringstream(finalText), firstline, '\n');
    fileWriter << finalText.erase(0, firstline.length() + 1);
    fileReader.close();
}

void writeIntermediaryFile(string filename) //, string filepath)
{
    ofstream fileWriter(filename, ios::app);
    //for loop should be removed
    for (int i = 0; i < 295; i++)
    {
        //this should be removed, file path will be given as parameter coming from dispatcher
        string var = "maildir/allen-p/_sent_mail/" + to_string(i + 1) + '_';
        //fileReader(filepath, ios::app);
        ifstream fileReader(var, ios::app);

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
}


void sayHello(Issuer *iss, Channel *chan)
{
    iss->publish(new HMessage("My first message from thread", "Hello everyone"), chan);
    iss->notify();
}


int main()
{
    time_t start, end;
    time(&start);

    MessageBus *messageBus = new MessageBus("mb-1", "Message Box");
    Channel *johnChannel = new Channel("c-john", "John Inbox Channel");
    Channel *samantaChannel = new Channel("c-samanta", "Samanta Inbox Channel");
    messageBus->addChannel(samantaChannel);
    messageBus->addChannel(johnChannel);

    Issuer *is_samanta = new Issuer(messageBus, "is-samanta", "Samanta");
    Issuer *is_john = new Issuer(messageBus, "is-john", "Samanta");

    Subscriber *sub_samanta = new Subscriber("sub-samanta", "Samanta");
    Subscriber *sub_john = new Subscriber("sub-john", "John");
    Subscriber *sub_tintin = new Subscriber("sub-tintin", "Tintin");

    Worker *worker = new Worker(WorkerStatus::Stopped, messageBus, "w-1", "Worker 1");

    messageBus->addSubscriber(sub_samanta);
    messageBus->addSubscriber(sub_john);
    messageBus->addSubscriber(sub_tintin);
    messageBus->addSubscriber(worker);

    sub_samanta->subscribe(samantaChannel);
    sub_john->subscribe(johnChannel);
    sub_tintin->subscribe(samantaChannel);
    worker->subscribe(samantaChannel);

    thread tone(sayHello, is_john, samantaChannel);
    thread ttwo(sayHello, is_samanta, johnChannel);
    thread tthree(sayHello, is_samanta, johnChannel);
    thread tfour(sayHello, is_samanta, johnChannel);
    thread tfive(sayHello, is_samanta, johnChannel);
    is_samanta->publish(new HMessage("My second message", "Hello John"), johnChannel);
    is_john->notify();
    worker->publish(new HMessage("Worker message", "Hello totto"), samantaChannel);
    worker->notify();
    tone.join();
    ttwo.join();
    tthree.join();
    tfour.join();
    tfive.join();
    // vector worjer = vector();

    // for(int i = 0; i < 10; i++)
    // {
    //     worjer.push_back(new Worker(WorkerStatus::Stopped, messageBus, "w-" + to_string(i), "Worker " + to_string(i)));
    // }

    // vecort worker = vector();

    // for (file in boo)
    // {
    //     select worker = worelr;
    //     dispater->pubish(new HMessage(runfunction, file, channnel))
    // }

    writeIntermediaryFile("fileWriter/test.txt");

    reduceIntermediaryFile("fileWriter/test.txt", "fileWriter/newfile.txt");

    time(&end);
    double time_taken = double(end - start);
    cout << "Time taken by program is : " << fixed << time_taken << setprecision(5) << " sec ";

    return 0;
}
