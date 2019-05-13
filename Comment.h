#ifndef COMMENT_H
#define COMMENT_H

#include<string>

class Comment {
public:

private:
	std::string content;
	int comment_id;
	bool comment_deleted;
	bool get_replied_by_publisher;
	bool seen;
};
#endif 

