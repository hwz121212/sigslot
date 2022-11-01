#include "sigslot.h"
#include <Windows.h>
#include <iostream>
#include <time.h>
#include <tchar.h>

using namespace std;


struct Clock
{
	sigslot::signal1<int> Tick;//闹钟响起
	void SendMsg(int nTime)
	{
		Tick(nTime);
	}
};

/*******************************************************/

struct Student : public sigslot::has_slots<>
{
	void GetUp(int nTime)//对闹钟响起事件的处理 和Tick的参数一一对应
	{
		std::cout << "起床时间 : " <<nTime<< std::endl;
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	Clock   AlarmClock;
	Student MidSchoolStu;
	AlarmClock.Tick.connect(&MidSchoolStu, &Student::GetUp);
	for(int i=0; i<10; i++)
	{
		AlarmClock.SendMsg((int)time(NULL));
		Sleep(1000);
	}
	AlarmClock.Tick.disconnect(&MidSchoolStu);
	return 0;
}
