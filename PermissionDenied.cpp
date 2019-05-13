#include"PermissionDenied.h"

const char* PermissionDenied::what() const noexcept {
	return "Permission Denied\n";
}