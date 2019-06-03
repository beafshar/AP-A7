#ifndef CUSTOMER_H
#define CUSTOMER_H

#include<map>
#include<vector>
#include<iostream>
#include<algorithm>
#include<regex>
#include<functional>
#include "../server/server.hpp"


#define USER_PUBLISHER 1
#define USER_CUSTOMER 2
#define TEMP 1
#define MAX_RATE 10
#define MIN_RATE 0
#define MAX_SIGNUP_SIZE 13
#define MIN_SIGNUP_SIZE 11
#define START 3
#define STEP 2
#define ID 4

class CommandHandler;
class Message;
class Movie;
class Publisher;
class Customer;
class RecommenderSystem;

typedef std::vector<std::string> InputVec;
typedef std::map<std::string, std::string> InformationMAP;
typedef std::vector<Message*> MessageVec;
typedef std::vector<Customer*> CustomersVector;
typedef std::vector<Movie*> MoviesVector;
typedef std::pair<std::string, std::string> MapPair;
typedef std::vector<Publisher*> PublishersVec;

class Customer {
public:
	Customer(int id);
	void set_map_keys();
	bool signup(Request *req);
	bool login(std::string username, std::string password);
	void set_user_type();
  void increase_money(float _money);
	bool score_movie(int id, int rate);
	bool check_email_validity(std::string email);
	std::string hash_password(std::string password);
/*
	bool comment_on_a_movie(int film_id, std::string content);

  */
	std::string get_username();
	int get_type();
	int get_id();
	int get_money();
  bool buy_movie(Movie* movie, RecommenderSystem* recommender);
	bool check_if_user_has_bought_movie(int id);
  virtual bool delete_film(int id) { return TEMP; };
  virtual Movie* publish_films(Request* req, int id) { return NULL; };
  /*

	virtual bool if_follower_exists(int id) { return TEMP; }
	virtual void get_published_movies(InputVec input) {};
  */
	std::string view_bought_movies(std::string name);

	void signup_admin(std::string username, std::string password);
	void add_movies_weight(int id,RecommenderSystem* recommender);

protected:
	InformationMAP user_information;
	MessageVec notification;
	float money;
	PublishersVec followings;
	MoviesVector bought_movies;
	int user_type;
	int user_id;
};
#endif
