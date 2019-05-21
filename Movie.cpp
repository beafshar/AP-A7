#include"Movie.h"
#include"BadRequest.h"
#include"Comment.h"
#include"Sale.h"
#include"NotFound.h"

Movie::Movie(InputVec input_vector , int id, int _publisher_id) {
	set_map_keys();
	publisher_id = _publisher_id;
	fill_movie_information(input_vector);
	deleted_by_publisher = false;
	sold_to_user = false;
	price = std::stoi(movie_information["price"]);
	film_id = id;
	rate = 0;
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

void Movie::fill_movie_information(InputVec input_vector) {
	if (check_publish_command_validity(input_vector)) {
		InformationMAP::iterator it;
		for (int i = 3; i < input_vector.size() - 1; i += 2) {
			it = movie_information.find(input_vector[i]);
			if (it != movie_information.end()) {
				movie_information[it->first] = input_vector[i + 1];
			}
			else
				throw BadRequest();
		}
	}
	else
		throw BadRequest();
}

bool Movie::check_publish_command_validity(InputVec input_vec) {
	for (int i = START; i < input_vec.size(); i++) {
		if (input_vec[i] == "price")
			if (check_price_validity(input_vec[i + 1]) == false)
				return false;
	}
	return true;
}

bool Movie::check_price_validity(std::string price) {
	static const std::regex intRegex{ R"(\d+)" };
	if (std::regex_match(price, intRegex)) {
		std::istringstream inputStream(price);
		int i;
		inputStream >> i;
		return true;
	}
	return false;
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

void Movie::edit_movie_information(InputVec input_vector) {
	InformationMAP::iterator it;
	for (int i = START; i < input_vector.size() - 1; i += 2) {
		it = movie_information.find(input_vector[i]);
		if (it != movie_information.end()) {
			movie_information[it->first] = input_vector[i + 1];
		}
	}
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

bool Movie::delete_comment(int id) {
	for (int i = 0; i < comments.size(); i++) {
		if (comments[i]->get_id() == id) {
			comments[i]->delete_comment();
			return true;
		}
	}
	return false;
}

bool Movie::reply_comment(int id, std::string content) {
	for (int i = 0; i < comments.size(); i++) {
		if (comments[i]->get_id() == id) {
			comments[i]->reply(content);
			return true;
		}
	}
	return false;
}

std::string Movie::get_movie_name() {;
	return movie_information["name"];
}

void Movie::view_details() {
	std::cout << "Details of Film " << movie_information["name"] << std::endl;
	std::cout << "Id = " << film_id << std::endl;
	std::cout << "Director = " << movie_information["director"] << std::endl;
	std::cout << "Length = " << movie_information["length"] << std::endl;
	std::cout << "Year = " << movie_information["year"] << std::endl;
	std::cout << "Summary = " << movie_information["summary"] << std::endl;
	std::cout << "Rate = " << std::setprecision(2) <<rate << std::endl;
	std::cout << "Price = " <<movie_information["price"]<< std::endl;
	std::cout << std::endl << std::endl;
	print_comments_and_replies();
}

void Movie::print_comments_and_replies() {
	std::cout << "Comments" << std::endl;
	for (int i = 0; i < comments.size(); i++) {
		if (comments[i]->check_if_deleted() == false) {
			std::cout << comments[i]->get_id() << ". " << comments[i]->get_content();
			std::cout << std::endl;
			comments[i]->print_replies();
		}
	}
	std::cout << std::endl << std::endl;
}

float Movie::get_rate() {
	return rate;
}

int Movie::get_publisher_id() {
	return publisher_id;
}

void Movie::print_recommendation() {
	std::cout << film_id << " | " << movie_information["name"] << " | ";
	std::cout << movie_information["length"] << " | ";
	std::cout << movie_information["director"] << std::endl;
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

float Movie::pay_to_publisher() {
	float publisher_money = 0;
	for (int i = 0; i < sold_movies.size(); i++) {
		if (sold_movies[i]->if_paid_to_publisher() == false) {
			publisher_money += sold_movies[i]->calculate_publisher_share();
			sold_movies[i]->pay_to_publisher();
		}
	}
	return publisher_money;
}

std::string Movie::get_director() {
	return movie_information["director"];
}

int Movie::get_year() {
	return std::stoi(movie_information["year"]);
}

bool Movie::check_if_comment_exists(int id) {
	for (int i = 0; i < comments.size(); i++) {
		if (comments[i]->get_id() == id)
			return true;
	}
	throw NotFound();
}


void Movie::view_published_details() {
	std::cout << film_id << " | " << movie_information["name"] << " | ";
	std::cout << movie_information["length"] << " | " << price << " | ";
	std::cout << std::setprecision(2) << rate << " | " << movie_information["year"];
	std::cout << " | " << movie_information["director"] << std::endl;
}

bool Movie::compare_by_id(Movie* a, Movie* b) {
	return a->get_film_id() < b->get_film_id();
}

bool Movie::compare_by_rate(Movie*a, Movie* b) {
	return a->get_rate() > b->get_rate();
}

int Movie::get_comment_user(int comment_id) {
	for (int i = 0; i < comments.size(); i++) {
		if (comments[i]->get_id() == comment_id)
			return comments[i]->get_user();
	}
}