#include "Html.h"

Html::Html(const std::string &content) :
m_content(content)
{ }

std::string Html::get_content_type() {
	return "text/html";
}

std::string Html::serialize() {
	return m_content;
}

unsigned long Html::get_content_length() {
	return m_content.length();
}