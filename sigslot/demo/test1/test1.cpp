#include "sigslot.h"
#include <Windows.h>
#include <iostream>
#include <time.h>
#include <tchar.h>

using namespace std;


struct Clock
{
	sigslot::signal1<int> Tick;//��������
	void SendMsg(int nTime)
	{
		Tick(nTime);
	}
};

/*******************************************************/

struct Student : public sigslot::has_slots<>
{
	void GetUp(int nTime)//�����������¼��Ĵ��� ��Tick�Ĳ���һһ��Ӧ
	{
		std::cout << "��ʱ�� : " <<nTime<< std::endl;
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
