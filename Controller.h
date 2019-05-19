#ifndef CONTROLLER_H
#define CONTROLLER_H

#include<vector>
#include<string>
#include"BadRequest.h"
#include"NotFound.h"

class UTflix;

typedef std::vector<std::string> InputVec;

class Controller {
public:
	Controller();
	void set_input(InputVec line);
	void detect_POST_command();
	void detect_PUT_command();
	void detect_DELETE_command();
	void detect_GET_command();
	void detect_films_command();
	void detect_notifucation_command();

private:
	InputVec input_line;
	UTflix* UT_flix;
};
#endif 
