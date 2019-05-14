#ifndef COMMENT_H
#define COMMENT_H

#include<string>

class Comment {
public:
	Comment(int id, std::string _content);
	int get_id();
	void delete_comment();

private:
	int user;
	std::string content;
	int comment_id;
	bool comment_deleted;
	bool get_replied_by_publisher;
	bool seen;
};
#endif 

