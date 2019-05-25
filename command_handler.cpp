#include"command_handler.h"
#include"Controller.h"

CommandHandler::CommandHandler() {
	controller = new Controller();
}

void CommandHandler::parse_input(std::string line) {
	if (line.compare("") == 0)
		return;
	std::istringstream is(line);
	std::string word;
	while (is >> word)
		input_line.push_back(word);
}

void CommandHandler::detect_command_type() {
	if (input_line.size() == 0)
		return;
	controller->set_input(input_line);
	std::string command = input_line[0];
	if (input_line.size() > 1) {
		if (command.compare("POST") == 0)
			controller->detect_POST_command();
		else if (command.compare("GET") == 0)
			controller->detect_GET_command();
		else
			throw BadRequest();
	}
	else
		throw BadRequest();
}

void CommandHandler::run() {
	std::string line;
	while (std::getline(std::cin, line)) {
		try {
			parse_input(line);
			detect_command_type();
			input_line.resize(0);
		}
		catch (const std::exception& exp) {
			std::cout << exp.what();
		}
	}
}