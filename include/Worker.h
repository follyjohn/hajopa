#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include "Issuer.h"
#include "Subscriber.h"

using namespace std;

enum class WorkerStatus { Running, Stopped, Paused, Error, Unknown, Finished };

class  Worker: public Issuer, public Subscriber {

	private:
		WorkerStatus status;
        string intermediary_file;
        HMessage current_task;
        ofstream outputFile;

    public : Worker();
        Worker(WorkerStatus status, MessageBus * messageBus, string uid, string name, string intermediary_file);
        ~Worker();
        virtual void run();
        virtual void stop();
        virtual void pause();
        virtual void resume();
        virtual void finish();
        virtual WorkerStatus get_status();
        virtual void set_status(WorkerStatus status);
        virtual void run_task(string task);
        virtual void update(HMessage* message);


};
