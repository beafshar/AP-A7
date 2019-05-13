#ifndef BADREQUEST_H
#define BADREQUEST_H

#include<exception>

class BadRequest :public std::exception {
public:
	virtual const char* what() const noexcept;
};
#endif 

