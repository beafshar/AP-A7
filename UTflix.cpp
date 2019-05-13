#include"UTflix.h"



UTflix::UTflix() {

}

void UTflix::run() {
	std::string line;
	std::getline(std::cin,line);
	CommandHandler command_handler = CommandHandler();
	command_handler.parse_input(line);
}