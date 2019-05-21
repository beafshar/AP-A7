#include"Filter.h"
#include"Movie.h"

Filter::Filter(InputVec input) {
	name = std::to_string(NOT_VALUED);
	director = std::to_string(NOT_VALUED);
	max_year = NOT_VALUED;
	min_year = NOT_VALUED;
	price = NOT_VALUED;
	min_rate = NOT_VALUED;
	parse_filtering_items(input);
}

void Filter::parse_filtering_items(InputVec input) {
	name = find_needed(input, "name");
	director = find_needed(input, "director");
	max_year = std::stoi(find_needed(input, "max_year"));
	min_year = std::stoi(find_needed(input, "min_year"));
	price = std::stof(find_needed(input, "price"));
	min_rate = std::stof(find_needed(input, "min_rate"));
}

std::string Filter::find_needed(InputVec input, std::string need) {
	for (int i = 0; i < input.size() - 1; i++) {
		if (input[i].compare(need) == 0)
			return input[i + 1];
	}
	return std::to_string(NOT_VALUED);
}

bool Filter::filter_by_price(Movie* film) {
	if (price == NOT_VALUED)
		return true;
	if (film->get_price() == price)
		return true;
	else
		return false;
}

bool Filter::filter_by_name(Movie* film) {
	if (name == std::to_string(NOT_VALUED))
		return true;
	if (film->get_movie_name() == name)
		return true;
	else
		return false;
}
bool Filter::filter_by_director(Movie* film) {
	if (director == std::to_string(NOT_VALUED))
		return true;
	if (film->get_director() == director)
		return true;
	else
		return false;
}

bool Filter::filter_by_min_rate(Movie* film) {
	if (min_rate == NOT_VALUED)
		return true;
	if (film->get_rate() > min_rate)
		return true;
	else
		return false;
}
bool Filter::filter_by_min_year(Movie* film) {
	if (min_year == NOT_VALUED)
		return true;
	if (film->get_year() >= min_year)
		return true;
	else
		return false;
}
bool Filter::filter_by_max_year(Movie* film) {
	if (max_year == NOT_VALUED)
		return true;
	if (film->get_year() <= max_year)
		return true;
	else
		return false;
}
