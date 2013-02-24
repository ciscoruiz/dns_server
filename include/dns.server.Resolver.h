#ifndef _dns_server_Resolver_h
#define _dns_server_Resolver_h

#include <string>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include <dns.server.Exception.h>
#include <dns.server.SingleList.h>

namespace dns {

namespace server {

class Application;

class Resolver {
public:
   ~Resolver ();
	
   const in_addr* apply (const char* domain) const throw ();

private:
   struct Entry {
      std::string domain;
      in_addr hostAddress;
		
      Entry (const char* _domain, const in_addr& _hostAddress) : domain (_domain), hostAddress (_hostAddress) {;}
   };

   // Odd number improve scattering function
   static const int HashSize = 11;

   typedef SingleList <Entry> collision_container;
   typedef collision_container::iterator collision_iterator;

   typedef collision_container** HashTable;

   HashTable hashTable;
	
   Resolver ();
   // We separates constructor and initialization in order to launch exception if it is necessary
   void initialize (const char* dictionaryName) throw (Exception);
   void record (const int lineno, char* line) throw (Exception);
   const in_addr* find (const char* domain) const throw ();

   friend class Application;
     // Constructor, initialize
};

}
}

#endif

