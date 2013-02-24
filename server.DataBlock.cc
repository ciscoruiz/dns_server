#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <dns.server.DataBlock.h>
#include <dns.server.Exception.h>
#include <dns.server.functions.h>

using namespace std;
using namespace dns;

server::DataBlock::DataBlock (const char* buffer, const int size)
   throw (Exception) :
   a_buffer (NULL),
   a_size (0),
   a_maxSize (0)
{
   initialize (buffer, size);
}

server::DataBlock::DataBlock (const DataBlock& other)
   throw (Exception) :
   a_buffer (NULL),
   a_size (0),
   a_maxSize (0)
{
   initialize (other.a_buffer, other.a_size);
}

server::DataBlock::~DataBlock ()
{
   delete [] a_buffer;
}

void server::DataBlock::initialize (const char* buffer, const int size)
   throw (Exception)
{
   if ((a_maxSize = a_size = size) > 0) {
      if ((a_buffer = new char [size]) != NULL)
         memcpy (a_buffer, buffer, size);
      else
         throw Exception ("Insufficient memory", FILE_LOCATION);
   }
   else
      a_buffer = NULL;
}

void server::DataBlock::allocate (const int nbytes)
   throw (Exception)
{
   if (nbytes > a_size) {
      if (a_maxSize == 0) {
         if ((a_buffer = new char [a_maxSize = nbytes]) == NULL)
            throw Exception ("Insufficient memory", FILE_LOCATION);
      }
      else
         extend (nbytes - a_size);

      a_size = nbytes;
   }
}

void server::DataBlock::setSize (const int size)
   throw (Exception)
{
   if (size > a_maxSize)
      allocate (size);
   else
      a_size = size;
}

void server::DataBlock::assign (const char* buffer, const int size)
   throw (Exception)
{
   if (a_size > size) {
     a_size = 0;
     append (buffer, size);
   }
   else {
      delete a_buffer;
      a_buffer = NULL;
      a_maxSize = a_size = 0;
      initialize (buffer, size);
   }
}

server::DataBlock& server::DataBlock::operator = (const server::DataBlock& right)
   throw (Exception)
{
   if (this != &right) {
      a_size = 0;
      append (right.a_buffer, right.a_size);
   }

   return *this;
}

const char server::DataBlock::operator [] (const int pos) const
   throw (Exception)
{
   if (pos >= a_size) {
      std::string msg ("Position: ");
      msg += functions::asString (pos);
      msg += " | Out of range [0,";
      msg += functions::asString (a_size);
      msg += ')';
      throw Exception (msg, FILE_LOCATION);
   }
   return a_buffer [pos];
}

char& server::DataBlock::operator [] (const int pos)
   throw (Exception)
{
   if (pos >= a_size) {
      std::string msg ("Position: ");
      msg += functions::asString (pos);
      msg += " | Out of range [0,";
      msg += functions::asString (a_size);
      msg += ')';
      throw Exception (msg, FILE_LOCATION);
   }
   char* aux = const_cast <char*> (a_buffer);
   return aux[pos];
}

void server::DataBlock::append (const char* data, const int len)
   throw (Exception)
{
   if (a_buffer == data && data != NULL && len > 0)
      throw Exception ("Can not append myself", FILE_LOCATION);

   if ((a_size + len) >= a_maxSize) extend (len);
   register char* w = a_buffer + a_size;
   switch (len) {
      case 0: break;
      case 1: *w = *data; a_size ++; break;
      case 2: *w = *data; *(w + 1) = *(data + 1); a_size += 2; break;
      case 3: *w = *data; *(w + 1) = *(data + 1); *(w + 2) = *(data + 2); a_size += 3; break;
      case 4: *w = *data; *(w + 1) = *(data + 1); *(w + 2) = *(data + 2); *(w + 3) = *(data + 3); a_size += 4; break;
      default: memcpy (w, data, len); a_size += len; break;
   }
}

void server::DataBlock::remove (const int pos, const int nbytes)
   throw (Exception)
{
   if (pos >= a_size || pos < 0)
      throw Exception ("Position out of range", FILE_LOCATION);

   const int nbytesToMove = a_size - (pos + nbytes);

   if (nbytesToMove < 0)
      throw Exception ("nbytes out of range", FILE_LOCATION);

   if (nbytesToMove > 0)
      memmove (a_buffer + pos, a_buffer + pos + nbytes, nbytesToMove);

   a_size -= nbytes;
}

void server::DataBlock::remove (const int nbytes)
   throw (Exception)
{
   if (nbytes == 0)
      return;

   const int nbytesToMove = a_size - nbytes;

   if (nbytesToMove < 0)
      throw Exception ("nbytes out of range", FILE_LOCATION);

   if (nbytesToMove > 0)
      memmove (a_buffer, a_buffer + nbytes, nbytesToMove);

   a_size -= nbytes;
}

void server::DataBlock::extend (const int nbytes)
   throw (Exception)
{
   if ((a_size + nbytes) < a_maxSize)
      return;

    int newSize = ((a_size + nbytes)  << 1) - ((a_size + nbytes)  >> 1);
    char* newBuffer = new char [newSize];

    if (newBuffer == NULL)
       throw Exception ("Insufficient memory", FILE_LOCATION);

    if (a_size > 0)
       memcpy (newBuffer, a_buffer, a_size);

    delete [] a_buffer;
    a_buffer = newBuffer;
    a_maxSize = newSize;
}

std::string server::DataBlock::asString (const int characterByLine) const
   throw ()
{
   char aux [8];
   std::string numbers;
   std::string characters;
   unsigned char c;
   int i;

   std::string result;

   if (a_size == 0) {
      result = "<null>";
      return result;
   }
  
   result += " (";
   result += functions::asHexString (dns_ptrnumber_cast (a_buffer));
   result += "):";

   for (i = 0; i < a_size; i ++) {
      if ((i % characterByLine) == 0) {
         if (i > 0) {
            result += '\n';
            result += numbers;
            result += "  ";
            result += characters;
            characters.clear ();
         }
         sprintf (aux, "%4d: ", i);
         numbers = aux;
      }

      c = (unsigned char) a_buffer [i];
      sprintf (aux, "%02x ", c);
      numbers += aux;
      characters += (isprint (c) ? (char) c: '.');
   }

   result += '\n';
   result += numbers;
   while ((i % characterByLine) != 0) {
      result += "   ";
      i ++;
   }
   result += "  ";
   return result += characters;
}

