#ifndef CPP_WEB_CONTENT_H
#define CPP_WEB_CONTENT_H

#include <string>

class Content {
public:
	virtual std::string serialize() = 0;
	virtual std::string get_content_type() = 0;
	virtual unsigned long get_content_length() = 0;
	virtual ~Content() = default;
};


#endif //CPP_WEB_CONTENT_H
