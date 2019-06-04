#include"Filter.h"
#include"Movie.h"
#include "UTflix.h"
#include"Recommender_System.h"
#include"Customer.h"
#include"Publisher.h"

std::string UTflix::view_movie_details(int id,int user_id) {
	int flag = 0;
  std::string body = "";
  body += set_movie_details_body();
		if (check_if_movie_existed(id)) {
			for (int i = 0; i < movies.size(); i++) {
				if (movies[i]->get_film_id() == id &&movies[i]->if_deleted() == false) {
					body += movies[i]->view_details();
					break;
				}
			}
		}
  body +="</table>"+ print_recommendation_films(id,user_id);
  return body;
}

std::string UTflix::print_recommendation_films(int id,int user_id) {
  std::string body = "";
	MoviesMap top_movies = recommender->recommend_movies(id);
	int count = 1;
	for (int i = 0; count < TOP4; i++) {
		if (i == top_movies.size())
			break;
		if (UTflix_users[user_id]->check_if_user_has_bought_movie(movies[top_movies[i].first]->
			get_film_id()) == false && movies[top_movies[i].first]->get_film_id() != id
			&& movies[top_movies[i].first]->if_deleted() == false) {
			 std::string code = movies[top_movies[i].first]->print_recommendation();
       body += code;
			count++;
		}
	}
  body += "</table></div></div></body></html>";
  return body;
}

std::string UTflix::set_movie_details_body(){
  std::string body = "";
  body += "<!DOCTYPE html> <html> <head> <style> body { font-family: \"Arial\";";
  body += "background-image: url(\"/film_detail\");background-attachment: fixed;background-size: cover;";
  body += "text-align: center;margin:0;}";
  body += "a:link:not(#film), a:visited:not(#film) {font-family: \"Arial\";";
  body += "background-color: rgb(255, 220, 147);color: black;padding: 30px 40px;" ;
  body += "  text-align: center;text-decoration: none;font-size: 16px;display: inline-block;" ;
  body += "bottom: 250px;left:100px;}";
  body += "a:hover:not(#film), a:active:not(#film) {background-color: red;"  ;
  body += "  bottom: 250px;left:100px;}";
  body += ".button {background-color: rgb(255, 220, 147);border: none;color: black;";
  body += "padding: 15px 32px;text-align: center;text-decoration: none;";
  body += "display: inline-block;font-size: 16px;margin: 4px 2px;cursor: pointer;}";
  body += ".button:hover {  background-color: red;}";
  body += ".logout_div{width: 10%;height: 50px;position:absolute;left:100px;top:230px;";
  body += "border-radius: 5px;display: inline-block;padding: 15px;margin : auto;}";
  body += ".profile_div{width: 10%;height: 50px;position:absolute;left:100px;";
  body += "top:400px;border-radius: 5px;display: inline-block;padding: 15px;margin : auto;}";
  body +=".table1_div{width: 50%;height: 120px;position:absolute;right:100px;top:60px;";
  body +="border-radius: 5px;display: inline-block;background-color: rgba(255, 220, 147,0.65);";
  body +="padding: 15px;margin : auto;}";
  body +=".table2_div{width: 50%;height: 250px;position:absolute;right:140px;top:200px;";
  body +="border-radius: 5px;display: inline-block;background-color: rgba(255, 220, 147,0.65);";
  body +="padding: 15px;margin : auto;}";
  body +="table {width:100%;}table, th, td {border: 1px ;border-collapse: collapse;}";
  body +="th, td {padding: 15px;text-align: left;}table#t01 th {background-color: rgb(255, 220, 147);";
  body += "color: black} </style></head><body>";
  body +="<div class=\"logout_div\"><a href=\"/loggedout\">Logout</a></div>";
  body +="<div class=\"profile_div\"><a href=\"/profile\">Profile</a></div>";
  body +="<div class=\"table1_div\"><table id=\"t01\"><tr>";
  body +="<th>Name</th><th>Rate</th><th>Price</th><th>Lenght</th><th>Year</th>";
  body +="<th>Director</th><th>Options</th></tr>";
  return body;
}

