#include"Publisher.h"
#include"Movie.h"
#include"Filter.h"



Publisher::Publisher(int id) : Customer(id) {
	user_type = USER_PUBLISHER;
}

Movie* Publisher::publish_films(InputVec input_vector , int id) {
	Movie* film = new Movie(input_vector ,id,user_id);
	published_movies.push_back(film);
	return film;
}

bool Publisher::edit_film_information(InputVec input_vector) {
	int id = std::stoi(input_vector[4]);
	for (int i = 0; i < published_movies.size(); i++) {
		if (published_movies[i]->get_film_id() == id) {
			published_movies[i]->edit_movie_information(input_vector);
			return true;
		}
	}
	throw PermissionDenied();
}

bool Publisher::delete_film(int id) {
	for (int i = 0; i < published_movies.size(); i++) {
		if (published_movies[i]->get_film_id() == id) {
			published_movies[i]->delete_movie();
			return true;
		}
	}
	throw PermissionDenied();
}

void Publisher::get_followers_list() {
	std::cout << "List of Followers" << std::endl;
	std::cout << "#. User Id | User Username | User Email " << std::endl;
	std::sort(followers.begin(), followers.end(), Publisher::compare_by_id);
	for (int i = 0; i < followers.size(); i++) {
		std::cout << i + 1 << ".";
		followers[i]->print_followers_information();
	}
}
//in sorte kar mikone ya na?
bool Publisher::compare_by_id(Customer* a, Customer* b) {
	return (a->get_id()) < (b->get_id());
}

void Publisher::add_followers(Customer* user) {
	followers.push_back(user);
}

void Publisher::view_published_movies(InputVec input_vector) {
	int count = 1;
	Filter* filter = new Filter(input_vector);
	for (int i = 0; i < published_movies.size(); i++) {
		Movie* m = published_movies[i];
		if (filter->filter_by_director(m) && filter->filter_by_max_year(m) &&
			filter->filter_by_min_rate(m) && filter->filter_by_min_year(m) &&
			filter->filter_by_name(m) && filter->filter_by_price(m)) {
			std::cout << count << ". ";
			m->view_published_details();
		}
		count++;
	}
}

bool Publisher::reply_comments(int film_id, int comment_id, std::string content) {
	for (int i = 0; i < published_movies.size(); i++) {
		if (published_movies[i]->get_film_id() == film_id)
			if (published_movies[i]->reply_comment(comment_id, content))
				return true;
	}
	return false;
}

bool Publisher::delete_comment(int film_id, int comment_id) {
	for (int i = 0; i < published_movies.size(); i++) {
		if (published_movies[i]->get_film_id() == film_id)
			return published_movies[i]->delete_comment(comment_id);
	}
	return false;
}

void Publisher::notify_followers(Message* message) {
	for (int i = 0; i < followers.size(); i++) {
		followers[i]->notify_user(message);
	}
}

float Publisher::publisher_get_paid() {
	float net_money = 0;
	for (int i = 0; i < published_movies.size(); i++) {
		if (published_movies[i]->if_movie_was_sold()) {
			net_money += published_movies[i]->pay_to_publisher();
		}	
	}
	money += net_money;
	return net_money;
}

bool Publisher::if_follower_exists(int id) {
	for (int i = 0; i < followers.size(); i++) {
		if (followers[i]->get_id() == id)
			return true;
	}
	return false;
}

void Publisher::get_published_movies(InputVec input_vector) {
	int count = 1;
	std::cout << "#. Film Id | Film Name | Film Length | ";
	std::cout << "Film price | Rate | Production Year | Film Director " << std::endl;
	Filter* filter = new Filter(input_vector);
	for (int i = 0; i < published_movies.size(); i++) {
		Movie* m = published_movies[i];
		if (published_movies[i]->if_deleted() == false &&
			filter->filter_by_director(m) && filter->filter_by_max_year(m) &&
			filter->filter_by_min_rate(m) && filter->filter_by_min_year(m) &&
			filter->filter_by_name(m) && filter->filter_by_price(m)) {
			std::cout << count << ". ";
			published_movies[i]->view_published_details();
		}
		count++;
	}
}
