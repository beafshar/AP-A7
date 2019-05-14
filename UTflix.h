#ifndef UTFLIX_H
#define UTFLIX_H



#include<vector>
#include<iostream>
#include<string>
#include"command_handler.h"
#include<map>

class Customer;

typedef std::map<int,Customer*> CustomersMap;

class UTflix {
public:
	UTflix();
	void run();

private:
	CustomersMap UTflix_users;
	Customer* active_user;

};
#endif 
