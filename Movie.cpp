#include"Movie.h"
#include"BadRequest.h"
#include"Comment.h"

Movie::Movie(InputVec input_vector , int id) {
	set_map_keys();
	fill_movie_information(input_vector);
	deleted_by_publisher = false;
	price = std::stof(movie_information["price"]);
	film_id = id;
	rate = 0;

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
	for (int i = 3; i < input_vec.size(); i++) {
		if (input_vec[i] == "price")
			if (check_price_validity(input_vec[i + 1]) == false)
				return false;
	}
	return true;
}

bool Movie::check_price_validity(std::string price) {
	static const std::regex doubleRegex{ R"([+\-]?(?:0|[1-9]\d*)(?:\.\d*)?(?:[eE][+\-]?\d+)?)" };
	if (std::regex_match(price, doubleRegex)) {
		std::istringstream inputStream(price);
		double d;
		inputStream >> d;
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
	for (int i = 3; i < input_vector.size() - 1; i += 2) {
		it = movie_information.find(input_vector[i]);
		if (it != movie_information.end()) {
			movie_information[it->first] = input_vector[i + 1];
		}
	}
}

void Movie::delete_movie() {
	deleted_by_publisher = true;
}

void Movie::score_movie(float score) {
	scores.push_back(score);
	calculate_average_rate();
}

void Movie::submit_comment(std::string content) {
	Comment* comment = new Comment(comments.size(), content);
	comments.push_back(comment);
}

bool Movie::delete_comment(int id) {
	for (int i = 0; i < comments.size(); i++) {
		if (comments[i]->get_id() == id) {
			comments[i]->delete_comment();
		}
		else
			return false;
	}
	return true;
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
	std::cout << "Length = " << movie_information["lenght"] << std::endl;
	std::cout << "Year = " << movie_information["year"] << std::endl;
	std::cout << "Summary = " << movie_information["summary"] << std::endl;
	std::cout << "Rate = " << rate << std::endl;
	std::cout << "Price = " <<movie_information["price"]<< std::endl;
	std::cout << std::endl << std::endl;
	print_comments_and_replies();
}

void Movie::print_comments_and_replies() {
	std::cout << "Comments" << std::endl;
	for (int i = 0; i < comments.size(); i++) {
		std::cout << comments[i]->get_id() << ". " << comments[i]->get_content();
		std::cout << std::endl;
		comments[i]->print_replies();
	}
}