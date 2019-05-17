#include"User.h"

User::User(int id, std::string _username, std::string _email) {
	user_id = id;
	username = _username;
	email = _email;
}

void User::print_information() {
	std::cout << " " << std::to_string(user_id) << " | " << username;
	std::cout << " | " << email << std::endl;
}

int User::get_id() {
	return user_id;
}

std::string User::get_username() {
	return username;
}