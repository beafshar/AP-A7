#ifndef CUSTOMER_H
#define CUSTOMER_H

#include<map>
#include<vector>
#include<iostream>
#include<algorithm>

#define PUBLISHER true;
#define NORMAL_CUSTOMER false;

class CommandHandler;
class Comment;
class User;
class Movie;
class Publisher;

typedef std::vector<std::string> InputVec;
typedef std::map<std::string, std::string> InformationMAP;
typedef std::vector<Comment*> CommentsVector;
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

protected:
	InformationMAP user_information;
	bool user_is_a_publisher;
	CommentsVector notification;
	float money;
	PublishersVec followings;
	MoviesVector bought_movies;
	bool user_type;
	int user_id;
};
#endif 

