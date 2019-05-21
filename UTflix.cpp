#include"UTflix.h"
#include"Customer.h"
#include"BadRequest.h"
#include"PermissionDenied.h"
#include"Publisher.h"
#include"Movie.h"
#include"Message.h"
#include"NotFound.h"

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
				add_publishers(user);
				set_active_user(user);
				std::cout << "OK" << std::endl;
				return;
			}
		}
	}
	throw BadRequest();
}

void UTflix::add_publishers(Customer* user) {
	if (user->get_type() == USER_PUBLISHER) {
		Publisher* publisher = new Publisher(user->get_id());
		publishers.insert(PublisherPair(user->get_id(), publisher));
	}
}

void UTflix::set_active_user(Customer* user) {
	active_user = user;
	if (check_user_type()) {
		active_user = publishers[user->get_id()];
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
		if (active_user->get_type() == USER_PUBLISHER)
			return true;
		else
			return false;
	}
	throw PermissionDenied();
}

void UTflix::upload_films(InputVec input) {
	if (check_user_type()) {
		if (input.size() == 15) {
				movies.push_back(active_user->publish_films(input, movies.size()));
				notify_publisher_has_uploaded_a_film();
				std::cout << "OK" << std::endl;                                  
		}
		else
			throw BadRequest();
	}
	else
		throw PermissionDenied();
}

void UTflix::notify_publisher_has_uploaded_a_film() {
	Message* message = new Message("");
	message->create_publish_film_notif(active_user->get_username(), active_user->get_id());
	active_user->notify_followers(message);
}

bool UTflix::check_if_movie_existed(int id) {
	for (int i = 0; i < movies.size(); i++) {
		if (id == movies[i]->get_film_id())
			return true;
	}
	return false;
}
void UTflix::edit_movie(InputVec input) {
	if (check_user_type()) {
		if (input.size() >= 5 && input.size() % 2 == 1) {
			int id = std::stoi(find_needed(input, "film_id"));
			if (check_if_movie_existed(id)) {
				if (active_user->edit_film_information(input))
					std::cout << "OK" << std::endl;
			}
			else
				throw NotFound();
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
			int id = std::stoi(find_needed(input, "film_id"));
			if (check_if_movie_existed(id)) {
				if (active_user->delete_film(id));
				std::cout << "OK" << std::endl;
			}
			else
				throw NotFound();
		}
		else
			throw BadRequest();
	}
	else
		throw PermissionDenied();
}

void UTflix::get_followers_list() {
	if (check_user_type()) {
		active_user->get_followers_list();
	}
	else
		throw PermissionDenied();
}

void UTflix::increase_user_money(InputVec input) {
	if (input.size() == 5) {
		float money = std::stoi(find_needed(input, "amount"));
		active_user->increase_money(money);
		std::cout << "OK" << std::endl;
		return;
		}
		throw BadRequest();
}

void UTflix::view_movie_details(std::string input) {
	int id = std::stoi(input);
	if (check_if_movie_existed(id)) {
		for (int i = 0; i < movies.size(); i++) {
			if (movies[i]->get_film_id() == id &&movies[i]->if_deleted() == false)
				movies[i]->view_details();
		}
		print_recommendation_films(id);
		return;
	}
	throw NotFound();
}


void UTflix::follow_publisher(InputVec input) {
	if (input.size() == 5) {
		int id = std::stoi(find_needed(input, "user_id"));
		active_user->follow_publisher(find_publisher(id));
		notify_user_has_followed_publisher(id);
		std::cout << "OK" << std::endl;
		return;
	}
	throw BadRequest();
}

void UTflix::notify_user_has_followed_publisher(int id) {
	Message* message = new Message("");
	message->create_follow_notif(active_user->get_username(),active_user->get_id());
	publishers[id]->notify_user(message);

}

Publisher* UTflix::find_publisher(int id) {
	PublishersMap::iterator it;
	for (it = publishers.begin(); it != publishers.end(); it++) {
		if (it->first == id)
			return it->second;
	}
	throw NotFound();
}

void UTflix::comment_on_films(InputVec input) {
	if (input.size() == 7) {
		int id = std::stoi(find_needed(input, "film_id"));
		std::string content = find_needed(input, "content");
		if (check_if_movie_existed(id)) {
			if (movies[id]->if_user_has_bought(active_user->get_id()) == true) {
				active_user->comment_on_a_movie(id, content);
				notify_user_has_submited_comment(movies[id]->get_movie_name(), id);
				std::cout << "OK" << std::endl;
			}
			else
				throw PermissionDenied();
		}
		else
			throw NotFound();
	}
	else
		throw BadRequest();
}

void UTflix::notify_user_has_submited_comment(std::string film, int film_id) {
	Message* message = new Message("");
	message->create_comment_film_notif(active_user->get_username(), active_user->get_id(),
		film, film_id);
	publishers[movies[film_id]->get_publisher_id()]->notify_user(message);
}

std::string UTflix::find_needed(InputVec input, std::string need) {
	for (int i = 0; i < input.size() - 1; i++) {
		if (input[i] == need)
			return input[i + 1];
	}
	throw BadRequest();
}

