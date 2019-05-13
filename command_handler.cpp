#include"command_handler.h"
#include"Controller.h"

CommandHandler::CommandHandler() {
	
}

//in irad dare

void CommandHandler::parse_input(std::string line) {
	int lenght = 0;
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == ' ' && lenght != 0) {
			std::string temp = line.substr(i-lenght, i-1);
			input_line.push_back(temp);
			lenght = 0;
			continue;
		}
		lenght++;
		
		
	}
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