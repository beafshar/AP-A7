#ifndef CUSTOMER_H
#define CUSTOMER_H

#include<map>
#include<vector>
#include<iostream>
#include<algorithm>
#include<regex>
#include<functional>
#include"PermissionDenied.h"

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
	bool signup(InputVec input_vector);
	bool login(InputVec input_vector);
	void set_user_type();
	void follow_publisher(Publisher* publisher);
	void increase_money(float _money);
	bool score_movie(int id, int rate);
	bool check_signup_command_validity(InputVec input_vector);
	bool check_email_validity(std::string email);
	std::string hash_password(std::string password);
	bool comment_on_a_movie(int film_id, std::string content);
	void get_unread_notifications();
	void get_all_notification(int limit);
	void notify_user(Message* message);
	std::string get_username();
	int get_type();
	int get_id();
	void print_followers_information();
	bool buy_movie(Movie* movie);
	bool check_if_user_has_bought_movie(int id);
	virtual float publisher_get_paid() { return TEMP; };
	virtual Movie* publish_films(InputVec input_vector, int id) { return NULL; };
	virtual bool edit_film_information(InputVec input_vector) { return TEMP; };
	virtual bool delete_film(int id) { return TEMP; };
	virtual void get_followers_list() {};
	virtual bool reply_comments(int film_id, int comment_id, std::string content) { return TEMP; };
	virtual bool delete_comment(int film_id, int comment_id) { return TEMP; };
	virtual void notify_followers(Message* message) {};
	virtual bool if_follower_exists(int id) { return TEMP; }
	virtual void get_published_movies(InputVec input) {};
	void view_bought_movies(InputVec input);
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

