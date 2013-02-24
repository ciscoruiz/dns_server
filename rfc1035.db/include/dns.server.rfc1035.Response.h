#ifndef _dns_server_rfc1035_Response_h
#define _dns_server_rfc1035_Response_h

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string>

#include <dns.server.rfc1035.Header.h>
#include <dns.server.rfc1035.QuestionSection.h>
#include <dns.server.rfc1035.AnswerSection.h>

namespace dns {

namespace server {


namespace rfc1035 {

class Response : public Header {
public:
   Response ();

   const DataBlock& encode () const throw (Exception);

   void setQuestionSection (const QuestionSection& _questionSection) throw () {
      questionSection = _questionSection;
   }

   // Copy first fieild from question, RDdata and length will be established in 'setHostAddress'
   void setAnswerSection (const QuestionSection& _questionSection) throw () {
      answerSection = _questionSection;
   }

   void clearHostAddress () { answerSection.clearData (); }
   void setHostAddress (const in_addr* _hostAddress) throw (Exception);

   std::string asString () const throw ();

private:
   QuestionSection questionSection;
   AnswerSection answerSection;
};

}
}
}

#endif

