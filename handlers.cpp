#include "handlers.hpp"
#include "UTflix.h"

using namespace std;

Response *HomeHandler::callback(Request *req) {
  int user_id = stoi(req->getSessionId());
  Response *res = new Response();
  if(UT_flix->get_user_type(user_id) == USER_PUBLISHER)
    res = Response::redirect("/publisherhome");
  else
    res = Response::redirect("/userhome");
  return res;
}
Response *LoginHandler::callback(Request *req) {
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  string id = to_string(UT_flix->login(username,password));
  Response *res = new Response;
  res->setSessionId(id);
  res = Response::redirect("/home");
  return res;
}

Response *SignupHandler::callback(Request *req) {
  string id = to_string(UT_flix->signup(req));
  Response *res = new Response;
  res = Response::redirect("/home");
  res->setSessionId(id);
  return res;
}

Response *LogoutHandler::callback(Request *req) {
  Response *res = Response::redirect("/loggedout");
  res->setSessionId(DEFAULT_SESSION_ID);
  return res;
}
Response *PublishFilmsHandler::callback(Request *req) {
  int user_id = stoi(req->getSessionId());
  UT_flix->upload_films(req,user_id);
  Response *res = Response::redirect("/publisherhome");
  return res;
}
Response *DeleteFilmsHandler::callback(Request *req) {
  string film_id = req->getQueryParam("film_id");
  int user_id = stoi(req->getSessionId());
  UT_flix->delete_movie(film_id, user_id);
  Response *res = Response::redirect("/publisherhome");
  return res;
}
Response *RateFilmHandler::callback(Request *req) {
  string film_id = req->getQueryParam("film_id");
  string score = req->getQueryParam("score");
  int user_id = stoi(req->getSessionId());
  UT_flix->rate_movie(film_id, score, user_id);
  Response *res = Response::redirect("/userhome");
  return res;
}
Response *BuyFilmHandler::callback(Request *req) {
  string film_id = req->getQueryParam("film_id");
  int user_id = stoi(req->getSessionId());
  UT_flix->buy_movie(film_id, user_id);
  Response *res = Response::redirect("/userhome");
  return res;
}
Response *FilmDetailsHandler::callback(Request *req) {
  int film_id = stoi(req->getQueryParam("film_id"));
  int user_id = stoi(req->getSessionId());
  Response *res = new Response;
  res->setHeader("Content-Type","text/html");
  res->setBody(UT_flix->view_movie_details(film_id,user_id));
  return res;

}
Response *IncreaseMoneyHandler::callback(Request *req) {
  std::string amount = req->getQueryParam("amount");
  int user_id = stoi(req->getSessionId());
  UT_flix->increase_user_money(amount, user_id);
  Response *res = Response::redirect("/userhome");
  return res;
}

Response *PublisherHandler::callback(Request *req) {
  int user_id = stoi(req->getSessionId());
  Response *res = new Response();
  res->setHeader("Content-Type","text/html");
  res->setBody(UT_flix->publisher_views_his_published_movies(req,user_id));
  return res;
}
Response *UserHandler::callback(Request *req) {
  int user_id = stoi(req->getSessionId());
  Response *res = new Response();
  res->setHeader("Content-Type","text/html");
  res->setBody(UT_flix->user_views_available_movies(req,user_id));
  return res;
}
Response *ProfileHandler::callback(Request *req) {
  int user_id = stoi(req->getSessionId());
  Response *res = new Response();
  res->setHeader("Content-Type","text/html");
  res->setBody(UT_flix->user_views_bought_movies(req,user_id));
  return res;
}
Response *CommentHandler::callback(Request *req) {
  int film_id = stoi(req->getQueryParam("film_id"));
  string content = req->getQueryParam("content");
  int user_id = stoi(req->getSessionId());
  UT_flix->comment_on_films(user_id,film_id, content);
  Response *res = Response::redirect("/userhome");
  return res;
}

Response *FilterHandler::callback(Request *req) {
  Response *res = Response::redirect("/home");
  return res;
}