std::string Movie::view_details() {
  std::string body = "";
  body += "<tr><td><form action=\"/film_details\" method=\"get\">";
  body += "<button class=\"button\" name=\"film_id\"type=\"submit\"";
  body += "value="+ std::to_string(film_id)+ ">";
  body += movie_information["name"] + "</a> </td>";
  body += "<td>" + std::to_string(rate) + "</td>";
  body += "<td>" + movie_information["price"] + "</td>";
  body += "<td>" + movie_information["length"] + "</td>";
  body += "<td>" + movie_information["year"] + "</td>";
  body += "<td>" + movie_information["director"] + "</td>";
  body += "<td><form action=\"/buy_movie\" method=\"get\"><a id=\"film\" href=\"/buy_movie\"></a>";
  body += "<button class=\"button\" type=\"submit\"value=\"";
  body += std::to_string(film_id)+"\">"+"Buy</button></td></form>";
  body+= "</tr>"  ;
  return body;
}
std::string Movie::print_recommendation() {
	std::string body = "";
  body += "<div class=\"table2_div\"> <table id=\"t01\">  <tr>";
  body += "<th>Name</th>  <th>Lenght</th> <th>Director</th>  </tr>";
  body += "<tr><td><form action=\"/film_details\" method=\"get\">";
  body += "<button class=\"button\" name=\"film_id\"type=\"submit\"";
  body += "value="+ std::to_string(film_id)+ ">";
  body += movie_information["name"] + "</a> </td>";
  body += "<td>" + movie_information["length"] + "</td>";
  body += "<td>" + movie_information["director"] + "</td></tr>";
  return body;
}


std::string UTflix::publisher_views_his_published_movies(Request *req,int id) {
  std::string body = set_publisher_home_body();
  //std::string director = req->getBodyParam("director");
  std::string director = "";
  std::string code = publishers[id]->get_published_movies(director);
  body += code;
  return body;
}
std::string UTflix::set_publisher_home_body(){
  std::string body = "";
  body += "<!DOCTYPE html><html><head>";
  body += "<style>body {font-family: \"Arial\";";
  body += "background-image: url(\"/publisher\");background-attachment: fixed;";
  body += "background-size: cover;text-align: center;margin:0;}";
  body += "a:link:not(#film), a:visited:not(#film) {";
  body += "font-family: \"Arial\";background-color: rgb(61, 96, 56);";
  body += "color: white;padding: 30px 40px;";
  body += "text-align: center;text-decoration: none;font-size: 16px;";
  body += "display: inline-block;bottom: 250px;left:100px;}";
  body += "a:hover:not(#film), a:active:not(#film) {";
  body += "background-color: red;";
  body += "bottom: 250px;left:100px;}a#film {";
  body += "font-family: \"Arial\";color: white;text-align: center;";
  body += "text-decoration: none;font-size: 16px;display: inline-block;}";
  body += "hover#film, a:active#film, a:visited#film {";
  body += "color:red;text-decoration: underline;}";
  body += "input[type=text] {width: 100%;";
  body += "box-sizing: border-box;border: 2px solid #ccc;";
  body += "border-radius: 4px;font-size: 16px;";
  body += "background-color: white;background-image: url('/filter');";
  body += "background-size: 28px;background-position: 10px 10px;";
  body += "background-repeat: no-repeat;padding: 10px 10px 12px 40px;}";
  body += ".filter_div {width: 18%;position:absolute;";
  body += "left:280px;top:30px;border-radius: 5px;display: inline-block;";
  body += "background-color: rgba(61, 96, 56,0.65);padding: 15px;margin : auto;";
  body += "font-family: \"Arial\";font-size: 32px;color: white;}";
  body += ".button {background-color: rgb(61, 96, 56);";
  body += "border: none;color: white;padding: 15px 32px;";
  body += "text-align: center;text-decoration: none;display: inline-block;";
  body += "font-size: 16px;margin: 4px 2px;cursor: pointer;}";
  body += ".button:hover {background-color: red;}.logout_div{";
  body += "width: 10%;position:absolute;left:10px;top:350px;";
  body += "border-radius: 5px;display: inline-block;padding: 15px;margin : auto;}";
  body += ".films_div{width: 10%;position:absolute;left:10px;top:220px;";
  body += "border-radius: 5px;display: inline-block;padding: 15px;margin : auto;}";
  body += ".table1_div{width: 50%;position:absolute;";
  body += "right:20px;top:30px;border-radius: 5px;";
  body += "display: inline-block;background-color: rgba(61, 96, 56,0.65);";
  body += "padding: 15px;margin : auto;}table {width:100%;}";
  body += "table, th, td {border:1px ;border-collapse: collapse;}";
  body += "th, td {padding: 15px;text-align: left;}";
  body += "table#t01 th {background-color: rgb(61, 96, 56);color: white;}";
  body += "table#t01 td {color: white;}";
  body += "</style></head><body>";
  body += "<div class=\"filter_div\"><form action=\"/filter_movies\" method=\"post\">";
  body += "<input type=\"text\" name=\"director\" placeholder=\"Filter by director\">";
  body += "<button class=\"button\" type=\"submit\">Filter</button> <br></form>";
  body += "</div><div class=\"logout_div\"><a href=\"/loggedout\">Logout</a></div>";
  body += "<div class=\"films_div\"><a href=\"/publish_films\">Publish Films</a></div>";
  body += "<div class=\"table1_div\">";
  body += "<table id=\"t01\"><tr><th>Name</th><th>Rate</th><th>Price</th>";
  body += "<th>Lenght</th><th>Year</th><th>Director</th><th>Options</th></tr>";
  return body;
}

