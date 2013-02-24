#include <stdio.h>

#include <dns.server.Exception.h>
#include <dns.server.Logger.h>

using namespace dns;

server::Exception::Exception (const char* text, const char* fromFile, const int fromLine)  :
   m_text (text),
   m_errorCode (-1)
{
   m_fromFile = fromFile;
   m_fromLine = fromLine;
}

server::Exception::Exception (const std::string& text, const char* fromFile, const int fromLine)  :
   m_text (text),
   m_errorCode (-1)
{
   m_fromFile = fromFile;
   m_fromLine = fromLine;
}

server::Exception::Exception (const Exception& other)
{
   m_text = other.m_text; 
   m_fromFile = other.m_fromFile;
   m_fromLine = other.m_fromLine;
   m_errorCode = other.m_errorCode;
}

server::Exception& server::Exception::operator = (const Exception& other)
   throw ()
{
   if (this != &other) {
      m_text = other.m_text;
      m_fromFile = other.m_fromFile;
      m_fromLine = other.m_fromLine;
      m_errorCode = other.m_errorCode;
   }
 
   return *this;
}

std::string server::Exception::asString () const
   throw ()
{
   std::string result;
   char n [32];

   sprintf (n, " (%d) ] ", m_fromLine);
   result = "[ ";
   result += m_fromFile;
   result += n;
   result += ": ";
   result += m_text; 

   return result;
}

void server::Exception::trace () const
   throw ()
{
   Logger::write (Logger::Error, "Exception", m_text.c_str (), m_fromFile.c_str (), m_fromLine);   
}

