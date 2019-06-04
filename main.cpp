#include "handlers.hpp"
#include "my_server.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  srand(time(NULL));
  try {
    MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
    server.get("/home_image", new ShowImage("htmlFiles/home_image.jpg"));
    server.get("/signup", new ShowImage("htmlFiles/signup.jpg"));
    server.get("/loggedout_image", new ShowImage("htmlFiles/loggedout_image.jpg"));
    server.get("/error", new ShowImage("htmlFiles/loggedin_image.jpg"));
    server.get("/publisher", new ShowImage("htmlFiles/publisher.jpg"));
    server.get("/money", new ShowImage("htmlFiles/money.png"));
    server.get("/filter", new ShowImage("htmlFiles/filter.png"));
    server.get("/publishFilmImage", new ShowImage("htmlFiles/publishFilmImage.jpg"));
    server.get("/404", new ShowImage("htmlFiles/404.jpg"));
    server.get("/film_detail", new ShowImage("htmlFiles/film_details.jpg"));

    server.setNotFoundErrPage("htmlFiles/404.html");
    server.get("/error_page", new ShowPage("htmlFiles/PermissionDenied.html"));
    server.get("/", new ShowPage("htmlFiles/firstPage.html"));
    server.get("/home", new HomeHandler());
    server.get("/userhome", new UserHandler());
    server.get("/profile", new ProfileHandler());
    server.get("/publisherhome", new PublisherHandler());
    server.get("/rate", new RateFilmHandler());
    server.get("/buy_movie", new BuyFilmHandler());
    server.get("/delete_film", new DeleteFilmsHandler());
    server.get("/increase_money", new IncreaseMoneyHandler());
    server.get("/signup_page", new ShowPage("htmlFiles/signup.html"));
    server.post("/signup", new SignupHandler());
    server.get("/login_page", new ShowPage("htmlFiles/login.html"));
    server.post("/login", new LoginHandler());
    server.get("/loggedout", new ShowPage("htmlFiles/loggedout.html"));
    server.get("/loggedin", new ShowPage("htmlFiles/loggedin.html"));
    server.get("/publish_films", new ShowPage("htmlFiles/publish_films.html"));
    server.post("/publish_films", new PublishFilmsHandler());
    server.get("/film_details", new FilmDetailsHandler());
    server.get("/filter_movies", new FilterHandler());
    server.get("/comment", new CommentHandler());
    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
}
