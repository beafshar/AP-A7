#include"Filter.h"
#include"Movie.h"

Filter::Filter(std::string name) {
	if(name.compare("")==0)
	 director = std::to_string(NOT_VALUED);
	director = name;
}

bool Filter::filter_by_director(Movie* film) {
	if (director == std::to_string(NOT_VALUED))
		return true;
	if (film->get_director() == director)
		return true;
	else
		return false;
}
