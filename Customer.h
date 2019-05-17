#ifndef CUSTOMER_H
#define CUSTOMER_H

#include<map>
#include<vector>
#include<iostream>
#include<algorithm>
#include<regex>
#include<functional>

#define PUBLISHER true;
#define NORMAL_CUSTOMER false;

class CommandHandler;
class Message;
class User;
class Movie;
class Publisher;

typedef std::vector<std::string> InputVec;
typedef std::map<std::string, std::string> InformationMAP;
typedef std::vector<Message*> MessageVec;
typedef std::vector<User*> UsersVector;
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
	bool score_movie(int id, float rate);
	bool check_signup_command_validity(InputVec input_vector);
	bool check_email_validity(std::string email);
	std::string hash_password(std::string password);
	void comment_on_a_movie(int film_id, std::string content);
	void get_unread_notifications();
	void get_all_notification(int limit);
	void notify_user(Message* message);
	void notify_reply(std::string publisher_name, int id);
	void view_movie_details(int film_id);


protected:
	InformationMAP user_information;
	bool user_is_a_publisher;
	MessageVec notification;
	float money;
	PublishersVec followings;
	MoviesVector bought_movies;
	bool user_type;
	int user_id;
};
#endif 

