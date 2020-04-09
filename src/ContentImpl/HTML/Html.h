#ifndef CPP_WEB_HTML_H
#define CPP_WEB_HTML_H

#include "../../Content/Content.h"
#include <string>


class Html: public Content {
public:
	explicit Html(const std::string& content);
	~Html() override = default;
	std::string serialize() override;
	std::string get_content_type() override;
	unsigned long get_content_length() override ;

private:
	std::string m_content;
};


#endif //CPP_WEB_HTML_H
