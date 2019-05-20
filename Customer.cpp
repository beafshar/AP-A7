#include"Customer.h"
#include"BadRequest.h"
#include"Publisher.h"
#include"Movie.h"
#include"Message.h"

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
	if (check_signup_command_validity(input_vector)) {
		InformationMAP::iterator it;
		for (int i = 3; i < input_vector.size() - 1; i += 2) {
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
	return false;
}

bool Customer::login(InputVec input_vector) {
	for (int i = 3; i < input_vector.size(); i += 2) {
		if (input_vector[i] == "username") {
			if (input_vector[i + 1].compare(user_information["username"]) != 0)
				return false;
		}
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
		else if (user_information["publisher"].compare("false") == 0
			|| user_information["publisher"].compare("") == 0) {
			user_type = NORMAL_CUSTOMER;
		}
		else
			throw BadRequest();
	}
}

void Customer::follow_publisher(Publisher* publisher) {
	followings.push_back(publisher);
	publisher->add_followers(this);

}

void Customer::view_movie_details(int film_id) {
	for (int i = 0; i < bought_movies.size(); i++) {
		if (bought_movies[i]->get_film_id() == film_id)
			if(bought_movies[i]->if_deleted()==false)
				bought_movies[i]->view_details();
	}
}

void Customer::increase_money(float _money) {
	money += _money;
}

bool Customer::score_movie(int id, float rate) {
	for (int i = 0; i < bought_movies.size(); i++) {
		if (bought_movies[i]->get_film_id() == id && 
			bought_movies[i]->if_deleted() == false) {
			bought_movies[i]->score_movie(rate);
		}
		else
			throw BadRequest();
	}
	return false;
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

bool Customer::comment_on_a_movie(int film_id, std::string content) {
	for (int i = 0; i < bought_movies.size(); i++) {
		if (bought_movies[i]->get_film_id() == film_id &&
			bought_movies[i]->if_deleted() == false) {
			bought_movies[i]->submit_comment(content ,user_id);
			return true;
		}
		else
			throw BadRequest();
	}
}

void Customer::get_unread_notifications() {
	std::cout << "#. Notification Message " << std::endl;
	for (int i = notification.size() - 1; i > -1;i--){
		if (notification[i]->if_read() == false) {
			notification[i]->read_message();
			std::cout << i + 1 << ". " << notification[i]->get_content();
			std::cout << std::endl;
		}
	}
}

void Customer::get_all_notification(int limit) {
	std::cout << "#. Notification Message " << std::endl;
	for (int i = notification.size(); limit != 0; i--) {
		std::cout << i + 1 << ". " << notification[i]->get_content();
		std::cout << std::endl;
		limit--;
	}
}
void Customer::notify_user(Message* message) {
	notification.push_back(message);
}


std::string Customer::get_username() {
	return user_information["username"];
}

int Customer::get_type() {
	return user_type;
}
int Customer::get_id() {
	return user_id;
}

void Customer::print_followers_information() {
	std::cout << " " << std::to_string(user_id) << " | " << user_information["username"];
	std::cout << " | " << user_information["email"] << std::endl;
}

bool Customer::buy_movie(Movie* movie) {
	if (money >= movie->get_price()) {
		bought_movies.push_back(movie);
		money -= movie->get_price();
		return true;
	}
	return false;
}

bool Customer::check_if_user_has_bought_movie(int id) {
	for (int i = 0; i < bought_movies.size(); i++) {
		if (bought_movies[i]->get_film_id() == id)
			return true;;
	}
	return false;
}