#include <iostream>

using namespace std;

enum class WorkerStatus { Running, Stopped, Paused, Error, Unknown };

class WTask {
	public:
		virtual void run() {
			cout << "WTask::run()" << endl;
		}
};

class BaseWorker {
	private:
		WorkerStatus status;
		WTask* task;

	public:


		virtual void work(){
			cout << "BaseWorker::work()" << endl;
		}

};