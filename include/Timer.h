#ifndef TIMER_H_
#define TIMER_H_

#include <IceUtil/Thread.h>
#include <IceUtil/Mutex.h>
#include <string.h>

class Timer : public IceUtil::Thread
{
	private:
		int _seconds;
		string _name;

	public:
		Timer (string name = "noname", int seconds=0) {
			_seconds = seconds;
			_name = name;
		}

		~Timer() {

		}

		int getSecondsLeft() { return _seconds; }

		virtual void run ()
		{
			while(_seconds>0)
			{
				IceUtil::ThreadControl::sleep( IceUtil::Time::seconds(1));
				_seconds--;
				std::cout << _name << " left " << _seconds << " seconds... " << endl;
			}
			std::cout << _name << " is finished. " << endl;
		};
};

#endif /* TIMER_H_ */
