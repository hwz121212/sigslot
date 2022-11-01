#include <iostream>
#include "sigslot.h"
using namespace std;
using namespace sigslot;


class CSender
{
public:
	sigslot::signal0<> Click0;
	sigslot::signal1<int> Click1;
};

class CReceiver : public sigslot::has_slots<>
{
public:
	void OnClick0()
	{
		std::cout << "OnClick0..." << std::endl;
	}

	virtual void OnClick1(int a)
	{
		std::cout << "OnClick1 " << a << " ..." << std::endl;
	}
};

class CDeliver : public CReceiver
{
public:
	void OnClick0()
	{
		std::cout << "CDeliver OnClick0..." << std::endl;
	}

	virtual void OnClick1(int a)
	{
		std::cout << "CDeliver OnClick1 " << a << " ..." << std::endl;
	}
};

int main()
{
	CReceiver recv;
	CDeliver deliver;
	CSender sender;

	sender.Click0.connect(&recv, &CReceiver::OnClick0);
	sender.Click1.connect(&recv, &CReceiver::OnClick1);
	sender.Click1.connect(&deliver, &CDeliver::OnClick1);

	sender.Click0();
	sender.Click1(2);

	cout << "============" << endl;
	
	//sender.Click0.disconnect(&recv);
	//sender.Click0.disconnect_all();
	//sender.Click1.disconnect(&recv);
//	sender.Click1.disconnect(&deliver);

	sender.Click0.emit();
	//sender.Click0();
	//sender.Click1(2);

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
