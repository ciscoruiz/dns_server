#ifndef _dns_server_rfc1035_Header_h
#define _dns_server_rfc1035_Header_h

#include <dns.server.autoenum.h>
#include <dns.server.DataBlock.h>
#include <dns.server.defines.h>

#include <dns.server.rfc1035.MessageBody.h>

namespace dns {

namespace server {

class DataBlock;

namespace rfc1035 {

// Detailed information at RFC 1035, page 25
class Header {
public:
   struct WhatIs { enum _v { Query = 0, Response = 1 }; };

   struct OpCode {
      enum _v { None = -1, StandardQuery, InverseQuery, Status };
      declare_enum (OpCode)
   };

   struct ResponseCode {
      enum _v { None = -1, Ok, FormatError, ServerFailure, NameError, NotImplemented, Refused };
      declare_enum (ResponseCode)
   };

   struct Counter {
      typedef short unsigned size_t;

      struct Type {
         enum _v { None = -1, EntriesInQuestionSection, ResourceRecordsInAnswerSection, ResourceRecordsInAuthoritySection, ResourceRecordsInAdditionalSection, End, Begin = 0 };

         declare_enum (Type)
      };
   };

   virtual ~Header ();

   short getID () const throw () { return id; }
   bool isQuery () const throw () { return detail.whatIs == WhatIs::Query; }
   int getOpCode () const throw () { return detail.opCode; }
   bool isAuthoritativeAnswer () const throw () { return detail.authoritativeAnswer == 1; }
   bool isTruncated () const throw () { return detail.truncation == 1; }
   bool getRecursionDesired () const throw () { return detail.recursionDesired == 1; }
   bool getRecursionAvailable () const throw () { return detail.recursionAvailable == 1; }
   int getResponseCode () const throw () { return detail.responseCode; }
   Counter::size_t getCounter (const Counter::Type::_v counterType) const throw (Exception);

   void setID (const short _id) { id = _id; }
   void setOpCode (const int opCode) throw () { detail.opCode = (opCode & 0xf); }
   void setAuthoritativeAnswer (const bool authoritativeAnswer) throw () { detail.authoritativeAnswer = authoritativeAnswer; }
   void setIsTruncated (const bool isTruncated) throw () { detail.truncation = isTruncated; }
   void setRecursionDesired (const bool recursionDesired) throw () { detail.recursionDesired = recursionDesired; }
   void setRecursionAvailable (const bool recursionAvailable) throw () { detail.recursionAvailable = recursionAvailable; }
   void setResponseCode (const int responseCode) throw () { detail.responseCode = (responseCode & 0xf); }
   void setCounter (const Counter::Type::_v, const Counter::size_t) throw (Exception);

   virtual std::string asString () const throw ();

protected:
   Header (const WhatIs::_v whatIs);

   DataBlock& encodeHeader () const throw (Exception);
   MessageBody decodeHeader (const DataBlock&) throw (Exception);

private:
   Short id;

   // More information about bit fields at: http://www.cs.cf.ac.uk/Dave/C/node13.html
   struct {
      bool whatIs: 1;
      int opCode: 4;
      bool authoritativeAnswer: 1;
      bool truncation: 1;
      bool recursionDesired: 1;
      bool recursionAvailable: 1;
      int unused: 3;
      int responseCode: 4;
   } detail;

   int detailtAsShort () const throw ();

   Counter::size_t counters [Counter::Type::End];

   const int calculateSizeOfHeader () const throw () { return sizeof (id) + sizeof (detail) + sizeof (counters); }

   mutable DataBlock* encodeContainer;
};

}
}
}

#endif

