#ifndef USER_H
#define USER_H

#include<string>
#include<iostream>

class User {
public:
	User(int id, std::string _username, std::string _email);
	void print_information();
	int get_id();
	std::string get_username();
private:
	int user_id;
	std::string username;
	std::string email;
};
#endif 

