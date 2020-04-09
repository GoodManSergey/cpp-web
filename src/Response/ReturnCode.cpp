#include "ReturnCode.h"

std::string ReturnCode::get_description(Code code) {
	switch (code) {
		case Code::I100:
			return "100 Continue";
		case Code::I101:
			return "101 Switching Protocols";
		case Code::I102:
			return "102 Processing";
		case Code::S200:
			return "200 OK";
// Todo: дописать коды)
		default:
			return "";
	}
}