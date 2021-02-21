#include <algorithm>
#include <string>
#include <random>

int rndm(int n, int m)
{
	if (n <= 0 || m <= 0 || n >= 65536 || m >= 65536)
	{
		return -1;
	}
	std::random_device gen;
	int ans = 0;
	for (int i = 0; i < m; i++)
	{
		ans += (gen() % n + 1);
	}
	return ans;
}

int parsern(std::string &cmd)
{
	std::string nstr = "";
	int start = 1, end = 0;
	for (int i = 0; i < cmd.size(); i++)
	{
		if (cmd[i] == 'r')
		{
			start = i + 1;
		}
		if (cmd[i] == 'd')
		{
			end = i;
			break;
		}
	}
	if (start != 2)
	{
		return -1;
	}
	for (int i = start; i < end; i++)
	{
		nstr += cmd[i];
	}
	int n = -1;
	try
	{
		n = std::stoi(nstr, nullptr, 10);
	}
	catch (...)
	{
		return -1;
	}
	return n;
}

int parserm(std::string &cmd)
{
	std::string mstr = "";
	int start = 1, end = cmd.size();
	for (int i = 0; i < cmd.size(); i++)
	{
		if (cmd[i] == 'd')
		{
			start = i + 1;
			break;
		}
	}
	for (int i = start; i < end; i++)
	{
		mstr += cmd[i];
	}
	int m = -1;
	try
	{
		m = std::stoi(mstr, nullptr, 10);
	}
	catch (...)
	{
		return -1;
	}
	return m;
}

int rndm(std::string &cmd)
{
	int n = parsern(cmd);
	int m = parserm(cmd);
	int ret = rndm(n, m);
	return ret;
}
