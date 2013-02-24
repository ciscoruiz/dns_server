#if !defined __solaris__ || !defined __forte__
#include <stdarg.h>
#endif

#ifdef __linux__
#include <ctype.h>
#endif

#include <string.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include <dns.server.functions.h>
#include <dns.server.DataBlock.h>

#include <iostream>

using namespace std;
using namespace dns;

string server::functions::asString (const int number)
   throw ()
{
   char aux [16];
   sprintf (aux, "%d", number);
   return string (aux);
}

string server::functions::asString (const Integer64 number)
   throw ()
{
   char aux [24];

#ifdef __dns_server64__
   sprintf (aux, "%ld", number);
#else
   sprintf (aux, "%lld", number);
#endif

   return string (aux);
}

string server::functions::asString (const unsigned int number)
   throw ()
{
   char aux [16];
   sprintf (aux, "%u", number);
   return string (aux);
}

string server::functions::asString (const Unsigned64 number)
   throw ()
{
   char aux [32];
#ifdef __dns_server64__
   sprintf (aux, "%lu", number);
#else
   sprintf (aux, "%llu", number);
#endif
   return string (aux);
}

string server::functions::asString (const float number, const char* format)
   throw ()
{
   char aux [64];
   sprintf (aux, format, number);
   return string (aux);
}

string server::functions::asString (const double number, const char* format)
   throw ()
{
   char aux [64];
   sprintf (aux, format, number);
   return string (aux);
}

std::string server::functions::asString (const DataBlock& dataBlock, const int characterByLine)
   throw ()
{
   return dataBlock.asString (characterByLine);
}

string server::functions::asHexString (const int number)
   throw ()
{
   char aux [16];
   sprintf (aux, "0x%x", number);
   return string (aux);
}

string server::functions::asHexString (const Integer64 number)
   throw ()
{
   char aux [32];
#ifdef __dns_server64__
   sprintf (aux, "0x%lx", number);
#else
   sprintf (aux, "0x%llx", number);
#endif
   return string (aux);
}

string server::functions::asString (const char* format, ...)
   throw ()
{
   va_list ap;
   char aux [1024];

   va_start(ap, format );
   vsnprintf (aux, sizeof (aux), format, ap);
   va_end (ap);

   return string (aux);
}

bool server::functions::asBool (const char* str)
   throw (Exception)
{
   if (str == NULL)
      return false;

   if (strcasecmp (str, "true") == 0 || strcmp (str, "1") == 0)
      return true;

   if (strcasecmp (str, "false") == 0 || strcmp (str, "0") == 0)
      return false;

   string msg ("nemesis::funcions::asBool | Can not process '");
   msg += str;
   msg += "' as boolean";
   throw Exception (msg, FILE_LOCATION);
}

server::Integer64 server::functions::asInteger64 (const char* str)
   throw ()
{
   Integer64 number = 0;

#ifdef __dns_server64__
  sscanf (str, "%ld", &number);
#else
   sscanf (str, "%lld", &number);
#endif

   return number;
}

//static
string server::functions::asByte (const int value)
   throw ()
{
   static const int KByte = 1024;
   static const int MByte = KByte * 1024;
   string result;

   if (value < (10 * KByte)) {
      result = server::functions::asString (value);
      result += " bytes";
   }
   else if (value < (10 * MByte)) {
      const int remain = value % KByte;
      if (remain == 0) {
         const int fix = value / KByte;
         result = server::functions::asString ("%d KB", fix);
      }
      else
         result = server::functions::asString ("%.2f KB", (float) value / KByte);
   }
   else {
      const int remain = value % MByte;
      if (remain == 0) {
         const int fix = value / MByte;
         result = server::functions::asString ("%d MB", fix);
      }
      else
         result = server::functions::asString ("%.2f MB", (float) value / MByte);
   }

   return result;

}

/*static*/
/*
 * Basado en el algoritmo de http://www-graphics.stanford.edu/~seander/bithacks.html#IntegerLogLookup
 */
int server::functions::log2 (const unsigned int v)
   throw ()
{
   static const char LogTable256[] =
   {
    -1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
     4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
     5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
     5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
     6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
     6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
     6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
     6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
     7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
     7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
     7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
     7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
     7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
     7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
     7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
     7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
   };

   int r = -1;     // r will be lg(v)
   register unsigned int t, tt; // temporaries

   if (tt = v >> 16)
   {
     r = (t = tt >> 8) ? 24 + LogTable256[t] : 16 + LogTable256[tt];
   }
   else
   {
     r = (t = v >> 8) ? 8 + LogTable256[t] : LogTable256[v];
   }

   return r;
}

// from a version by Allen Holub (see Andrew Binstock, "Hashing Revisited"
// Dr. Dobb's Journal, April 1996)
server::Integer64 server::functions::hash (const char* p)
   throw ()
{
   static const int long_bits = sizeof(Integer64) << 3;
   static const int one_eighth = long_bits >> 3;
   static const int three_fourths = long_bits * 3 / 4;
   static const Integer64 high_bits = ((Integer64)(~0L)) << (long_bits - one_eighth);

   Integer64 result = 0;
   Integer64 temp;

   while (*p != 0) {
      result = (result << one_eighth) + *p ++;
      if ((temp = result & high_bits) != 0)
         result = (result ^ (temp >> three_fourths)) &~ high_bits;
   }

   return result;
}

//static
const server::DataBlock& server::functions::encodeShort (const server::Short value)
   throw (Exception)
{
   static DataBlock* memory = NULL;

   if (memory == NULL) {
      memory = new DataBlock;
      memory->allocate (sizeof (short));
   }

   char* buffer = (char*) memory->getData ();
   *buffer       = (value & 0xff00) >> 8;
   *(buffer + 1) = (value & 0x00ff);

   return *memory;
}

/*
 * Higher bits are on the left
 */

//static
const server::DataBlock& server::functions::encodeInteger (const int value)
   throw (Exception)
{
   static DataBlock* memory = NULL;

   if (memory == NULL) {
      memory = new DataBlock;
      memory->allocate (sizeof (int));
   }

   char* buffer = (char*) memory->getData ();
   *buffer 		  = (value & 0xff000000) >> 24;
   *(buffer + 1) = (value & 0x00ff0000) >> 16;
   *(buffer + 2) = (value & 0x0000ff00) >> 8;
   *(buffer + 3) = (value & 0x000000ff);

   return *memory;
}

//static
const server::DataBlock& server::functions::encode (const std::string& domain)
   throw (Exception)
{
   static DataBlock* memory = NULL;

   if (memory == NULL)
      memory = new DataBlock;

   DataBlock& buffer (*memory);
   char* label;
   char* str;

   label = str = strdup (domain.c_str ());

   buffer.clear ();
   while ((label = strtok (label, ".")) != NULL) {
      buffer += strlen (label);
      while (*label) buffer += *label ++;

      // Reset 'label' to continue reading tokens of 'strtok'
      label = NULL;
   }
   buffer += '\0';

   free (str);

   return buffer;
}

// static
server::Short server::functions::decodeShort (const char*& buffer)
   throw ()
{
   int result = *buffer ++;
   result &= 0x000000ff;
   result <<= 8;
   result |= ((int) *buffer ++ & 0x00ff);
   return result;
}


