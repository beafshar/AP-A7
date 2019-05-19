#ifndef PUBLISHER_H
#define PUBLISHER_H

#include"Customer.h"

class Movie;

class Publisher :public Customer {
public:
	Publisher(int id);
	virtual Movie* publish_films(InputVec input_vector, int id);
	virtual bool edit_film_information(InputVec input_vector);
	virtual bool delete_film(int id);
	virtual void get_followers_list();
	static bool compare_by_id(Customer* a, Customer* b);
	void add_followers(Customer* user);
	virtual void view_published_movies(InputVec input_vector);
	virtual bool reply_comments(int film_id, int comment_id, std::string content);
	virtual bool delete_comment(int film_id, int comment_id);
	virtual void notify_followers(Message* message);
private:
	CustomersVector followers;
	MoviesVector published_movies;
	


};
#endif 

