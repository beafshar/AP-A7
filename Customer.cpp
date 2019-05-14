#include"Customer.h"
#include"BadRequest.h"
#include"User.h"
#include"Publisher.h"
#include"Movie.h"

Customer::Customer(int id) {
	set_map_keys();
	user_id = id;
}

void Customer::set_map_keys() {
	user_information.insert(MapPair("email", ""));
	user_information.insert(MapPair("username", ""));
	user_information.insert(MapPair("password", ""));
	user_information.insert(MapPair("age", ""));
	user_information.insert(MapPair("publisher", ""));
}

bool Customer::signup(InputVec input_vector) {
	//check requset validity user not existed
	InformationMAP::iterator it;
	for (int i = 3; i < input_vector.size()- 1; i += 2) {
		it = user_information.find(input_vector[i]);
		if (it != user_information.end()) {
			user_information[it->first] = input_vector[i + 1];
		}
		else
			throw BadRequest();
	}
	set_user_type();
	user_information["password"] = hash_password(user_information["password"]);
	return true;
}

bool Customer::login(InputVec input_vector) {
	int flag = 0;
	for (int i = 3; i < input_vector.size(); i += 2) {
		if (input_vector[i] == "username")
			if (input_vector[i + 1].compare(user_information["username"]) != 0)
				return false;
		else if (input_vector[i] == "password") {
			std::string pass = hash_password(input_vector[i + 1]);
			if (pass.compare(user_information["password"]) != 0)
				return false;
		}
	}
	return true;
}

void Customer::set_user_type() {
	InformationMAP::iterator it;
	it = user_information.find("publisher");
	if (it != user_information.end()) {
		if (user_information["publisher"].compare("true") == 0) {
			user_type = PUBLISHER;
		}
		else if (user_information["publisher"].compare("false") == 0) {
			user_type = NORMAL_CUSTOMER;
		}
		else
			throw BadRequest();
	}
}

void Customer::follow_publisher(Publisher* publisher) {
	followings.push_back(publisher);
	//notify publisher
	User* user = new User(user_id, user_information["username"], user_information["email"]);
	publisher->add_followers(user);

}

void Customer::increase_money(float _money) {
	money += _money;
}

bool Customer::score_movie(int id, float rate) {
	for (int i = 0; i < bought_movies.size(); i++) {
		if (bought_movies[i]->get_film_id() == id) {
			bought_movies[i]->score_movie(rate);
		}
		else
			throw BadRequest();
	}
}

bool Customer::check_signup_command_validity(InputVec input_vec) {
	if (input_vec.size() < 11 || input_vec.size() > 13)
		return false;
	for (int i = 3; i < input_vec.size(); i++) {
		if (input_vec[i] == "email")
			if (check_email_validity(input_vec[i + 1]) == false)
				return false;
		

	}
}
//kar mikone regex?
bool Customer::check_email_validity(std::string email) {
	const std::regex pattern
		("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

	return std::regex_match(email, pattern);
}

std::string Customer::hash_password(std::string password) {
	std::hash<std::string> str_hash;
	password = str_hash(password);
	return password;
}

void Customer::comment_on_a_movie(int film_id, std::string content) {
	for (int i = 0; i < bought_movies.size(); i++) {
		if (bought_movies[i]->get_film_id() == film_id) {
			bought_movies[i]->submit_comment(content);
		}
		else
			throw BadRequest();
	}
}