#ifndef _dns_server_rfc1035_Query_h
#define _dns_server_rfc1035_Query_h

#include <dns.server.rfc1035.Header.h>
#include <dns.server.rfc1035.QuestionSection.h>

namespace dns {

namespace server {

namespace rfc1035 {

class Query : public Header {
public:
   Query ();

   void decode (const DataBlock&) throw (Exception);

   bool isValid () const throw ();

   const char* getQName () const throw () { return questionSection.getQName(); }

   const QuestionSection& getQuestionSection () const throw () { return questionSection; }

   std::string asString () const throw ();

private:
   QuestionSection questionSection;
};

}
}
}

#endif

