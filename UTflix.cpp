#include"UTflix.h"



UTflix::UTflix() {

}

void UTflix::run() {
	std::string line;
	CommandHandler command_handler = CommandHandler();
	while (std::getline(std::cin, line)) {
		command_handler.parse_input(line);
	}
}