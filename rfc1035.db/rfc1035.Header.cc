#include <string.h>

#include <arpa/inet.h>

#include <dns.server.DataBlock.h>
#include <dns.server.functions.h>

#include <dns.server.rfc1035.Header.h>

using namespace std;
using namespace dns;
using namespace dns::server;

assign_enum (rfc1035::Header::OpCode) = { "StandardQuery", "InverseQuery", "Status", NULL };
assign_enum (rfc1035::Header::ResponseCode) = { "Ok", "FormatError", "ServerFailure", "NameError", "NotImplemented", "Refused", NULL };
assign_enum (rfc1035::Header::Counter::Type) = { "QDCount", "ANCount", "NSCount", "ARCount", NULL };

rfc1035::Header::Header (const WhatIs::_v whatIs) :
   encodeContainer (NULL)
{
   memset (&detail, 0, sizeof (detail));
   memset (counters, 0, sizeof (counters));

   detail.whatIs = whatIs;
}

//virtual 
rfc1035::Header::~Header ()
{
   delete encodeContainer;
}

rfc1035::Header::Counter::size_t rfc1035::Header::getCounter (const Header::Counter::Type::_v counterType) const
   throw (Exception)
{
   if (counterType >= Counter::Type::End)
      throw Exception ("Counter out of range", FILE_LOCATION);

   return counters [counterType];
}

void rfc1035::Header::setCounter (const Header::Counter::Type::_v counterType, const Header::Counter::size_t counterValue)
   throw (Exception)
{
   if (counterType >= Counter::Type::End)
      throw Exception ("Counter out of range", FILE_LOCATION);

   counters [counterType] = counterValue;
}

DataBlock& rfc1035::Header::encodeHeader () const
   throw (Exception)
{
   if (encodeContainer == NULL) {
      // Create and reserve memory that will be used along the execution
      encodeContainer = new DataBlock;
      encodeContainer->allocate (calculateSizeOfHeader ());
   }

   encodeContainer->clear ();
   encodeContainer->append (functions::encodeShort (id));
   encodeContainer->append (functions::encodeShort (detailtAsShort()));

   for (int cc = Counter::Type::Begin; cc < Counter::Type::End; cc ++)
      encodeContainer->append (functions::encodeShort (counters [cc]));

   return *encodeContainer;
}

/*
 * Returns the address and length of the body message.
 */
rfc1035::MessageBody rfc1035::Header::decodeHeader (const DataBlock& message)
   throw (Exception)
{
   if (message.getSize() < calculateSizeOfHeader ()) {
      string msg ("rfc1035::Header::decodeHeader | Message does not contains message matching with RFC 1035 | Buffer: ");
      msg += message.asString (24);
      throw Exception (msg, FILE_LOCATION);
   }

   const char* buffer = message.getData();

   // remember method decodeShort, decode and move 'buffer' to next element
   id = functions::decodeShort (buffer);

   const short aux = functions::decodeShort (buffer);

   detail.whatIs              = (aux & 0x8000 /* 1000 0000 0000 0000 */) >> 15;
   detail.opCode              = (aux & 0x7800 /* 0111 1000 0000 0000 */) >> 11;
   detail.authoritativeAnswer = (aux & 0x0400 /* 0000 0100 0000 0000 */) >> 10;
   detail.truncation          = (aux & 0x0200 /* 0000 0010 0000 0000 */) >> 9;
   detail.recursionDesired    = (aux & 0x0100 /* 0000 0001 0000 0000 */) >> 8;
   detail.recursionAvailable  = (aux & 0x0080 /* 0000 0000 1000 0000 */) >> 7;
   detail.unused              = 0;            /* 0000 0000 0zzz 0000 */
   detail.responseCode        = (aux & 0x000f /* 0000 0000 0000 1111 */);

   for (int cc = Counter::Type::Begin; cc < Counter::Type::End; cc ++)
      counters [cc] = functions::decodeShort (buffer);

   // 'buffer' points to the beginning of Question Section
   return MessageBody (buffer, message.getSize() - calculateSizeOfHeader());
}

//virtual
std::string rfc1035::Header::asString () const
   throw ()
{
   string result ("rfc1035::Header { ID: ");

   result += functions::asHexString (id);

   result += functions::asHexText (" | Bits: ", detailtAsShort());
   result += " | WhatIs: ";
   result += detail.whatIs == WhatIs::Query ? "Query": "Response";

   if (detail.opCode <= OpCode::Status) {
      OpCode::_v opCode = (OpCode::_v) detail.opCode;
      result += " | OpCode: ";
      result += OpCode::asCString (opCode);
   }
   else
      result += functions::asText (" | OpCode: ", detail.opCode);

   result += functions::asText (" | AA: ", detail.authoritativeAnswer);
   result += functions::asText (" | TC: ", detail.truncation);
   result += functions::asText (" | RD: ", detail.recursionDesired);
   result += functions::asText (" | RA: ", detail.recursionAvailable);

   if (detail.responseCode <= ResponseCode::Refused) {
      ResponseCode::_v responseCode = (ResponseCode::_v) detail.responseCode;
      result += " | RCode: ";
      result += ResponseCode::asCString (responseCode);
   }
   else
      result += functions::asText (" | RCode: ", detail.responseCode);

   for (int cc = Counter::Type::Begin; cc < Counter::Type::End; cc ++)
      result += functions::asString (" | %s: %u", item_enum (Counter::Type, cc), counters [cc]);

   return result += " }";
}

int rfc1035::Header::detailtAsShort () const
   throw ()
{
   int result (0);
   int aux;

   if (detail.whatIs == WhatIs::Response)
      result = 0x8000;

   aux = detail.opCode; result += (aux << 11);

   if (detail.authoritativeAnswer)
      result |= 0x0400;

   if (detail.truncation)
      result |= 0x0200;

   if (detail.recursionDesired)
      result |= 0x0100;

   if (detail.recursionAvailable)
      result |= 0x0080;

   return result |= detail.responseCode;
}