std::string Publisher::get_published_movies(std::string director_name) {
	int count = 1;
  std::string body = "";
	Filter* filter = new Filter(director_name);
	for (int i = 0; i < published_movies.size(); i++) {
		if (published_movies[i]->if_deleted() == false //&&
  /*filter->filter_by_director(published_movies[i])*/) {
			std::string code = published_movies[i]->view_published_details();
      body += code;
			count++;
      ////
      std::cout<<published_movies[i]->get_movie_name()<<std::endl;
      ////
		}

	}
  body += "</table></div></body></html>";
  return body;
}

std::string Movie::view_published_details() {
  std::string body = "";
  body += "";
  body += "<tr><td><form action=\"/film_details\" method=\"get\">";
  body += "<button class=\"button\" name=\"film_id\"type=\"submit\"";
  body += "value="+ std::to_string(film_id)+ ">";
  body += movie_information["name"] + "</a> </td>";
  body += "<td>" + std::to_string(rate) + "</td>";
  body += "<td>" + movie_information["price"] + "</td>";
  body += "<td>" + movie_information["length"] + "</td>";
  body += "<td>" + movie_information["year"] + "</td>";
  body += "<td>" + movie_information["director"] + "</td>";
  body += "<td><form action=\"/delete\" method=\"get\">";
  body += "<button class=\"button\" name=\"film_id\"type=\"submit\"value=";
  body += std::to_string(film_id)+">"+"Delete</button></td></form>";
  body+= "</tr>";
  return body;
}

