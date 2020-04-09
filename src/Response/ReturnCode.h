#ifndef CPP_WEB_RETURNCODE_H
#define CPP_WEB_RETURNCODE_H

#include <string>

class ReturnCode {
public:
	enum class Code{
		// Information
		I100,
		I101,
		I102,

		// Success
		S200,
		S201,
		S202,
		S203,
		S204,
		S205,
		S206,
		S207,
		S208,
		S226,

		// Redirect
		R300,
		R301,
		R302,
		RF302,
		R303,
		R304,
		R305,
		R307,
		R308,

		// Client error
		CE400,
		CE401,
		CE402,
		CE403,
		CE404,
		CE405,
		CE406,
		CE407,
		CE408,
		CE409,
		CE410,
		CE411,
		CE412,
		CE413,
		CE414,
		CE415,
		CE416,
		CE417,
		CE418,
		CE419,
		CE421,
		CE422,
		CE423,
		CE424,
		CE426,
		CE428,
		CE429,
		CE431,
		CE449,
		CE451,
		CE499,

		// Server error
		SE500,
		SE501,
		SE502,
		SE503,
		SE504,
		SE505,
		SE506,
		SE507,
		SE508,
		SE509,
		SE510,
		SE511,
		SE520,
		SE521,
		SE522,
		SE523,
		SE524,
		SE525,
		SE526
	};

	static std::string get_description(Code code);
	ReturnCode() = delete;
};


#endif //CPP_WEB_RETURNCODE_H
