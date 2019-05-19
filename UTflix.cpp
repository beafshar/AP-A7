#include"UTflix.h"
#include"Customer.h"
#include"BadRequest.h"
#include"PermissionDenied.h"
#include"Publisher.h"
#include"Movie.h"

UTflix::UTflix() {
	net_money = 0;
	active_user = new Customer(NULL_USER);
}

void UTflix::login(InputVec input) {
	if (input.size() == 7) {
		CustomersMap::iterator it;
		for (it = UTflix_users.begin(); it != UTflix_users.end(); it++) {
			if (it->second->login(input)) {
				set_active_user(it->second);
				std::cout << "OK" << std::endl;
				return;
			}
		}
	}
	throw BadRequest();
}

void UTflix::signup(InputVec input) {
	if (input.size() == 13 || input.size() == 11) {
		Customer* user = new Customer(UTflix_users.size());
		if (user->signup(input)) {
			if (check_if_user_existed(user) == false) {
				UTflix_users.insert(UserPair(UTflix_users.size(), user));
				set_active_user(user);
				add_publishers(user->get_id());
				std::cout << "OK" << std::endl;
				return;
			}
		}
	}
	throw BadRequest();
}

void UTflix::add_publishers(int id) {
	if (check_user_type()) {
		Publisher* publisher = new Publisher(id);
		publishers.insert(PublisherPair(id, publisher));
	}
}

void UTflix::set_active_user(Customer* user) {
	active_user = user;
	if (check_user_type()) {
		Publisher* publisher = new Publisher(user->get_id());
		active_user = publisher;
	}
}

bool UTflix::check_if_user_existed(Customer* user) {
	CustomersMap::iterator it;
	for (it = UTflix_users.begin(); it != UTflix_users.end(); it++) {
		if (it->second->get_username().compare(user->get_username()) == 0)
			return true;
	}
	return false;
}

bool UTflix::check_user_type() {
	if (active_user->get_id() != NULL_USER){
		if (active_user->get_type() == 1)
			return true;
		else
			return false;
	}
	throw PermissionDenied();
}

void UTflix::upload_films(InputVec input) {
	if (check_user_type()) {
		if (input.size() == 15) {
			if (check_if_movie_existed() == false) {
				movies.push_back(active_user->publish_films(input, movies.size()));
				std::cout << "OK" << std::endl;
			}
			else
				throw;
		}
		else
			throw BadRequest();
	}
	else
		throw PermissionDenied();
}

bool UTflix::check_if_movie_existed() {
	for (int i = 0; i < movies.size(); i++) {
		if (i == movies[i]->get_film_id())
			return true;
	}
	return false;
}
void UTflix::edit_movie(InputVec input) {
	if (check_user_type()) {
		if (input.size() >= 5 && input.size() % 2 == 1) {
			if (active_user->edit_film_information(input))
				std::cout << "OK" << std::endl;
		}
		else
			throw BadRequest();
	}
	else
		throw PermissionDenied();
}

void UTflix::delete_movie(InputVec input) {
	if (check_user_type()) {
		if (input.size() == 5) {
			int id = parse_movie_id(input);
			if (active_user->delete_film(id));
				std::cout << "OK" << std::endl;
		}
		else
			throw BadRequest();
	}
	else
		throw PermissionDenied();
}

int UTflix::parse_movie_id(InputVec input) {
	for (int i = 0; i < input.size(); i++) {
		if (input[i].compare("film_id") == 0) {
			int id = std::stoi(input[i + 1]);
			return id;
		}
	}
}

void UTflix::get_followers_list() {
	if (check_user_type()) {
		active_user->get_followers_list();
		std::cout << "OK" << std::endl;
	}
	else
		throw PermissionDenied();
}

void UTflix::increase_user_money(InputVec input) {
	if (input.size() == 5) {
		for (int i = 0; i < input.size(); i++) {
			if (input[i].compare("amount") == 0) {
				float money = std::stoi(input[i + 1]);
				active_user->increase_money(money);
				return;
			}
		}
	}
		throw BadRequest();
}

void UTflix::view_movie_details(std::string input) {
	if (check_if_movie_existed()) {
		int id = std::stoi(input);
		active_user->view_movie_details(id);
	}
	throw;
}

void UTflix::follow_publisher(InputVec input) {
	if (input.size() == 5) {
		for (int i = 0; i < input.size(); i++) {
			if (input[i].compare("user_id") == 0) {
				int id = std::stoi(input[i+1]);
				active_user->follow_publisher(find_publisher(id));
				return;
			}
		}
		throw BadRequest();
	}
}

Publisher* UTflix::find_publisher(int id) {
	PublishersMap::iterator it;
	for (it = publishers.begin(); it != publishers.end(); it++) {
		if (it->first == id)
			return it->second;
	}
}