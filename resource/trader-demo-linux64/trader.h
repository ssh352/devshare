#ifndef TRADER_H_
#define TRADER_H_
#include <string>
using namespace std;
class Trader {
public:
	string username;
	string password;
	string brokerid;
	string trade_addr;
	Trader(string username,string password,string brokerid,string trade_addr);
};



#endif