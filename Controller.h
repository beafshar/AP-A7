#ifndef CONTROLLER_H
#define CONTROLLER_H

#include<vector>
#include<string>
#include"BadRequest.h"

class UTflix;

class Controller {
public:
	Controller(std::vector<std::string> line);
	void detect_POST_command();
	void detect_PUT_command();
	void detect_DELETE_command();
	void detect_GET_command();
	void detect_films_command();
	void detect_notifucation_command();

private:
	std::vector<std::string> input_line;
	UTflix* UT_flix;
};
#endif 
