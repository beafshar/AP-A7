#include"Recommender_System.h"
#include"Movie.h"

RecommenderSystem::RecommenderSystem() {
	recommender.resize(1);
	recommender[0].resize(1);
}

void RecommenderSystem::expand_matrix(Movie* movie) {
	
	for (int i = 0; i < recommender.size(); i++) {
		recommender[i].push_back(movie);
	}
	recommender.push_back(recommender[0]);
}

const MovieVec RecommenderSystem::recommend_movies(int film_id)const {
	MovieVec top_movies = recommender[film_id];
	top_movies.erase(top_movies.begin());
	std::sort(top_movies.begin(), top_movies.end(),Movie::compare_by_weight);
	return top_movies;
}