std::string UTflix::user_views_available_movies(int id){
  std::string body = set_user_home_body();
  std::string director = "";
  Filter* filter = new Filter(director);
  for (int i = 0; i < movies.size(); i++) {
    if (movies[i]->if_deleted() == false && //filter->filter_by_director(movies[i]) &&
    movies[i]->get_price() <= UTflix_users[id]->get_money()){
        std::string code = movies[i]->view_details();
        body += code;
    }
  }
  body += "</table></div></body></html>";
  return body;
}
std::string UTflix::set_user_home_body(){
  std::string body = "";
  body += "<!DOCTYPE html><html><head>";
  body += "<style>body {font-family: \"Arial\";";
  body += "background-image: url(\"/publisher\");background-attachment: fixed;";
  body += "background-size: cover;text-align: center;margin:0;}";
  body += "a:link:not(#film), a:visited:not(#film) {";
  body += "font-family: \"Arial\";background-color: rgb(61, 96, 56);";
  body += "color: white;padding: 30px 40px;";
  body += "text-align: center;text-decoration: none;font-size: 16px;";
  body += "display: inline-block;bottom: 250px;left:100px;}";
  body += "a:hover:not(#film), a:active:not(#film) {";
  body += "background-color: red;";
  body += "bottom: 250px;left:100px;}a#film {";
  body += "font-family: \"Arial\";color: white;text-align: center;";
  body += "text-decoration: none;font-size: 16px;display: inline-block;}";
  body += "hover#film, a:active#film, a:visited#film {";
  body += "color:red;text-decoration: underline;}";
  body += "input[type=text] {width: 100%;";
  body += "box-sizing: border-box;border: 2px solid #ccc;";
  body += "border-radius: 4px;font-size: 16px;";
  body += "background-color: white;background-image: url('/filter');";
  body += "background-size: 28px;background-position: 10px 10px;";
  body += "background-repeat: no-repeat;padding: 10px 10px 12px 40px;}";
  body += ".filter_div {width: 18%;position:absolute;";
  body += "left:280px;top:30px;border-radius: 5px;display: inline-block;";
  body += "background-color: rgba(61, 96, 56,0.65);padding: 15px;margin : auto;";
  body += "font-family: \"Arial\";font-size: 32px;color: white;}";
  body += ".button {background-color: rgb(61, 96, 56);";
  body += "border: none;color: white;padding: 15px 32px;";
  body += "text-align: center;text-decoration: none;display: inline-block;";
  body += "font-size: 16px;margin: 4px 2px;cursor: pointer;}";
  body += ".button:hover {background-color: red;}.logout_div{";
  body += "width: 10%;position:absolute;left:10px;top:350px;";
  body += "border-radius: 5px;display: inline-block;padding: 15px;margin : auto;}";
  body += ".films_div{width: 10%;position:absolute;left:10px;top:220px;";
  body += "border-radius: 5px;display: inline-block;padding: 15px;margin : auto;}";
  body += ".table1_div{width: 50%;position:absolute;";
  body += "right:20px;top:30px;border-radius: 5px;";
  body += "display: inline-block;background-color: rgba(61, 96, 56,0.65);";
  body += "padding: 15px;margin : auto;}table {width:100%;}";
  body += "table, th, td {border:1px ;border-collapse: collapse;}";
  body += "th, td {padding: 15px;text-align: left;}";
  body += "table#t01 th {background-color: rgb(61, 96, 56);color: white;}";
  body += "table#t01 td {color: white;}";
  body += "</style></head><body>";
  body += "<div class=\"filter_div\"><form action=\"/filter_movies\" method=\"post\">";
  body += "<input type=\"text\" name=\"director\" placeholder=\"Filter by director\">";
  body += "<button class=\"button\" type=\"submit\">Filter</button> <br></form>";
  body += "</div><div class=\"logout_div\"><a href=\"/loggedout\">Logout</a></div>";
  body += "<div class=\"films_div\"><a href=\"/profile\">Profile</a></div>";
  body += "<div class=\"table1_div\">";
  body += "<table id=\"t01\"><tr><th>Name</th><th>Rate</th><th>Price</th>";
  body += "<th>Lenght</th><th>Year</th><th>Director</th><th>Options</th></tr>";
  return body;
}

std::string UTflix::user_views_bought_movies(int id) {
  std::string body = set_profile_body();
  //std::string director = req->getBodyParam("director");
  std::string director = "";
  std::string code = UTflix_users[id]->view_bought_movies(director);
  body += code;
  return body;
}


std::string Customer::view_bought_movies(std::string director_name) {
  std::string body = "";
  Filter* filter = new Filter(director_name);
  for (int i = 0; i < bought_movies.size(); i++) {
    if (bought_movies[i]->if_deleted() == false/* && filter->filter_by_director
    (bought_movies[i])*/){
        std::string code = bought_movies[i]->view_bought_details();
        body += code;
    }
  }
  body += "</table></div></body></html>";
  return body;
}

