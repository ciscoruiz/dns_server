#include <ctype.h>

#include <dns.server.DataBlock.h>
#include <dns.server.functions.h>
#include <dns.server.Logger.h>

#include <dns.server.rfc1035.AnswerSection.h>

using namespace std;
using namespace dns;
using namespace dns::server;

rfc1035::AnswerSection::AnswerSection () :
   encodeContainer (NULL),
   ttl (0)
{
}

//virtual
rfc1035::AnswerSection::~AnswerSection ()
{
   delete encodeContainer;
}

const DataBlock& rfc1035::AnswerSection::encode () const
   throw (Exception)
{
   if (encodeContainer == NULL) {
      // Create and reserve memory that will be used along the execution
      encodeContainer = new DataBlock;
      encodeContainer->allocate (sizeof (short) * 3);
   }

   encodeContainer->clear ();
   encodeContainer->append (functions::encode (name));
   encodeContainer->append (functions::encodeShort (type));
   encodeContainer->append (functions::encodeShort (xClass));
   encodeContainer->append (functions::encodeInteger (ttl));

   if (data.isEmpty() == false) {
      encodeContainer->append (functions::encodeShort (data.getSize ()));
      encodeContainer->append (data);
   }
   else {
      encodeContainer->append (functions::encodeShort (1));
      *encodeContainer += '\0';
   }

   LOGDEBUG (
      string msg ("rfc1035::AnswerSection::decode | ");
      msg += encodeContainer->asString ();
      Logger::debug (msg, FILE_LOCATION);
   );

   return *encodeContainer;
}

string rfc1035::AnswerSection::asString () const
   throw ()
{
   string result ("rfc1035::AnswerSection { Name: ");
   result += name;
   result += functions::asText (" | Type: ", type);
   result += functions::asText (" | Class: ", xClass);
   result += functions::asText (" | RDLength: ", data.getSize());
   result += " | Data: ";
   result += data.asString ();
   return result += " }";
}
