#ifndef PERMISSIONDENIED_H
#define PERMISSIONDENIED_H

#include<exception>

class PermissionDenied :public std::exception {
public:
	virtual const char* what() const noexcept;
};
#endif 


