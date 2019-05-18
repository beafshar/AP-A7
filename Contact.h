#ifndef CONTACT_H
#define CONTACT_H

#include<string>
#include<iostream>

class Contact {
public:
	Contact(int id, std::string _username, std::string _email);
	void print_information();
	int get_id();
	std::string get_username();
private:
	int user_id;
	std::string username;
	std::string email;
};
#endif 

