#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <assert.h>

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable : 4996)
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#define SOCKET_ERROR -1
#endif

#include "network.h"

#define GLOBAL_BUFFER_SIZE 512

using namespace std;

GameSocket::GameSocket() : sock(-1) {}

bool GameSocket::open_server_connection(const string host, const int port)
{
    struct sockaddr_in addr;

#ifdef WIN32
    WSADATA wsaData;
    WSAStartup( MAKEWORD( 2, 2 ), &wsaData );
#endif
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock == SOCKET_ERROR )
    {
        cerr << "Error creating socket" << endl;
        return false;
    }

    // cover our DNS lookup stuff:
    struct hostent *h;
    if((h = gethostbyname( host.c_str() )) == NULL)
    {
        cerr << "Unable to lookup host: " << host << endl;
        return false;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr = *((struct in_addr *)h->h_addr);
    memset(addr.sin_zero, '\0', sizeof(addr.sin_zero) );

    if( connect(sock, (struct sockaddr *)&addr, sizeof(addr) ) == SOCKET_ERROR)
    {
        cerr <<  "Unable to open socket!" << endl;
        cerr << "Couldn't connect to " << host << endl;
#ifdef WIN32
        cerr << "Windows Error " << WSAGetLastError() << endl;
#endif
        return false;
    }
    return true;
}


bool GameSocket::send_string(const string payload) {

#ifdef SHOW_NETWORK
    cout << "C: " << payload << endl;
#endif

    int length = payload.size();
    int offset = 0;

    int msg_len = htonl(length);

    // first, send the payload size (4 bytes)
   int val = send(sock, (char*)&msg_len, 4, 0);
    if( val != 4)
    {
        cerr << "Connection broken." << endl;
        cerr << "Sent: " << val << endl;
        return false;
    }

    // now, keep sending chunks of the payload
    // until we send the whole thing


    while(offset < length)
    {
        int sent;
        if((sent = send(sock,
                        payload.c_str()+offset,
                        length-offset, 0)) == -1)
        {
            cerr << "Error sending data to  server!" << endl;
            return false;
        }

        // update the offset to copy from
        offset += sent;
    }

    return true;

}


// Takes the socket connected to the server, reads
// the network packet format, and extracts the payload
// as a string.
string GameSocket::rec_string()
{
    static char* buffer = NULL;
    static int buffer_length = -1;

    int received = 0;
    int numbytes;
    int length = -1;
    int bytes_left_to_read = 0;

    // first, receive the payload size (4 bytes)
    numbytes = recv(sock, (char*)&length, 4, 0);
    if( numbytes == 0)
    {
        cerr << "Disconnected from server!" << endl;
        // we've been disconnected, there's no point in going on
        exit(0);
    }
    // get this out of network byte order
    //memcpy((void*)&msg_len, (void*)&buffer, 4);
    length = ntohl(length);

    bytes_left_to_read = length;

    if(buffer_length < length)
    {
        buffer = new char[length];
        buffer_length = length;
    }

    while(bytes_left_to_read - received > 0)
    {
        numbytes = 0;
        if((numbytes = recv(sock, buffer+received,
                        length-received, 0)) == -1)
        {
            cerr << "Error reading data from server!" << endl;
            return 0;
        }

        if(numbytes == 0)
        {
            cerr << "Disconnected from server!" << endl;
            // we've been disconnected, there's no point in going on
            exit(0);
        }

        received += numbytes;
    }

#ifdef SHOW_NETWORK
    cout << "S: " << result.c_str() << endl;
#endif
    string ret(buffer, length);
    return ret;
}
