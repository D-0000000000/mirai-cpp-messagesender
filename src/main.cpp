// 注意: 本项目的所有源文件都必须是 UTF-8 编码

// 这是一个“反撤回”机器人
// 在群里回复 “/anti-recall enabled.” 或者 “撤回没用” 之后
// 如果有人在群里撤回，那么机器人会把撤回的内容再发出来

#include <iostream>
#include <fstream>
#include <map>
#include <mirai.h>
#include "myheader.h"

uint64_t getull(std::string &str)
{
	uint64_t ret = 0;
	try
	{
		ret = std::stoull(str, nullptr, 10);
	}
	catch (...)
	{
		return 0;
	}
	return ret;
}

int main(int argc, char *argv[])
{
	using namespace std;
	using namespace Cyan;

#if defined(WIN32) || defined(_WIN32)
	// 切换代码页，让 CMD 可以显示 UTF-8 字符
	system("chcp 65001");
#endif

	if (argc != 2)
	{
		std::cout << "WRONG ARGS" << std::endl;
		return 0;
	}

	std::string authKey = "";
	std::string QQstr = "";
	std::string Gstr = "";

	std::fstream settings;
	try
	{
		settings.open("settings.txt", std::fstream::in);
	}
	catch (...)
	{
		std::cout << "Cannot open settings.txt" << std::endl;
		return 0;
	}
	settings >> authKey;
	settings >> QQstr;
	settings >> Gstr;
	settings.close();

	uint64_t QQuint = getull(QQstr);
	if (QQuint == 0)
	{
		std::cout << "Invalid QQ number" << std::endl;
		return 0;
	}
	uint64_t Guint = getull(Gstr);
	if (Guint == 0)
	{
		std::cout << "Invalid Group number" << std::endl;
		return 0;
	}
	Cyan::QQ_t botQQ = Cyan::QQ_t(QQuint);
	Cyan::GID_t GQQ = Cyan::GID_t(Guint);

	MiraiBot bot("127.0.0.1", 8080);
	while (true)
	{
		try
		{
			bot.Auth(authKey, botQQ);
			break;
		}
		catch (const std::exception &ex)
		{
			cout << ex.what() << endl;
		}
		MiraiBot::SleepSeconds(1);
	}
	cout << "Bot Working..." << endl;

	std::string message = argv[1];
	Cyan::MessageChain msg = MessageChain().Plain(message);
	bot.SendMessage(GQQ, msg);
	std::cout << "Complete" << std::endl;

	return 0;
}