std::string UTflix::set_profile_body(){
  std::string body = "";
  body += "<!DOCTYPE html><html><head><style>body {font-family: \"Arial\";";
  body += "background-image: url(\"/publishFilmImage\");background-attachment: fixed;";
  body += "background-size: cover;text-align: center;margin:0;}";
  body += "a:link:not(#film), a:visited:not(#film) {font-family: \"Arial\";";
  body += "background-color: rgb(61, 96, 56);color: white;padding: 30px 40px;";
  body += "text-align: center;text-decoration: none;font-size: 16px;";
  body += "display: inline-block;bottom: 250px;left:100px;}";
  body += "a:hover:not(#film), a:active:not(#film) {";
  body += "background-color: red;bottom: 250px;left:100px;}";
  body += "a#film {font-family: \"Arial\";color: white;text-align: center;";
  body += "text-decoration: none;font-size: 16px;display: inline-block;}";
  body += "hover#film, a:active#film, a:visited#film {";
  body += "color:red;text-decoration: underline;}";
  body += "input[type=text]:not(#rate){width: 100%;box-sizing: border-box;";
  body += "border: 2px solid #ccc;border-radius: 4px;font-size: 16px;";
  body += "background-color: white;background-image: url('/filter');";
  body += "background-size: 28px;background-position: 10px 10px;";
  body += "background-repeat: no-repeat;padding: 10px 10px 12px 40px;}";
  body += "input[type=text]#rate {width: 20%;border: 2px solid #ccc;border-radius: 2px;";
  body += "font-size: 16px;background-color: white;padding: 2px 2px 5px 5px;}";
  body += ".filter_div {width: 18%;position:absolute;right:500px;";
  body += "top:30px;border-radius: 5px;display: inline-block;";
  body += "background-color: rgba(61, 96, 56,0.65);padding: 15px;";
  body += "margin : auto;font-family: \"Arial\";font-size: 32px;";
  body += "color: white;}.button:not(#rate) {background-color: rgb(61, 96, 56);";
  body += "border: none;color: white;padding: 15px 32px;";
  body += "text-align: center;text-decoration: none;display: inline-block;";
  body += "font-size: 16px;margin: 4px 2px;cursor: pointer;}";
  body += ".button:hover {background-color: red;}";
  body += ".button#rate {background-color: rgb(61, 96, 56);border: none;";
  body += "color: white;padding: 3px 15px;text-align: center;text-decoration: none;";
  body += "display: inline-block;font-size: 16px;margin: 4px 2px;cursor: pointer;}";
  body += ".button:hover#rate {background-color: red;}";
  body += ".logout_div{width: 10%;position:absolute;";
  body += "left:60px;top:280px;border-radius: 5px;display: inline-block;";
  body += "padding: 15px;margin : auto;}.films_div{width: 10%;";
  body += "position:absolute;left:60px;top:150px;border-radius: 5px;";
  body += "display: inline-block;padding: 15px;margin : auto;}.money_div {";
  body += "width: 18%;height: 100px;position: absolute;right: 80px;";
  body += "top: 30px;border-radius: 5px;display: inline-block;";
  body += "background-color: rgba(61, 96, 56,0.65);padding: 15px;margin: auto;}";
  body += ".table1_div{width: 50%;position:absolute;";
  body += "right:50px;top:200px;border-radius: 5px;";
  body += "display: inline-block;background-color: rgba(61, 96, 56,0.65);";
  body += "padding: 15px;margin : auto;}table {width:100%;}";
  body += "table, th, td {border: 1px ;border-collapse: collapse;}";
  body += "th, td {padding: 15px;text-align: left;}";
  body += "table#t01 th {background-color: rgb(61, 96, 56);color: white;}";
  body += "table#t01 td {color: white;}</style></head><body>";
  body += "<div class=\"money_div\"><form action=\"/increase_money\" method=\"get\">";
  body += "<input type=\"text\" name=\"amount\" placeholder=\"Increase money\">";
  body += "<button class=\"button\" type=\"submit\">Charge</button> <br>";
  body += "</form></div><div class=\"filter_div\"><form action=\"/filter_movies\" method=\"get\">";
  body += "<input type=\"text\" name=\"director\" placeholder=\"Filter by director\">";
  body += "<button class=\"button\" type=\"submit\">Filter</button> <br></form>";
  body += "</div><div class=\"logout_div\"><a href=\"/loggedout\">Logout</a></div>";
  body += "<div class=\"films_div\"><a href=\"/userhome\">Home</a></div>";
  body += "<div class=\"table1_div\"><table id=\"t01\"><tr>";
  body += "<th>Name</th><th>Rate</th><th>Price</th><th>Lenght</th>";
  body += "<th>Year</th><th>Director</th><th>Options</th></tr>";
  return body;
}

std::string Movie::view_bought_details() {
  std::string body = "";
  body += "";
  body += "<tr><td><form action=\"/film_details\" method=\"get\">";
  body += "<button class=\"button\" name=\"film_id\"type=\"submit\"";
  body += "value="+ std::to_string(film_id)+ ">";
  body += movie_information["name"] + "</a> </td>";
  body += "<td>" + std::to_string(rate) + "</td>";
  body += "<td>" + movie_information["price"] + "</td>";
  body += "<td>" + movie_information["length"] + "</td>";
  body += "<td>" + movie_information["year"] + "</td>";
  body += "<td>" + movie_information["director"] + "</td>";
  body += "<td><form action=\"/rate\" method=\"get\"><input id=\"rate\" type=\"text\" name=\"score\">";
  body += "<button id=\"rate\" class=\"button\" type=\"submit\"value=\"";
  body += std::to_string(film_id)+"\">"+"Rate</button></form></td>";
  body+= "</tr>";
  return body;
}
