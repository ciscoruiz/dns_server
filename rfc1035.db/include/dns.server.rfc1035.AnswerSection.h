#ifndef _dns_server_rfc1035_AnswerSection_h
#define _dns_server_rfc1035_AnswerSection_h

#include <dns.server.rfc1035.MessageBody.h>
#include <dns.server.rfc1035.QuestionSection.h>

namespace dns {

namespace server {

class DataBlock;

namespace rfc1035 {

class AnswerSection {
public:
   AnswerSection ();
   ~AnswerSection ();

   const DataBlock& encode () const throw (Exception);

   const std::string& getName () const throw () { return name; }
   int getType () const throw () { return type; }
   int getClass () const throw () { return xClass; }
   const DataBlock& getData () const throw () { return data; }

   void setTTL (const int _ttl) throw () { ttl = _ttl; }

   void setData (const void* buffer, const int size) { data.assign ((char*) buffer, size); }
   void setData (const DataBlock& _data) throw () { data = _data; }
   void clearData () throw () { data.clear (); }

   AnswerSection& operator= (const QuestionSection& questionSection) throw () {
      name = questionSection.getQName ();
      type = questionSection.getQType();
      xClass = questionSection.getQClass ();
      return *this;
   }

   std::string asString () const throw ();

private:
   std::string name;
   Short type;
   Short xClass;
   int ttl;
   DataBlock data;
   mutable DataBlock* encodeContainer;
};

}
}
}

#endif

