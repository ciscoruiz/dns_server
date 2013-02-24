#include <ctype.h>

#include <dns.server.DataBlock.h>
#include <dns.server.functions.h>
#include <dns.server.Logger.h>

#include <dns.server.rfc1035.QuestionSection.h>

using namespace std;
using namespace dns;
using namespace dns::server;

rfc1035::QuestionSection::QuestionSection () :
   encodeContainer (NULL)
{
}

//virtual
rfc1035::QuestionSection::~QuestionSection ()
{
   delete encodeContainer;
}

void rfc1035::QuestionSection::decode (const rfc1035::MessageBody& body)
   throw (Exception)
{
   qName.clear ();
   qType = qClass = 0;

   if (body.second <= sizeof (short) * 2)
      throw Exception ("rfc1035::QuestionSection::decode | Question section is not valid", FILE_LOCATION);

   const char* buffer = body.first;

   int length = *buffer ++;

   /*
    * QName fields is compound by a list N of labels matching with pattern:
    *    1 byte indicating length of label (M).
    *    list of M bytes that contains label, We want searching with case-insensitivity
    *    1 byte with 0 value indicating the ending.
    */
   while (length != 0) {
      for (int ii = 0; ii < length; ii ++)
         qName += tolower (*buffer ++);

      // If there is more labels then we  must separate them with '.'
      if ((length = *buffer ++) != 0)
         qName += '.';
   }

   qType = functions::decodeShort (buffer);
   qClass = functions::decodeShort (buffer);
}

const DataBlock& rfc1035::QuestionSection::encode () const
   throw (Exception)
{
   if (encodeContainer == NULL) {
      // Create and reserve memory that will be used along the execution
      encodeContainer = new DataBlock;
      encodeContainer->allocate (sizeof (short) * 2);
   }

   encodeContainer->clear ();
   encodeContainer->append (functions::encode (qName));
   encodeContainer->append (functions::encodeShort (qType));
   encodeContainer->append (functions::encodeShort (qClass));

   LOGDEBUG (
      string msg ("rfc1035::QuestionSection::decode | ");
      msg += encodeContainer->asString ();
      Logger::debug (msg, FILE_LOCATION);
   );

   return *encodeContainer;
}

string rfc1035::QuestionSection::asString () const
   throw ()
{
   string result ("rfc1035::QuestionSection { QName: ");
   result += qName;
   result += functions::asText (" | QType: ", qType);
   result += functions::asText (" | QClass: ", qClass);
   return result += " }";
}
