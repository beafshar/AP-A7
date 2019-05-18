#include"Contact.h"

Contact::Contact(int id, std::string _username, std::string _email) {
	user_id = id;
	username = _username;
	email = _email;
}

void Contact::print_information() {
	std::cout << " " << std::to_string(user_id) << " | " << username;
	std::cout << " | " << email << std::endl;
}

int Contact::get_id() {
	return user_id;
}

std::string Contact::get_username() {
	return username;
}