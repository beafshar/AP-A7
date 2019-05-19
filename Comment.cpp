#include"Comment.h"

Comment::Comment(int id, std::string _content, int user_id, int _movie_id) : Message(_content){
	comment_id = id;
	movie_id = _movie_id;
	user = user_id;
	comment_deleted = false;
	get_replied_by_publisher = false;
}

int Comment::get_user() {
	return user;
}

bool Comment::check_if_deleted() {
	return comment_deleted;
}

int Comment::get_id() {
	return comment_id;
}

void Comment::delete_comment() {
	comment_deleted = true;
}

void Comment::reply(std::string content) {
	get_replied_by_publisher = true;
	replies.push_back(content);
}

void Comment::print_replies() {
	for (int i = 0; i < replies.size(); i++) {
		std::cout << comment_id << "." << i + 1 << ". ";
		std::cout << replies[i] << std::endl;
	}
}