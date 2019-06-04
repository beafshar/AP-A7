#include"Publisher.h"
#include"Movie.h"
#include"Filter.h"

Publisher::Publisher(int id) : Customer(id) {
	user_type = USER_PUBLISHER;
}

Movie* Publisher::publish_films(Request* req, int id) {
	Movie* film = new Movie(req,id,user_id);
	published_movies.push_back(film);
	return film;
}

bool Publisher::delete_film(int id) {
	for (int i = 0; i < published_movies.size(); i++) {
		if (published_movies[i]->get_film_id() == id) {
			published_movies[i]->delete_movie();
			return true;
		}
	}
//	throw PermissionDenied();
}
/*
bool Publisher::compare_by_id(Customer* a, Customer* b) {
	return a->get_id() < b->get_id();
}

bool Publisher::delete_comment(int film_id, int comment_id) {
	for (int i = 0; i < published_movies.size(); i++) {
		if (published_movies[i]->get_film_id() == film_id)
			return published_movies[i]->delete_comment(comment_id);
	}
	return false;
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

*/
