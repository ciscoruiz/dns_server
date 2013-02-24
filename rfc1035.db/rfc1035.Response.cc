#include <string.h>
#include <errno.h>

#include <dns.server.DataBlock.h>
#include <dns.server.Logger.h>

#include <dns.server.rfc1035.Response.h>

using namespace std;
using namespace dns;
using namespace dns::server;

rfc1035::Response::Response () :
   rfc1035::Header (Header::WhatIs::Response)
{
   Header::setCounter (Counter::Type::EntriesInQuestionSection, 1);
   Header::setCounter (Counter::Type::ResourceRecordsInAnswerSection, 1);
}

void rfc1035::Response::setHostAddress (const in_addr* _hostAddress)
   throw (Exception)
{
   char str [64];

   if (inet_ntop (AF_INET, _hostAddress, str, sizeof (str)) == NULL) {
      string msg ("inet_ntop: ");
      msg += strerror (errno);
      throw Exception (msg, FILE_LOCATION);
   }

   int bytes = ntohl (_hostAddress->s_addr);
   char* swap = (char*) &bytes;

   /*
    * If we do not swap bytes client will receive: 10.10.95.10 for the address 10.95.10.10, or 40.30.20.10 for 10.20.30.40
    */
   char aux = swap [0];
   swap [0] = swap [3];
   swap [3] = aux;
   aux = swap [1];
   swap [1] = swap [2];
   swap [2] = aux;
   answerSection.setData (swap, sizeof (int));
}

const DataBlock& rfc1035::Response::encode () const
   throw (Exception)
{
   DataBlock& buffer (Header::encodeHeader());

   buffer += questionSection.encode ();
   buffer += answerSection.encode ();

   LOGDEBUG (
      string msg ("rfc1035::Response::decode | ");
      msg += buffer.asString ();
      Logger::debug (msg, FILE_LOCATION);
   );

   return buffer;
}

string rfc1035::Response::asString () const
   throw ()
{
   string result ("rfc1035::Response { ");
   result += Header::asString();
   result += " | ";
   result += questionSection.asString ();
   result += " | ";
   result += answerSection.asString ();

   return result += " }";
}

