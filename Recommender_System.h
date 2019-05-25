#ifndef RECOMMENDER_H
#define RECOMMENDER_H

#include<vector>
#include<map>
class Movie;
typedef std::vector<int> MoviesVec;
typedef std::vector<std::vector<int>> Matrix;
typedef std::vector<std::pair<int, int>> MoviesMap;
typedef std::pair<int, int> MyPair;

class RecommenderSystem {
public:
	RecommenderSystem();
	void expand_matrix();
	void fill_matrix(int film_id,int bought_movie_id);
	MoviesMap recommend_movies(int film_id) ;
	MoviesMap make_map(MoviesVec top_movies);
	static bool compare_by_weight(MyPair a, MyPair b);

private:
	Matrix recommender;
};

#endif 

