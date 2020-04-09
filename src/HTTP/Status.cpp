#include "Status.h"

std::string get_status_code_description(StatusCode code) {
	switch (code) {
		case StatusCode::I100:
			return "100 Continue";
		case StatusCode::I101:
			return "101 Switching Protocols";
		case StatusCode::I102:
			return "102 Processing";
		case StatusCode::S200:
			return "200 OK";

		case StatusCode::CE405:
			return "405 Method Not Allowed";
// Todo: дописать коды)
		default:
			return "";
	}
}


