#ifndef RECOMMENDER_H
#define RECOMMENDER_H

#include<vector>
class Movie;
typedef std::vector<Movie*> MovieVec;
typedef std::vector<MovieVec> Matrix;

class RecommenderSystem {
public:
	RecommenderSystem();
	void expand_matrix(Movie* movie);
	const MovieVec recommend_movies(int film_id) const;
private:
	Matrix recommender;
};

#endif 

