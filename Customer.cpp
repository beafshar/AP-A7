#include"Customer.h"
//#include"BadRequest.h"
#include"Publisher.h"
#include"Movie.h"
//#include"Message.h"
#include"Filter.h"
#include"Recommender_System.h"



Customer::Customer(int id) {
	user_type = USER_CUSTOMER;
	money = 0;
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

void Customer::signup_admin(std::string username, std::string password) {
 	user_information["username"] = username;
 	user_information["password"] = hash_password(password);
}

bool Customer::signup(Request *req) {
		InformationMAP::iterator it;
		for(it = user_information.begin();it != user_information.end(); it++)
      user_information[it->first] = req->getBodyParam(it->first);
		set_user_type();
		user_information["password"] = hash_password(user_information["password"]);
    if(check_email_validity(user_information["email"]))
      return true;
	return false;
}

bool Customer::login(std::string username, std::string password) {
  std::string pass = hash_password(password);
  if(username.compare(user_information["username"]) != 0 &&
    pass.compare(user_information["password"]) != 0)
    return true;
	return false;
}

void Customer::set_user_type() {
	InformationMAP::iterator it;
	it = user_information.find("publisher");
	if (it != user_information.end()) {
		if (user_information["publisher"].compare("on") == 0) {
			user_type = USER_PUBLISHER;
		}
		else if (user_information["publisher"].compare("") == 0
			|| user_information["publisher"].compare("") == 0) {
			user_type = USER_CUSTOMER;
		}
	}
}

void Customer::increase_money(float _money) {
	money += _money;
}

bool Customer::score_movie(int id, int rate) {
	// if (rate > MAX_RATE || rate < MIN_RATE)
	// 	throw BadRequest();
	for (int i = 0; i < bought_movies.size(); i++) {
		if (bought_movies[i]->get_film_id() == id &&
			bought_movies[i]->if_deleted() == false) {
			bought_movies[i]->score_movie(rate);
		}
		// else
		// 	throw BadRequest();
	}
	return true;
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
/*
bool Customer::comment_on_a_movie(int film_id, std::string content) {
	for (int i = 0; i < bought_movies.size(); i++) {
		if (bought_movies[i]->get_film_id() == film_id &&
			bought_movies[i]->if_deleted() == false) {
			bought_movies[i]->submit_comment(content ,user_id);
			return true;
		}
	}
	throw BadRequest();
}


*/
std::string Customer::get_username() {
	return user_information["username"];
}

int Customer::get_type() {
	return user_type;
}
int Customer::get_id() {
	return user_id;
}

bool Customer::buy_movie(Movie* movie, RecommenderSystem* recommender) {
	if (money >= movie->get_price()) {
		add_movies_weight(movie->get_film_id(),recommender);
		bought_movies.push_back(movie);
		money -= movie->get_price();
		return true;
	}
}

bool Customer::check_if_user_has_bought_movie(int id) {
	for (int i = 0; i < bought_movies.size(); i++) {
		if (bought_movies[i]->get_film_id() == id)
			return true;;
	}
	return false;
}

int Customer::get_money() {
	return money;
}

void Customer::add_movies_weight(int id,RecommenderSystem* recommender) {
	for (int i = 0; i < bought_movies.size(); i++) {
		recommender->fill_matrix(id, bought_movies[i]->get_film_id());
	}
}
