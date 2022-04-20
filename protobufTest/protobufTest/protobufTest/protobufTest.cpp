// protobufTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include "user.pb.h"

using namespace std;

int main(int argc, char** argv)
{
	IM::Account account1;
	account1.set_id(1);
	account1.set_name("windsun");
	account1.set_password("123456");

	string serializeToStr;
	account1.SerializeToString(&serializeToStr);
	cout << "序列化后的字节：" << serializeToStr << endl;


	IM::Account account2;
	if (!account2.ParseFromString(serializeToStr))
	{
		cerr << "failed to parse student." << endl;
		return -1;
	}
	cout << "反序列化：" << endl;
	cout << account2.id() << endl;
	cout << account2.name() << endl;
	cout << account2.password() << endl;

	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
