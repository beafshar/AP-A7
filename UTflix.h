#ifndef UTFLIX_H
#define UTFLIX_H



#include<vector>
#include<iostream>
#include<string>
#include"command_handler.h"

class Customer;

typedef std::vector<Customer*> CustomersVector;

class UTflix {
public:
	UTflix();
	void run();

private:
	CustomersVector UTflix_users;
	Customer* active_user;

};
#endif 
