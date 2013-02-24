#ifndef _dns_server_rfc1035_QuestionSection_h
#define _dns_server_rfc1035_QuestionSection_h

#include <dns.server.rfc1035.MessageBody.h>

namespace dns {

namespace server {

class DataBlock;

namespace rfc1035 {

// This class/part of protocol is used from Query and Response
// because response must contain Question Section of Query.
class QuestionSection {
public:
   QuestionSection ();
   ~QuestionSection ();

   void decode (const MessageBody&) throw (Exception);
   const DataBlock& encode () const throw (Exception);

   const char* getQName () const throw () { return qName.empty () ? NULL: qName.c_str (); }
   Short getQType () const throw () { return qType; }
   Short getQClass () const throw () { return qClass; }

   QuestionSection& operator= (const QuestionSection& other) throw () {
      qName = other.qName;
      qType = other.qType;
      qClass = other.qClass;
      return *this;
   }

   std::string asString () const throw ();

private:
   std::string qName;
   Short qType;
   Short qClass;
   mutable DataBlock* encodeContainer;
};

}
}
}

#endif

