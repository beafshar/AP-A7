#include"Comment.h"

Comment::Comment(int id, std::string _content) : Message(_content, false){
	comment_id = id;
	comment_deleted = false;
	get_replied_by_publisher = false;

}

int Comment::get_id() {
	return comment_id;
}

void Comment::delete_comment() {
	comment_deleted = true;
}

void Comment::reply(std::string content) {
	replies.push_back(content);
}

void Comment::print_replies() {
	for (int i = 0; i < replies.size(); i++) {
		std::cout << comment_id << "." << i + 1 << ". ";
		std::cout << replies[i] << std::endl;
	}
}