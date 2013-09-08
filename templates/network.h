#ifndef NETWORK_H
#define NETWORK_H

#include <string>

class GameSocket
{
    public:
        GameSocket();
        bool open_server_connection(const std::string host, const int port);
        bool send_string(const std::string payload);
        std::string rec_string();

    private:
        int sock;
};
#endif
