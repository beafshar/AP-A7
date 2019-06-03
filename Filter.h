#ifndef FILTER_H
#define FILTER_H

#include<iostream>
#include<string>
#define NOT_VALUED -1

class Movie;

class Filter {
public:
	Filter(std::string name);
	bool filter_by_director(Movie* film);

private:
	std::string director;
};


#endif
