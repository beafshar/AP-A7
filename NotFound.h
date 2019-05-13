#ifndef NOTFOUND_H
#define NOTFOUND_H

#include<exception>

class NotFound :public std::exception {
public:
	virtual const char* what() const noexcept;
};
#endif 


