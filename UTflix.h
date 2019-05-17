#ifndef UTFLIX_H
#define UTFLIX_H



#include<vector>
#include<iostream>
#include<string>
#include"command_handler.h"
#include<map>

class Customer;
class Movie;

typedef std::map<int,Customer*> CustomersMap;
typedef std::vector<Movie*> MovieVec;

class UTflix {
public:
	UTflix();
private:
	CustomersMap UTflix_users;
	Customer* active_user;
	MovieVec movies;

};
#endif 
