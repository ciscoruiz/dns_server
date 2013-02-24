#ifndef _dns_server_DatagramSocket_h
#define _dns_server_DatagramSocket_h

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <dns.server.Exception.h>
#include <dns.server.DataBlock.h>

namespace dns {

namespace server {

class Application;

class DatagramSocket : public DataBlock {
public:
   ~DatagramSocket ();

   const DataBlock& read () throw (Exception);
   void write (const DataBlock&) throw (Exception);
	
private:
   int stream;   
   sockaddr_in clientAddress;
   socklen_t addrLen;

   DatagramSocket ();
   // We separates constructor and initialization in order to launch exception if it is necessary
   void initialize (const int port, const char* ip) throw (Exception);
	
   friend class Application;
      // Constructor, initialize
};

}
}

#endif

