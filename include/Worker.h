#include <iostream>
#include "Issuer.h"
#include "Subscriber.h"

using namespace std;

enum class WorkerStatus { Running, Stopped, Paused, Error, Unknown };

class  Worker: public Issuer, public Subscriber {

	private:
		WorkerStatus status;

	public:
		Worker();
        Worker(WorkerStatus status, MessageBus * messageBus, string uid, string name);
        ~Worker();
        virtual void run();
        virtual void stop();
        virtual void pause();
        virtual void resume();
        virtual WorkerStatus get_status();
        virtual void set_status(WorkerStatus status);

};
