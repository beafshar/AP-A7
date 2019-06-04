#include"Movie.h"
#include"Comment.h"
#include"Sale.h"
//#include"NotFound.h"

Movie::Movie(Request* req, int id, int _publisher_id) {
	set_map_keys();
	publisher_id = _publisher_id;
	fill_movie_information(req);
	deleted_by_publisher = false;
	sold_to_user = false;
	price = std::stoi(movie_information["price"]);
	film_id = id;
	rate = 0;
	weight = 0;
}

bool Movie::if_movie_was_sold() {
	return sold_to_user;
}

void Movie::set_map_keys() {
	movie_information.insert(MapPair("name", ""));
	movie_information.insert(MapPair("year", ""));
	movie_information.insert(MapPair("length", ""));
	movie_information.insert(MapPair("price", ""));
	movie_information.insert(MapPair("summary", ""));
	movie_information.insert(MapPair("director", ""));
}

void Movie::fill_movie_information(Request* req) {
		InformationMAP::iterator it;
    for(it = movie_information.begin();it != movie_information.end(); it++)
      movie_information[it->first] = req->getBodyParam(it->first);
      std::cout<<"****"<<movie_information["director"]<<"****"<<std::endl;
}


void Movie::calculate_average_rate() {
	float sum = 0;
	for (int i = 0; i < scores.size(); i++)
		sum += scores[i];
	rate = sum / scores.size();
}

int Movie::get_film_id() {
	return film_id;
}

void Movie::delete_movie() {
	deleted_by_publisher = true;
}

bool Movie::if_deleted() {
	return deleted_by_publisher;
}

void Movie::score_movie(float score) {
	scores.push_back(score);
	calculate_average_rate();
}

void Movie::submit_comment(std::string content, int user_id) {
	Comment* comment = new Comment(comments.size() + 1, content, user_id, film_id);
	comments.push_back(comment);
}


std::string Movie::get_movie_name() {;
	return movie_information["name"];
}


float Movie::get_rate() {
	return rate;
}

int Movie::get_publisher_id() {
	return publisher_id;
}



int Movie::buy_movie(int user_id) {
	Sale* sold_movie = new Sale(film_id, rate, price, user_id, publisher_id);
	sold_movies.push_back(sold_movie);
	sold_to_user = true;
	return price;
}

bool Movie::if_user_has_bought(int user_id) {
	for (int i = 0; i < sold_movies.size(); i++) {
		if (sold_movies[i]->get_customer_id() == user_id)
			return true;
	}
	return false;
}

int Movie::get_price() {
	return price;
}

std::string Movie::get_director() {
	return movie_information["director"];
}

int Movie::get_year() {
	return std::stoi(movie_information["year"]);
}
/*
bool Movie::check_if_comment_exists(int id) {
	for (int i = 0; i < comments.size(); i++) {
		if (comments[i]->get_id() == id)
			return true;
	}
	throw NotFound();
}
*/

bool Movie::compare_by_id(Movie* a, Movie* b) {
	return a->get_film_id() < b->get_film_id();
}

bool Movie::compare_by_rate(Movie*a, Movie* b) {
	return a->get_rate() > b->get_rate();
}

void Movie::add_weight() {
	weight++;
}

int Movie::get_weight() {
	return weight;
}

bool Movie::compare_by_weight(Movie* a, Movie* b) {
	return a->get_weight() > b->get_weight();
}
