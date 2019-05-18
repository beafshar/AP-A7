#ifndef MOVIE_H
#define MOVIE_H

#include<map>
#include<iostream>
#include<vector>
#include<string>
#include<regex>
#include<sstream>

class Comment;

typedef std::vector<std::string> InputVec;
typedef std::map<std::string, std::string> InformationMAP;
typedef std::vector<Comment*> CommentsVector;
typedef std::pair<std::string, std::string> MapPair;

class Movie {
public:
	Movie(InputVec input_vector , int id);
	void fill_movie_information(InputVec input_vector);
	void set_map_keys();
	void calculate_average_rate();
	int get_film_id();
	void edit_movie_information(InputVec input_vector);
	void delete_movie();
	void score_movie(float score);
	void submit_comment(std::string content);
	bool delete_comment(int id);
	bool reply_comment(int id, std::string content);
	std::string get_movie_name();
	void view_details();
	void print_comments_and_replies();
	bool check_publish_command_validity(InputVec input_vec);
	bool check_price_validity(std::string price);
private:
	InformationMAP movie_information;
	int film_id;
	float price;
	bool deleted_by_publisher;
	std::vector<int> scores;
	float rate;
	CommentsVector comments;

};
#endif 

