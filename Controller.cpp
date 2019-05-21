#include"Controller.h"
#include"UTflix.h"

Controller::Controller() {
	UT_flix = new UTflix();
}

void Controller::set_input(InputVec input) {
	input_line = input;
}

void Controller::detect_DELETE_command() {
	try {
		std::string command = input_line[1];
		if (command.compare("films") == 0)
			UT_flix->delete_movie(input_line);
		else if (command.compare("comments") == 0)
			UT_flix->delete_comment(input_line);
		else
			throw NotFound();
		input_line.resize(0);
	}
	catch (const std::exception& exp) {
		std::cout << exp.what();
	}

}

void Controller::detect_GET_command() {
	try {
		std::string command = input_line[1];
		if (command.compare("followers") == 0)
			UT_flix->get_followers_list();
		else if (command.compare("published") == 0)
			UT_flix->publisher_views_his_published_movies(input_line);
		else if (command.compare("films") == 0)
			detect_films_command();
		else if (command.compare("purchased") == 0)
			UT_flix->user_views_his_bought_movies(input_line);
		else if (command.compare("notifications") == 0)
			detect_notifucation_command();
		else
			throw NotFound();
		input_line.resize(0);
	}
	catch (const std::exception& exp) {
		std::cout << exp.what();
	}
}

void Controller::detect_PUT_command() {
	try {
		std::string command = input_line[1];
		if (command.compare("films") == 0)
			UT_flix->edit_movie(input_line);
		else
			throw NotFound();
		input_line.resize(0);
	}
	catch (const std::exception& exp) {
		std::cout << exp.what();
	}
}

void Controller::detect_POST_command() {
	try {
		std::string command = input_line[1];
		if (command.compare("signup") == 0)
			UT_flix->signup(input_line);
		else if (command.compare("login") == 0)
			UT_flix->login(input_line);
		else if (command.compare("films") == 0)
			UT_flix->upload_films(input_line);
		else if (command.compare("money") == 0)
			detect_money_command();
		else if (command.compare("replies") == 0)
			UT_flix->reply_comment(input_line);
		else if (command.compare("followers") == 0)
			UT_flix->follow_publisher(input_line);
		else if (command.compare("money") == 0)
			UT_flix->increase_user_money(input_line);
		else if (command.compare("buy") == 0)
			UT_flix->buy_movie(input_line);
		else if (command.compare("rate") == 0)
			UT_flix->rate_movie(input_line);
		else if (command.compare("comments") == 0)
			UT_flix->comment_on_films(input_line);
		else
			throw NotFound();
		input_line.resize(0);
	}
	catch (const std::exception& exp) {
			std::cout << exp.what();
		}
}

void Controller::detect_films_command() {
	if (input_line.size() == 2 || input_line.size() >= 3 && input_line[3] != "film_id")
		UT_flix->user_search_movies(input_line);
	else if(input_line[3].compare("film_id") == 0)
		UT_flix->view_movie_details(input_line[4]);
	else
		throw BadRequest();
}

void Controller::detect_notifucation_command() {
	if (input_line.size() == 2 || input_line.size() == 3)
		UT_flix->view_unread_notification();
	else if (input_line[2].compare("read") == 0)
		UT_flix->view_all_notification(input_line);
	
	else
		throw BadRequest();
}

void Controller::detect_money_command() {
	if (input_line.size() == 2 || input_line.size() == 3)
		UT_flix->pay_to_publisher();
	else if (input_line[3].compare("amount") == 0)
		UT_flix->increase_user_money(input_line);
	else
		throw BadRequest();
}