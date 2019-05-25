#include"Recommender_System.h"
#include"Movie.h"

RecommenderSystem::RecommenderSystem() {
	recommender.resize(1);
	recommender[0].resize(1);
}

void RecommenderSystem::expand_matrix() {
	
	for (int i = 0; i < recommender.size(); i++) {
		recommender[i].push_back(0);
	}
	recommender.push_back(recommender[0]);
}

MoviesMap RecommenderSystem::recommend_movies(int film_id) {

	MoviesVec top_movies = recommender[film_id];
	top_movies.erase(top_movies.begin());

	return make_map(top_movies);
}

void RecommenderSystem::fill_matrix(int film_id1, int film_id2) {
	recommender[film_id1][film_id2]++;
	for (int i = 1; i < recommender.size(); i++) {
		for (int j = 1; j < recommender[i].size(); j++) {
			recommender[i][i] = 0;
			recommender[i][j] = recommender[j][i];
		}
	}
}

MoviesMap RecommenderSystem::make_map(MoviesVec top_movies) {
	MoviesMap map;
	for (int i = 0; i < top_movies.size(); i++) {
		map.push_back(std::pair<int, int>(i, top_movies[i]));
	}
	std::sort(map.begin(), map.end(), RecommenderSystem::compare_by_weight);
	return map;
}

bool RecommenderSystem::compare_by_weight(MyPair a, MyPair b) {
	return a.second > b.second;
}