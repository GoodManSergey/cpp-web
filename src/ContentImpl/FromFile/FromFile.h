#ifndef CPP_WEB_FROMFILE_H
#define CPP_WEB_FROMFILE_H

#include "../../Content/Content.h"
#include <string>

class FromFile: public Content {
public:
	FromFile(const std::string& file_path, std::string content_type);
	std::string serialize() override;
	std::string get_content_type() override;
	unsigned long get_content_length() override;

private:
	std::string m_data;
	std::string m_content_type;
};


#endif //CPP_WEB_FROMFILE_H
