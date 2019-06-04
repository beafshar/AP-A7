#ifndef UTFLIX_H
#define UTFLIX_H

#include<vector>
#include<iostream>
#include<string>
#include<map>
#include "../server/server.hpp"

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
  static UTflix* get_instance();
	void add_publishers(Customer* user, Request *req);
	int signup(Request *req);
	Publisher* find_publisher(int id);
	int check_user_type(int id);
  bool check_if_user_existed(Customer* user);
  int login(std::string username, std::string password);
  void delete_movie(std::string film_id,int user_id);
  void increase_user_money(std::string money, int user_id);
  void rate_movie(std::string film_id, std::string rate, int user_id);
  void buy_movie(std::string film_id, int user_id);
  bool check_if_movie_existed(int id);
	void upload_films(Request *req,int id);
  std::string publisher_views_his_published_movies(Request *req,int id);
  int get_user_type(int id);
	std::string view_movie_details(int film_id,int user_id);
  std::string print_recommendation_films(int id,int user_id);
  std::string set_movie_details_body();
  std::string set_publisher_home_body();
  std::string set_user_home_body();
  std::string set_profile_body();
  std::string user_views_available_movies(Request *req,int id);
  std::string user_views_bought_movies(Request *req,int id);
	void comment_on_films(int user_id,int film_id,std::string content);
/*
	void buy_movie(InputVec input);

	bool check_if_comment_existed(int film_id, int comment_id);

  */

private:
	CustomersMap UTflix_users;
	PublishersMap publishers;
	MovieVec movies;
	int net_money;
	RecommenderSystem* recommender;
  UTflix();
  static UTflix* instance;
};
#endif
