#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>
#include <ctime>
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

bool getPic(std::vector<std::string> &url, std::string &curTime)
{
	std::string curPath = std::filesystem::current_path();
	if (!std::filesystem::exists(curPath + "/cache/"))
	{
		std::filesystem::create_directory(curPath + "/cache/");
	}
	if (!std::filesystem::exists(curPath + "/cache/" + curTime))
	{
		std::filesystem::create_directory(curPath + "/cache/" + curTime);
	}
	std::filesystem::rename("./msgTitle.txt", "./cache/" + curTime + "/msgTitle.txt");
	std::filesystem::rename("./msgBody.txt", "./cache/" + curTime + "/msgBody.txt");
	std::filesystem::rename("./msgURL.txt", "./cache/" + curTime + "/msgURL.txt");
	std::filesystem::rename("./msgPicURL.txt", "./cache/" + curTime + "/msgPicURL.txt");
	if (url.size() == 0)
	{
		std::filesystem::remove("./ cache / " + curTime + " / msgPicURL.txt");
		return false;
	}
	for (auto &picurl : url)
	{
		std::string fileName = "";
		int start = picurl.size() - 1;
		for (auto i = start; i >= 0; i--)
		{
			if (picurl[i] == '/')
			{
				start = i + 1;
				break;
			}
		}
		for (int i = start; i < picurl.size(); i++)
		{
			fileName += picurl[i];
		}
		// std::string curlcmd = "curl -o" + curPath + "/cache/" + curTime + "/" + fileName + picurl;
		std::string curlcmd = "curl " + picurl + " -o ./cache/" + curTime + "/" + fileName;
		system(curlcmd.c_str());
		std::cout << curlcmd << std::endl;
		picurl = "./cache/" + curTime + "/" + fileName;
	}
	return true;
}

bool AddPictures(Cyan::MiraiBot &bot, std::vector<std::string> &picCache, Cyan::MessageChain &msg)
{
	int count = 0;
	if (picCache.size() == 0)
	{
		return false;
	}
	for (auto cache : picCache)
	{
		count++;
		Cyan::GroupImage img = bot.UploadGroupImage(cache);
		msg = msg + Cyan::MessageChain().Image(img);
	}
	std::cout << count << std::endl;
	return true;
}

int main(int argc, char *argv[])
{
	using namespace std;
	using namespace Cyan;

	std::string currentTime = std::to_string(time(0));
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

	std::string title = "", body = "", url = "";
	std::fstream msgFile;
	std::stringstream sstp;
	msgFile.open("msgTitle.txt");
	sstp << msgFile.rdbuf();
	title = sstp.str();
	sstp.clear();
	sstp.str("");
	msgFile.close();

	msgFile.open("msgBody.txt");
	sstp << msgFile.rdbuf();
	body = sstp.str();
	sstp.clear();
	sstp.str("");
	msgFile.close();

	msgFile.open("msgURL.txt");
	sstp << msgFile.rdbuf();
	url = sstp.str();
	sstp.clear();
	sstp.str("");
	msgFile.close();

	msgFile.open("msgPicURL.txt");
	std::vector<std::string> picurl;
	std::string strtp;
	while (msgFile >> strtp)
	{
		picurl.push_back(strtp);
	}
	msgFile.close();

	if (title.empty() || body.empty() || url.empty())
	{
		std::cout << "Invalid message" << std::endl;
		return 0;
	}

	getPic(picurl, currentTime);
	try
	{
		Cyan::MessageChain msg = MessageChain().Plain(title + "\n" + body + "\n" + url + "\n");
		if (picurl.size() != 0)
		{
			AddPictures(bot, picurl, msg);
		}
		bot.SendMessage(GQQ, msg);
		std::cout << "Complete" << std::endl;
	}
	catch (const std::exception &ex)
	{
		std::cerr << "Fail to send message" << '\n';
		std::cerr << ex.what() << '\n';
	}

	return 0;
}