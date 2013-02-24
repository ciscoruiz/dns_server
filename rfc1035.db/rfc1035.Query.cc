#include <dns.server.DataBlock.h>
#include <dns.server.functions.h>
#include <dns.server.Logger.h>

#include <dns.server.rfc1035.Query.h>

using namespace std;
using namespace dns;
using namespace dns::server;

rfc1035::Query::Query () :
   Header (Header::WhatIs::Query)
{
}

bool rfc1035::Query::isValid () const
   throw ()
{
   return Header::isQuery() == true && Header::getOpCode() == Header::OpCode::StandardQuery && Header::getCounter (Header::Counter::Type::EntriesInQuestionSection) > 0 && getQName () != NULL;
}

void rfc1035::Query::decode (const DataBlock& message)
   throw (Exception)
{
   LOGDEBUG (
      string msg ("rfc1035::Query::decode | ");
      msg += message.asString ();
      Logger::debug (msg, FILE_LOCATION);
   );

   // Decode header and returns where would begin the question section
   questionSection.decode (Header::decodeHeader (message));
}

string rfc1035::Query::asString () const
   throw ()
{
   string result ("rfc1035::Query { ");
   result += Header::asString();
   result += " | ";
   result += questionSection.asString ();
   return result += " }";
}
