#include"Publisher.h"
#include"Movie.h"
#include"User.h"

Publisher::Publisher(int id) : Customer(id) {
	user_type = PUBLISHER;
}

bool Publisher::publish_films(InputVec input_vector) {
	try {
		Movie* film = new Movie(input_vector ,published_movies.size());
		published_movies.push_back(film);
		//notify members
	}
	catch (std::exception &exp) {
		std::cout << exp.what();
	}
}

bool Publisher::edit_film_information(InputVec input_vector) {
	//check valid input
	int id = std::stoi(input_vector[4]);
	for (int i = 0; i < published_movies.size(); i++) {
		if (published_movies[i]->get_film_id() == id)
			published_movies[i]->edit_movie_information(input_vector);
	}
	return true;
}

bool Publisher::delete_film(int id) {
	for (int i = 0; i < published_movies.size(); i++) {
		if (published_movies[i]->get_film_id() == id)
			published_movies[i]->delete_movie();
	}
	return true;
}

void Publisher::get_followers_list() {
	std::cout << "List of Followers" << std::endl;
	std::cout << "#. User Id | User Username | User Email " << std::endl;
	std::sort(followers.begin(), followers.end(), compare_by_id);
	for (int i = 0; i < followers.size(); i++) {
		std::cout << i + 1 << ".";
		followers[i]->print_information();
	}
}
//in sorte kar mikone ya na?
bool Publisher::compare_by_id(User* a, User* b) {
	return (a->get_id()) < (b->get_id());
}

void Publisher::add_followers(User* user) {
	followers.push_back(user);
}