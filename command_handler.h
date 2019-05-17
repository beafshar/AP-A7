#ifndef COMMAND_HANDLER
#define COMMAND_HANDLER

#include<string>
#include<iostream>
#include<vector>
#include<exception>
#include"BadRequest.h"
#include<sstream>

class Controller;

class CommandHandler {
public:
	CommandHandler();
	void run();
	void parse_input(std::string line);
	void detect_command_type(std::vector<std::string> line);

private:
	Controller* controller;
	std::vector<std::string> input_line;
};
#endif 
