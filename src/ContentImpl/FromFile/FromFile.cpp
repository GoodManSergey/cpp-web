#include "FromFile.h"
#include <fstream>
#include <iostream>

FromFile::FromFile(const std::string& file_path, std::string content_type) :
	m_content_type(std::move(content_type))
{
	std::ifstream file;
	file.open(file_path, std::ios::binary);
	if (file.is_open()) {
		std::string line;
		while (getline(file, line) ) {
			m_data += line;
		}
		file.close();
	}
}

std::string FromFile::serialize() {
	return m_data;
}

std::string FromFile::get_content_type() {
	return m_content_type;
}

unsigned long FromFile::get_content_length() {
	return m_data.size();
}
