#include"Controller.h"
#include"UTflix.h"

Controller::Controller() {
	UT_flix = new UTflix();
}

void Controller::set_input(InputVec input) {
	input_line = input;
}

void Controller::detect_DELETE_command() {
	std::string command = input_line[1];
	if (command.compare("films") == 0)
	{}
		//publisher.delete
	else if(command.compare("comments") == 0)
	{}
		//publisher.dlete comment
	else
		throw BadRequest();
	input_line.resize(0);

}

void Controller::detect_GET_command() {
	std::string command = input_line[1];
	if (command.compare("followers") == 0) {
		//publisher . see followers
	}
	else if (command.compare("published") == 0) {
		//publisher. see published films
	}
	else if (command.compare("films") == 0) {
		//customer . search films or film details
	}
	else if (command.compare("purchased") == 0) {
		//customer. bougth films
	}
	else if (command.compare("notification") == 0)
		detect_notifucation_command();
	else
		throw BadRequest();
	input_line.resize(0);
}

void Controller::detect_PUT_command() {
	std::string command = input_line[2];
	if (command.compare("films") == 0) {
		// publisher put his films
	}
	else
		throw BadRequest();
	input_line.resize(0);
}

void Controller::detect_POST_command() {
	std::string command = input_line[1];
	if (command.compare("signup") == 0)
		UT_flix->signup(input_line);
	else if (command.compare("login") == 0)
		UT_flix->login(input_line);
	else if (command.compare("films") == 0) {
		//publisher. upload film
	}
	else if (command.compare("money") == 0) {
		//publisher get money
	}
	else if (command.compare("replies") == 0) {
		//publisher reply comments
	}
	else if (command.compare("followers") == 0) {
		//customer follows publisher
	}
	else if (command.compare("money") == 0) {
		//customers charges account
	}
	else if (command.compare("buy") == 0) {
		//customer buys film
	}
	else if (command.compare("rate") == 0) {
		//customrs rate movies
	}
	else if (command.compare("comments") == 0) {
		//customer comments on movie
	}
	else
		throw BadRequest();
	input_line.resize(0);
}

void Controller::detect_films_command() {
	//std::string command = input_line[2];
	//if(command.compare(""))
}

void Controller::detect_notifucation_command() {
	std::string command = input_line[2];
	if (command.compare("read") == 0) {
		//customers reads all notifs
	}
	else if (command.compare("?") == 0) {
		//customers wants new massages
	}
	else
		throw BadRequest();
}