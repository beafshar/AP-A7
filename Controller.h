#ifndef CONTROLLER_H
#define CONTROLLER_H

#include<vector>
#include<string>
#include"BadRequest.h"
#include"NotFound.h"
#include "../server/server.hpp"

class UTflix;

class Controller :public RequestHandler {
public:
  Controller();

protected:
	UTflix* UT_flix;
};
#endif
