#include"UTflix.h"
#include"Customer.h"
#include"Publisher.h"
#include"Movie.h"
#include"Message.h"
// #include"NotFound.h"
#include"Filter.h"
#include"Recommender_System.h"

UTflix* UTflix::instance = 0;

UTflix* UTflix::get_instance(){
  if(instance == 0)
    instance = new UTflix();
  return instance;
}

UTflix::UTflix() {
	net_money = 0;
	Customer* admin = new Customer(ADMIN);
	admin->signup_admin("admin", "admin");
	UTflix_users.insert(UserPair(ADMIN, admin));
	recommender = new RecommenderSystem();
}


int UTflix::login(std::string username, std::string password) {
	CustomersMap::iterator it;
	for (it = UTflix_users.begin(); it != UTflix_users.end(); it++) {
		if (it->second->login(username,password)) {
			return it->first;
		}
	}
}

int UTflix::get_user_type(int id){
  return UTflix_users[id]->get_type();
}

int UTflix::signup(Request *req) {
		Customer* user = new Customer(UTflix_users.size() + 1);
		if (user->signup(req)) {
			if (check_if_user_existed(user) == false) {
				UTflix_users.insert(UserPair(UTflix_users.size()+1, user));
				add_publishers(user,req);
				return user->get_id();
			}
		}
//	throw BadRequest();
}

void UTflix::add_publishers(Customer* user, Request *req) {
	if (user->get_type() == USER_PUBLISHER) {
		Publisher* publisher = new Publisher(user->get_id());
		publisher->signup(req);
		publishers.insert(PublisherPair(user->get_id(), publisher));
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

int UTflix::check_user_type(int id) {
		if (UTflix_users[id]->get_id() == ADMIN)
			return ADMIN;
		else if (UTflix_users[id]->get_type() == USER_PUBLISHER)
			return USER_PUBLISHER;
		else if (UTflix_users[id]->get_type() == USER_CUSTOMER)
			return USER_CUSTOMER;
}

void UTflix::upload_films(Request *req,int id) {
	movies.push_back(publishers[id]->publish_films(req, movies.size()+1));
	recommender->expand_matrix();
}

bool UTflix::check_if_movie_existed(int id) {
	for (int i = 0; i < movies.size(); i++) {
		if (id == movies[i]->get_film_id() && movies[i]->if_deleted() == false)
			return true;
	}
	return false;
}

void UTflix::delete_movie(std::string film_id, int user_id) {
	int id = std::stoi(film_id);
	if (check_user_type(user_id) == USER_PUBLISHER) {
			if (check_if_movie_existed(id)) {
				publishers[user_id]->delete_film(id);
			}
			// else
			// 	throw NotFound();
		}
}

void UTflix::increase_user_money(std::string money_amount, int user_id) {
	int money = std::stoi(money_amount);
	UTflix_users[user_id]->increase_money(money);
}

/*
Publisher* UTflix::find_publisher(int id) {
	PublishersMap::iterator it;
	for (it = publishers.begin(); it != publishers.end(); it++) {
		if (it->first == id)
			return it->second;
	}
	throw NotFound();
}
*/
void UTflix::comment_on_films(int user_id,int id,std::string content) {
	if (check_if_movie_existed(id)) {
		if (movies[id - 1]->if_user_has_bought(UTflix_users[user_id]
      ->get_id()) == true)
					UTflix_users[user_id]->comment_on_a_movie(id, content);
		}
}


void UTflix::rate_movie(std::string film_id, std::string rate, int user_id) {
	int id = std::stoi(film_id);
  float score = std::stof(rate);
	if (check_if_movie_existed(id)) {
			if (movies[id - 1]->if_user_has_bought(user_id)== true)
				UTflix_users[user_id]->score_movie(id, score);
		}

}

void UTflix::buy_movie(std::string film_id, int user_id) {
	int id = std::stoi(film_id);
	if (check_if_movie_existed(id)) {
		if (movies[id -1]->if_user_has_bought(user_id) == false &&
				UTflix_users[user_id]->buy_movie(movies[id-1],recommender)) {
				net_money += movies[id - 1]->buy_movie(UTflix_users[user_id]->get_id());
				return;
			}
		}
}
