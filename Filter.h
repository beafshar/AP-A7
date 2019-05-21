#ifndef FILTER_H
#define FILTER_H

#include<vector>
#include<iostream>
#include<map>
#include<string>
#define NOT_VALUED -1


class Movie;

typedef std::map<std::string, std::string> InformationMAP;
typedef std::vector<Movie*> MoviesVector;
typedef std::vector<std::string> InputVec;

class Filter {
public:
	Filter(InputVec input);
	void parse_filtering_items(InputVec input);
	std::string find_needed(InputVec input, std::string need);
	bool filter_by_price(Movie* film);
	bool filter_by_name(Movie* film);
	bool filter_by_min_year(Movie* film);
	bool filter_by_max_year(Movie* film);
	bool filter_by_director(Movie* film);
	bool filter_by_min_rate(Movie* film);
	

private:
	std::string name;
	float price;
	int min_year;
	int max_year;
	std::string director;
	float min_rate;

};


#endif