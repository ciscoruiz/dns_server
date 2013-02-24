#ifndef _dns_server_Application_h
#define _dns_server_Application_h

#include <dns.server.Exception.h>

namespace dns {

namespace server {

namespace rfc1035 {
	class Query;
	class Response;
}

class DatagramSocket;
class Resolver;

class Application {
public:
   Application ();
   ~Application ();

   // We separates constructor and initialization in order to launch exception if it is necessary
   void initialize (const int argc,  char* argv []) throw (Exception);
   void run () throw (Exception);

private:
   DatagramSocket* datagramSocket;
   Resolver* resolver;
   rfc1035::Query* query;
   rfc1035::Response* response;
};

}
}

#endif

