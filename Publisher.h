#ifndef PUBLISHER_H
#define PUBLISHER_H

#include"Customer.h"

class Movie;

class Publisher :public Customer {
public:
	Publisher(int id);
	virtual Movie* publish_films(Request* req, int id);
  /*

	virtual bool delete_film(int id);

	static bool compare_by_id(Customer* a, Customer* b);
	virtual bool if_follower_exists(int id);
	virtual float publisher_get_paid();

  */
	virtual std::string get_published_movies(std::string director_name);

private:
	CustomersVector followers;
	MoviesVector published_movies;
};
#endif
