#ifndef PUBLISHER_H
#define PUBLISHER_H

#include"Customer.h"

class Movie;

class Publisher :public Customer {
public:
	Publisher(int id);
	bool publish_films(InputVec input_vector);
	bool edit_film_information(InputVec input_vector);
	bool delete_film(int id);
	void get_followers_list();
	bool compare_by_id(User* a, User* b);
	void add_followers(User* user);


private:
	UsersVector followers;
	MoviesVector published_movies;
	


};
#endif 

