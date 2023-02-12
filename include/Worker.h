#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include "Issuer.h"
#include "Subscriber.h"

#ifndef WORKER_H
#define WORKER_H
using namespace std;

enum class WorkerStatus { Running, Stopped, Paused, Error, Unknown, Finished };

class  Worker: public Issuer, public Subscriber {

	protected:
		WorkerStatus status;

    public :
        Worker();
        Worker(WorkerStatus status, MessageBus * messageBus, string uid, string name);
        ~Worker();
        virtual void run() = 0;
        virtual void stop();
        virtual void pause();
        virtual void resume();
        virtual void finish();
        virtual WorkerStatus get_status();
        virtual void set_status(WorkerStatus status);
        virtual void update(HMessage* message) = 0;
};
#endif
