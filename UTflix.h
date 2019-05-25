#ifndef UTFLIX_H
#define UTFLIX_H

#include<vector>
#include<iostream>
#include<string>
#include"command_handler.h"
#include<map>

#define NULL_USER -1
#define LOGIN_SIZE 7
#define FILM_SIZE 15
#define MIN_COMMAND_SIZE 5
#define COMMENTS_SIZE 7
#define RATE_SIZE 7
#define ALL_NOTIF_SIZE 6
#define REPLY_SIZE 9
#define DELETE_SIZE 7
#define TOP4 5
#define ADMIN -2

class Customer;
class Movie;
class Publisher;
class RecommenderSystem;

typedef std::map<int, Publisher*> PublishersMap;
typedef std::map<int,Customer*> CustomersMap;
typedef std::vector<Movie*> MovieVec;
typedef std::vector<std::string> InputVec;
typedef std::pair<int, Customer*> UserPair;
typedef std::pair<int, Publisher*> PublisherPair;

class UTflix {
public:
	UTflix();
	void add_publishers(Customer* user, InputVec input);
	void signup(InputVec input);
	Publisher* find_publisher(int id);
	int check_user_type();
	void upload_films(InputVec input);
	void login(InputVec input);
	void edit_movie(InputVec input);
	void delete_movie(InputVec input);
	void get_followers_list();
	void increase_user_money(InputVec input);
	void view_movie_details(std::string input);
	void follow_publisher(InputVec input);
	void set_active_user(Customer* user);
	bool check_if_user_existed(Customer* user);
	bool check_if_movie_existed(int id);
	void comment_on_films(InputVec input);
	void notify_publisher_has_uploaded_a_film();
	void view_unread_notification();
	void view_all_notification(InputVec input);
	std::string find_needed(InputVec input, std::string need);
	void notify_user_has_submited_comment(std::string film, int film_id);
	void rate_movie(InputVec input);
	void notify_user_has_rated_movie(std::string film, int film_id);
	void reply_comment(InputVec input);
	void notify_publisher_has_replied_comment(int film_id, int comment_id);
	void delete_comment(InputVec input);
	void buy_movie(InputVec input);
	void notify_user_has_bought_movie(std::string film, int film_id);
	void notify_user_has_followed_publisher(int id);
	void publisher_views_his_published_movies(InputVec input);
	void print_recommendation_films(int id);
	void user_views_his_bought_movies(InputVec input);
	void pay_to_publisher();
	bool check_int_validity(std::string integer);
	bool check_if_comment_existed(int film_id, int comment_id);
	void user_search_movies(InputVec input);
	void view_filtered_movies(InputVec input);
	void logout();
	void view_money();

private:
	CustomersMap UTflix_users;
	PublishersMap publishers;
	Customer* active_user;
	MovieVec movies;
	int net_money;
	Customer* null_user;
	RecommenderSystem* recommender;

};
#endif 
