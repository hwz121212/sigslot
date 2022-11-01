// test2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "sigslot.h"  
#include <string>  
#include <stdio.h>  
#include <iostream>  
using namespace std;  

class CSender  
{  
public:  
	sigslot::signal2<string, int> m_pfnsigDanger;  

	void Panic()  
	{  
		static int nVal = 0;  
		char szVal[20] = {0};  
		sprintf_s(szVal, "help--%d", nVal);
		m_pfnsigDanger(szVal, nVal++);  
	}  
};  

class CReceiver:public sigslot::has_slots<>  
{  
public:  
	void OnDanger(string strMsg, int nVal)  
	{  
		//printf("%s ==> %d", strMsg.c_str(), nVal);  
		cout << strMsg.c_str() << " ==> " << nVal << endl;  
	}  
};  

int main()  
{  
	CSender sender;  
	CReceiver recever;  
	cout << "create object ok..." << endl;  
	sender.m_pfnsigDanger.connect(&recever, &CReceiver::OnDanger);  
	cout << "connect succ!" << endl;  

	while (1)  
	{  
		cout << "in while..." << endl;
		sender.Panic();  
		Sleep(2);
		cout << "end of sleep" << endl;  
	}  

	return 0;  
}  
