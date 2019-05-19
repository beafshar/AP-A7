#ifndef UTFLIX_H
#define UTFLIX_H



#include<vector>
#include<iostream>
#include<string>
#include"command_handler.h"
#include<map>

#define PUBLISHER 1;
#define NORMAL_CUSTOMER 2;
#define NULL_USER -1

class Customer;
class Movie;
class Publisher;

typedef std::map<int, Publisher*> PublishersMap;
typedef std::map<int,Customer*> CustomersMap;
typedef std::vector<Movie*> MovieVec;
typedef std::vector<std::string> InputVec;
typedef std::pair<int, Customer*> UserPair;
typedef std::pair<int, Publisher*> PublisherPair;

class UTflix {
public:
	UTflix();
	void add_publishers(int id);
	void signup(InputVec input);
	Publisher* find_publisher(int id);
	bool check_user_type();
	void upload_films(InputVec input);
	void login(InputVec input);
	void edit_movie(InputVec input);
	void delete_movie(InputVec input);
	void get_followers_list();
	void increase_user_money(InputVec input);
	void view_movie_details(std::string input);
	void follow_publisher(InputVec input);
	int parse_movie_id(InputVec input);
	void set_active_user(Customer* user);
	bool check_if_user_existed(Customer* user);
	bool check_if_movie_existed();
private:
	CustomersMap UTflix_users;
	PublishersMap publishers;
	Customer* active_user;
	MovieVec movies;
	float net_money;
};
#endif 
