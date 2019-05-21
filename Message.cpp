#include"Message.h"

Message:: Message(std::string _content){
	seen = false;
	content = _content;
}

void Message::read_message() {
	seen = true;
}

std::string Message::get_content() {
	return content;
}

bool Message::if_read() {
	return seen;
}

void Message:: create_reply_notif(std::string publisher_name, int id) {
	content = "Publisher " + publisher_name + " with id "
		+ std::to_string(id) + " reply to your comment.";

}


void Message:: create_publish_film_notif(std::string publisher_name, int id) {
	content = "Publisher " + publisher_name + " with id "
		+ std::to_string(id) + " register new film.";

}


void Message:: create_follow_notif(std::string user_name, int id) {
	content = "User " + user_name + " with id "+ std::to_string(id)
		+ " follow you.";
}


void Message:: create_buy_film_notif(std::string user_name, int user_id,
	std::string film, int film_id) {
	content = "User " + user_name + " with id " + std::to_string(user_id)
		+ " buy your film " + film + " with id " + std::to_string(film_id) + ".";
}


void Message:: create_rate_film_notif(std::string user_name, int user_id,
	std::string film, int film_id) {
	content = "User " + user_name + " with id " + std::to_string(user_id)
		+ " rate your film " + film + " with id " + std::to_string(film_id) + ".";
}

void Message:: create_comment_film_notif(std::string user_name, int user_id,
	std::string film, int film_id) {
	content = "User " + user_name + " with id " + std::to_string(user_id)
		+ " comment on your film " + film + " with id " + std::to_string(film_id)
		+ ".";
}

