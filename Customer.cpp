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
	return true;
}

bool Customer::login(InputVec input_vector) {
	InformationMAP::iterator it;
	for (int i = 3; i < input_vector.size() - 1; i += 2) {
		it = user_information.find(input_vector[i]);
		if (it != user_information.end()) {
			if (user_information[it->first] == input_vector[i + 1])
				return true;
			else
				return false;
		}
		else
			throw BadRequest();

	}
	return false;
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