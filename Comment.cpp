#include"Comment.h"

Comment::Comment(int id, std::string _content) {
	comment_id = id;
	content = _content;
	comment_deleted = false;
	get_replied_by_publisher = false;
	seen = false;
}

int Comment::get_id() {
	return comment_id;
}

void Comment::delete_comment() {
	comment_deleted = true;
}

