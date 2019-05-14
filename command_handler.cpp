#include"command_handler.h"
#include"Controller.h"

CommandHandler::CommandHandler() {
	
}

void CommandHandler::parse_input(std::string line) {
	std::istringstream is(line);
	std::string word;
	while (is >> word)
		input_line.push_back(word);
}

void CommandHandler::detect_command_type(std::vector<std::string> line) {
	controller = new Controller(line);
	std::string command = input_line[0];
	if (command.compare("POST"))
		controller->detect_POST_command();
	else if (command.compare("PUT"))
		controller->detect_PUT_command();
	else if (command.compare("GET")) 
		controller->detect_GET_command();
	else if (command.compare("DELETE"))
		controller->detect_DELETE_command();
	else
		throw BadRequest();
}