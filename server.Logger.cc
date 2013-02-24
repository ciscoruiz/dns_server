#if __solaris__ || __forte__
#include <stdarg.h>
#include <stdio.h>
#endif

#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <dns.server.Logger.h>
#include <dns.server.Exception.h>
#include <dns.server.DataBlock.h>
#include <dns.server.functions.h>

using namespace std;
using namespace dns;

//static
server::Logger::Level server::Logger::st_level (server::Logger::Debug);

//static
ofstream* server::Logger::st_file (NULL);

void server::Logger::initialize (const char* fileName)
   throw (Exception)
{
   if (st_file == NULL) {
      st_file = new ofstream (fileName, ios::out|ios::trunc);
  
      if (st_file->is_open () == false) {
         string msg (fileName);
         msg += ": " ;
         msg += strerror (errno);
         delete st_file;
         st_file = NULL;
         throw Exception (msg, FILE_LOCATION);
      }
   }
}

void server::Logger::write (const Level level, const char* text, const char* fromFile, const int fromLine)
   throw ()
{
   if (isActive (level) && st_file != NULL) 
      *st_file << asString (level) << " | " << fromFile << " (" << fromLine << ") | " << text << endl << endl;
}

void server::Logger::write (const Level level, const char* text, const char* value, const char* fromFile, const int fromLine)
   throw ()
{
   if (isActive (level) && st_file != NULL) 
      *st_file << asString (level) << " | " << fromFile << " (" << fromLine << ") | " << text << " | " << value << endl << endl;
}

void server::Logger::write (const Level level, const char* text, const int value, const char* fromFile, const int fromLine)
   throw ()
{
   if (isActive (level) && st_file != NULL) 
      *st_file << asString (level) << functions::asString (" | %s (%d) | %s | %d (%x)", fromFile, fromLine, text, value, value) << endl << endl;
}

void server::Logger::write (const Level level, const char* text, const DataBlock& value, const char* fromFile, const int fromLine)
   throw ()
{
   if (isActive (level) && st_file != NULL) {
      try {
         *st_file << asString (level) << " | " << fromFile << " (" << fromLine << ") | " << text << " | DataBlock: ";
         *st_file << value.asString (24);
      }
      catch (...) {
         *st_file << asString (level) << " | " << fromFile << " (" << fromLine << ") | " << text << " | DataBlock: <fault!>" << endl << endl;
      }
   }
}
       
server::Logger::Level server::Logger::asLevel (const char* stringLevel)
   throw (Exception)
{
   static struct {
      const char* stringLevel;
      const Level level;
   } values [] = {
      { "emergency", Emergency }, { "alert", Alert }, { "critical", Critical }, { "error", Error },
      { "warning", Warning }, { "notice", Notice }, { "information", Information }, { "debug", Debug },
      { "local0", Local0 }, { "local1", Local1 }, { "local2", Local2 }, { "local3", Local3 }, 
      { "local4", Local4 }, { "local5", Local5 }, { "local6", Local6 }, { "local7", Local7 },
      { NULL, (Level) -1  }
   };
   int i = 0;
   
   while (values [i].stringLevel != NULL) {
      if (strcasecmp (stringLevel, values [i].stringLevel) == 0) 
         break;
      i ++; 
   }
   
   if (values [i].stringLevel == NULL) {
      std::string msg = "Level of traces is not registrered: '";
      msg += stringLevel;
      msg += "'. Valid levels are: ";
      for (i = 0; values [i].stringLevel != NULL; i ++) {
         msg += values [i].stringLevel;
         msg += ' ';
      }
      throw Exception (msg, FILE_LOCATION);  
   }
   
   return values [i].level;
}

const char* server::Logger::asString (const Level level)
   throw ()
{
   static const char* levels [] = {
       "Emergency", "Alert", "Critical", "Error", "Warning", "Notice", "Information", "Debug"
   };
   static struct {
      const char* stringLevel;
      const Level level;
   } values [] = {
      { "Local0", Local0 }, { "Local1", Local1 }, { "Local2", Local2 }, { "Local3", Local3 }, 
      { "Local4", Local4 }, { "Local5", Local5 }, { "Local6", Local6 }, { "Local7", Local7 },
      { NULL, (Level) -1  }
   };
   const char* result = NULL;
   
   if (level >= Emergency && level <= Debug) 
      result = levels [level];
   else {
      for (int i = 0; values [i].stringLevel != NULL; i ++) {
         if (level == values [i].level) {
            result = values [i].stringLevel;
            break;
         }
      }
      if (result == NULL)
         result = "Other";
   }
      
   return result;
}

