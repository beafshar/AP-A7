#include"BadRequest.h"

const char* BadRequest::what() const noexcept {
	return "Bad Request\n";
}