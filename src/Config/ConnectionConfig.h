#ifndef CPP_WEB_CONNECTIONCONFIG_H
#define CPP_WEB_CONNECTIONCONFIG_H

class ConnectionConfig {
public:
	ConnectionConfig() :
		m_usleep_time_nothing_to_read(200),
		m_usleep_time_no_free_handler(200)
	{}

	int m_usleep_time_nothing_to_read;
	int m_usleep_time_no_free_handler;
};

#endif //CPP_WEB_CONNECTIONCONFIG_H
