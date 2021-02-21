// 注意: 本项目的所有源文件都必须是 UTF-8 编码

// 这是一个“反撤回”机器人
// 在群里回复 “/anti-recall enabled.” 或者 “撤回没用” 之后
// 如果有人在群里撤回，那么机器人会把撤回的内容再发出来

#include <iostream>
#include <map>
#include <mirai.h>
#include <mirai/third-party/nlohmann/json.hpp>
#include "myheader.h"

int main(int argc, char *argv[])
{
	using namespace std;
	using namespace Cyan;

#if defined(WIN32) || defined(_WIN32)
	// 切换代码页，让 CMD 可以显示 UTF-8 字符
	system("chcp 65001");
#endif

	MiraiBot bot("127.0.0.1", 8080);
	while (true)
	{
		try
		{
			bot.Auth("AUTHKEY", 00000000_qq);
			// Fill Authkey and QQbot number
			break;
		}
		catch (const std::exception &ex)
		{
			cout << ex.what() << endl;
		}
		MiraiBot::SleepSeconds(1);
	}
	cout << "Bot Working..." << endl;

	if (argc != 2)
	{
		std::cout << "WRONG ARGS" << std::endl;
		return 0;
	}
	else
	{
		std::string message = argv[1];
		Cyan::MessageChain msg = MessageChain().Plain(message);
		bot.SendMessage(00000000_gid, msg);
		// Fill target QQ group ID
	}
	std::cout << "Complete" << std::endl;
	return 0;
}