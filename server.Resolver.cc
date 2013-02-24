#include <string.h>
#include <errno.h>
#include <ctype.h>

#include <iostream>
#include <fstream>

#include <dns.server.Resolver.h>
#include <dns.server.Logger.h>
#include <dns.server.functions.h>

using namespace std;
using namespace dns;

server::Resolver::Resolver ()
{
   hashTable = new collision_container* [HashSize];
   memset (hashTable, 0, sizeof (collision_container*) * HashSize);
}

server::Resolver::~Resolver()
{
   for (int index = 0; index < HashSize; index ++) 
      delete hashTable [index];
      
   delete [] hashTable;
}

void server::Resolver::initialize (const char* dictionaryName) 
   throw (Exception)
{
   LOGDEBUG (
      string msg ("server::Resolver::initialize | Dictionary: ");
      msg += dictionaryName;
      Logger::debug (msg, FILE_LOCATION);
   );
   
   ifstream dictionaryFile (dictionaryName);
   
   if (!dictionaryFile) {
      const int xerror = errno;
      string msg (dictionaryName);
      msg += ": ";
      msg += strerror (xerror);
      throw Exception (msg, FILE_LOCATION);
   }
   
   char line [1024];
   char* comment;
   int lineno = 1;
   
   // As usual we can write comments using '#' character
   while (dictionaryFile.eof () == false) {
      dictionaryFile.getline (line, sizeof (line));
      lineno ++;
      
      if ((comment = strchr (line, '#')) != NULL) 
         *comment = 0;
      
      if (strlen (line) == 0)
         continue;
         
      record (lineno, line);
   }
}

/*
 * Every line must have something similar to:
 * 
 *    www.google.es 209.85.146.105
 *    www.yahoo.com         87.248.112.181
 */
void server::Resolver::record (const int lineno, char* line) 
   throw (Exception)
{
   char* domain = NULL;
   char* hostAddress = NULL;

   char* separation = strchr (line, ' ');

   if (separation != NULL) {
      domain = line;
      *separation = 0;
      
      for (hostAddress = separation + 1; *hostAddress == ' ' && *hostAddress != 0; hostAddress ++);
      if (*hostAddress == 0)
         hostAddress = NULL;      
   }
   
   if (domain == NULL || hostAddress == NULL) {
      string msg ("server::Resolver::record | LineNo: ");
      msg += functions::asString (lineno);
      msg += " | Line does not match format <Domain>{<space>*}<HostAddress>";
      throw Exception (msg, FILE_LOCATION);
   }
            
   in_addr address;
   
   if (inet_aton (hostAddress, &address) == 0) {
      string msg ("HostAddress: ");
      msg += hostAddress;
      msg += " | Host address has not valid format";
      throw Exception (msg, FILE_LOCATION);
   }
            
   // Search will be case-insensitive
   for (char* ww = domain; *ww != 0; ww ++) *ww = tolower (*ww);

   if (find (domain) != NULL) {
      string msg ("server::Resolver::record | LineNo: ");
      msg += functions::asString (lineno);
      msg += " | Domain '";
      msg += domain;
      msg += "' already registered";
      throw Exception (msg, FILE_LOCATION);
   }

   const Integer64 hash = functions::hash (domain);
   const int index = hash % HashSize;

   LOGDEBUG (
      string msg = functions::asString ("LineNo: %d | Domain: %s | HostAddress: %s | Index: %d | InetAddress (0x%lx): 0x%x", lineno, domain, hostAddress, index, address.s_addr, ntohl (address.s_addr));
      Logger::debug (msg, FILE_LOCATION);
   )
      
   if (hashTable [index] == NULL) 
      hashTable [index] = new collision_container;
      
   hashTable [index]->push_back (new Entry (domain, address));

   cout << "   Reading " << domain << " -> " << hostAddress << endl;
}

const in_addr* server::Resolver::apply (const char* _domain) const throw ()
{
   bool duplicate = false;
   
   char* domain = const_cast <char*> (_domain);

   for (char* ww = domain; *ww != 0; ww ++){
      if (isupper (*ww)) {
         duplicate = true;
         break;         
      }
   }
   
   // Try to optimize dynamic memory usage
   if (duplicate == true) {
      domain = strdup (domain);
      for (char* ww = domain; *ww != 0; ww ++)
         *ww = tolower (*ww);
   }
   
   const in_addr* result = find (domain);
   
   if (duplicate == true)
      free (domain);
      
   LOGDEBUG (
      const char* ip = (result != NULL) ? inet_ntoa (*result): "<none>";
      string msg = functions::asString ("Resolver searching for Domain: %s | Found: %s", domain, ip);
      Logger::debug (msg, FILE_LOCATION);
   )
      
   return result;
}

// After tuning process (element vs collision container) the HASH structure would perform complexity close to O(1)
const in_addr* server::Resolver::find (const char* domain) const throw ()
{
   const Integer64 hash = functions::hash (domain);
   const int index = hash % HashSize;
   
   collision_container* container = hashTable [index];

   LOGDEBUG (
      string msg = functions::asString ("server::Resolver::find | Domain: %s | Index: %d", domain, index);
      Logger::debug (msg, FILE_LOCATION);
   )

   if (container == NULL) 
      return NULL;
      
   in_addr* result (NULL);
   for (collision_iterator ii = container->begin (); ii != NULL && result == NULL; ii = collision_container::next (ii)) {
      if (ii->data->domain == domain) {
         result = &ii->data->hostAddress;
         break;
      }
   }      
   
   return result;
}