void UTflix::view_all_notification(InputVec input) {
	if (input.size() == 6 && input[4] == "limit") {
		int limit = std::stoi(input[5]);
		active_user->get_all_notification(limit);
	}
	else
		throw BadRequest();
}

void UTflix::view_unread_notification() {
	active_user->get_unread_notifications();
}

void UTflix::rate_movie(InputVec input) {
	if (input.size() == 7) {
		float score = 0;
		int id = std::stoi(find_needed(input, "film_id"));
		if (check_if_movie_existed(id)) {
			if (check_rate_validity(find_needed(input, "score")) &&
				movies[id]->if_user_has_bought(active_user->get_id()) == true) {
				score = std::stof(find_needed(input, "score"));
				if (active_user->score_movie(id, score)) {
					notify_user_has_rated_movie(movies[id]->get_movie_name(), id);
					std::cout << "OK" << std::endl;
					return;
				}
			}
		}
		else
			throw NotFound();
	}
	throw BadRequest();
}

bool UTflix::check_rate_validity(std::string rate) {
	static const std::regex intRegex{ R"(\d+)" };
	if (std::regex_match(rate, intRegex)) {
		std::istringstream inputStream(rate);
		int i;
		inputStream >> i;
		return true;
	}
	throw BadRequest();
}

void UTflix::notify_user_has_rated_movie(std::string film, int film_id) {
	Message* message = new Message("");
	message->create_rate_film_notif(active_user->get_username(), active_user->get_id(),
		film, film_id);
	publishers[movies[film_id]->get_publisher_id()]->notify_user(message);
}

bool UTflix::check_if_comment_existed(int film_id, int comment_id) {
	if (check_if_movie_existed(film_id))
		return movies[film_id]->check_if_comment_exists(comment_id);
}

void UTflix::reply_comment(InputVec input) {
	if (check_user_type()) {
		if (input.size() == 9) {
			int film_id = std::stoi(find_needed(input, "film_id"));
			int comment_id = std::stoi(find_needed(input, "comment_id"));
			std::string content = find_needed(input, "content");
			if (check_if_comment_existed(film_id, comment_id)) {
				if (active_user->reply_comments(film_id, comment_id, content)) {
					notify_publisher_has_replied_comment();
					std::cout << "OK" << std::endl;
				}
			}
			else
				throw NotFound();
		}
		else
			throw BadRequest();
	}
	else
		throw PermissionDenied();
}

void UTflix::notify_publisher_has_replied_comment() {
	Message* message = new Message("");
	message->create_reply_notif(active_user->get_username(), active_user->get_id());
	UTflix_users[message->get_user()]->notify_user(message);
}

void UTflix::delete_comment(InputVec input) {
	if (check_user_type()) {
		if (input.size() == 7) {
			int film_id = std::stoi(find_needed(input, "film_id"));
			int comment_id = std::stoi(find_needed(input, "comment_id"));
			if (check_if_comment_existed(film_id, comment_id)) {
				if (active_user->delete_comment(film_id, comment_id))
					std::cout << "OK" << std::endl;
			}
			else
				throw NotFound();
		}
		else
			throw BadRequest();
	}
	else
		throw PermissionDenied();
}

void UTflix::notify_user_has_bought_movie(std::string film, int film_id) {
	Message* message = new Message("");
	message->create_buy_film_notif(active_user->get_username(), active_user->get_id(),
		film, film_id);
	publishers[movies[film_id]->get_publisher_id()]->notify_user(message);

}

void UTflix::buy_movie(InputVec input) {
	if (input.size() == 5) {
		int id = std::stoi(find_needed(input, "film_id"));
		if (check_if_movie_existed(id)) {
			if (movies[id]->if_user_has_bought(active_user->get_id()) == false &&
				active_user->buy_movie(movies[id])) {
				net_money += movies[id]->buy_movie(active_user->get_id());
				notify_user_has_bought_movie(movies[id]->get_movie_name(), id);
				std::cout << "OK" << std::endl;
				return;
			}
		}
		throw NotFound();
	}
	throw BadRequest();
}
//check sorts
void UTflix::print_recommendation_films(int id) {
	std::cout << "Recommendation Film" << std::endl;
	std::cout << "#. Film Id | Film Name | Film Length | Film Director " << std::endl;
	std::sort(movies.begin(), movies.end(), UTflix::compare_by_id);
	std::sort(movies.begin(), movies.end(), UTflix::compare_by_rate);
	int count = 1;
	for (int i = 0; count < 5; i++) {
		if (i == movies.size())
			break;
		if (active_user->check_if_user_has_bought_movie(movies[i]->
			get_film_id()) == false && movies[i]->get_film_id() != id &&
			movies[i]->if_deleted() == false) {
			std::cout << count << ". ";
			movies[i]->print_recommendation();
			count++;
		}
	}
}

bool UTflix::compare_by_id(Movie*a, Movie* b) {
	return (a->get_film_id()) < (b->get_film_id());
}

bool UTflix::compare_by_rate(Movie*a, Movie* b) {
	return (a->get_rate()) > (b->get_rate());
}

void UTflix::pay_to_publisher() {
	if (check_user_type()) {
		net_money -= active_user->publisher_get_paid();
		std::cout << "OK" << std::endl;
	}
	else
		throw PermissionDenied();
}

