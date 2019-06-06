#include "handlers.hpp"
#include "UTflix.h"
#include<exception>

using namespace std;

Response *HomeHandler::callback(Request *req) {
  int user_id = stoi(req->getSessionId());
  Response *res = new Response();
  if(UT_flix->get_user_type(user_id) == USER_PUBLISHER)
    res = Response::redirect("/publisherhome");
  else if(UT_flix->get_user_type(user_id) == USER_CUSTOMER)
    res = Response::redirect("/userhome");
  else
    res = Response::redirect("/error_page");
  return res;
}
Response *LoginHandler::callback(Request *req) {
  Response *res = new Response();
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  try{
    string id = to_string(UT_flix->login(username,password));
    res = Response::redirect("/home");
    res->setSessionId(id);
  }
  catch(const std::exception& exp){
    res->setHeader("Content-Type","text/html");
    res->setBody(readFile("htmlFiles/wrong_password.html"));
  }
  return res;
}

Response *SignupHandler::callback(Request *req) {
  Response *res = new Response();
  try{
    string id = to_string(UT_flix->signup(req));
    res = Response::redirect("/home");
    res->setSessionId(id);
    return res;
  }
  catch(const std::exception& exp){
     res->setHeader("Content-Type","text/html");
     res->setBody(readFile("htmlFiles/not_match.html"));
     return res;
   }
}

Response *LogoutHandler::callback(Request *req) {
  Response *res = Response::redirect("/loggedout");
  res->setSessionId(DEFAULT_SESSION_ID);
  return res;
}
Response *PublishFilmsHandler::callback(Request *req) {
  int user_id = stoi(req->getSessionId());
  Response *res = new Response();
  try{
    UT_flix->upload_films(req,user_id);
    res = Response::redirect("/publisherhome");
  }
  catch(const std::exception& exp){
    res = Response::redirect("/error_page");
  }
  return res;
}
Response *DeleteFilmsHandler::callback(Request *req) {
  string film_id = req->getQueryParam("film_id");
  int user_id = stoi(req->getSessionId());
  Response *res = new Response();
  try{
    UT_flix->delete_movie(film_id, user_id);
    res = Response::redirect("/publisherhome");
  }
  catch(const std::exception& exp){
    res = Response::redirect("/error_page");
  }
  return res;
}
Response *RateFilmHandler::callback(Request *req) {
  string film_id = req->getQueryParam("film_id");
  string score = req->getQueryParam("score");
  int user_id = stoi(req->getSessionId());
  Response *res = new Response();
  try{
  UT_flix->rate_movie(film_id, score, user_id);
  res = Response::redirect("/userhome");
  }
  catch(const std::exception& exp){
    res = Response::redirect("/error_page");
  }
  return res;
}
Response *BuyFilmHandler::callback(Request *req) {
  string film_id = req->getQueryParam("film_id");
  int user_id = stoi(req->getSessionId());
  Response *res = new Response();
  try{
  UT_flix->buy_movie(film_id, user_id);
    res = Response::redirect("/userhome");
  }
  catch(const std::exception& exp){
    res = Response::redirect("/error_page");
  }
  return res;
}
Response *FilmDetailsHandler::callback(Request *req) {
  int film_id = stoi(req->getQueryParam("film_id"));
  int user_id = stoi(req->getSessionId());
  Response *res = new Response();
  res->setHeader("Content-Type","text/html");
  res->setBody(UT_flix->view_movie_details(film_id,user_id));
  return res;

}
Response *IncreaseMoneyHandler::callback(Request *req) {
  std::string amount = req->getQueryParam("amount");
  int user_id = stoi(req->getSessionId());
  Response *res = new Response();
  try{
  UT_flix->increase_user_money(amount, user_id);
    res = Response::redirect("/userhome");
  }
  catch(const std::exception& exp){
    res = Response::redirect("/error_page");
  }
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
  Response *res = new Response();
  try{
  UT_flix->comment_on_films(user_id,film_id, content);
    res = Response::redirect("/userhome");
  }
  catch(const std::exception& exp){
    res = Response::redirect("/error_page");
  }
  return res;
}

Response *FilterHandler::callback(Request *req) {
  Response *res = Response::redirect("/home");
  return res;
}
