#ifndef CPP_WEB_SERVERCONFIG_H
#define CPP_WEB_SERVERCONFIG_H


class ServerConfig {

public:
	ServerConfig() :
		m_max_active_connections(60000),
		m_usleep_time_no_new_connections(200)
	{ }

	int m_max_active_connections;
	int m_usleep_time_no_new_connections;
};


#endif //CPP_WEB_SERVERCONFIG_H
