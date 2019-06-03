#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#define DEFAULT_SESSION_ID "-1"
#define USER_PUBLISHER 1
#define USER_CUSTOMER 2
#include "../server/server.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include"Controller.h"

class UserHandler : public Controller {
public:
  Response *callback(Request *);
};
class ProfileHandler : public Controller {
public:
  Response *callback(Request *);
};
class PublisherHandler : public Controller {
public:
  Response *callback(Request *);
};
class LoginHandler : public Controller {
public:
  Response *callback(Request *);
};
class SignupHandler : public Controller {
public:
  Response *callback(Request *);
};
class LogoutHandler : public Controller {
public:
  Response *callback(Request *);
};
class PublishFilmsHandler : public Controller {
public:
  Response *callback(Request *);
};
class DeleteFilmsHandler : public Controller {
public:
  Response *callback(Request *);
};
class RateFilmHandler : public Controller {
public:
  Response *callback(Request *);
};
class BuyFilmHandler : public Controller {
public:
  Response *callback(Request *);
};
class FilmDetailsHandler : public Controller {
public:
  Response *callback(Request *);
};
class IncreaseMoneyHandler : public Controller {
public:
  Response *callback(Request *);
};
#endif
