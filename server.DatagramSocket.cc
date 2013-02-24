#include <errno.h>
#include <string.h>

#include <iostream>

#include <dns.server.functions.h>
#include <dns.server.DatagramSocket.h>
#include <dns.server.Logger.h>

using namespace std;
using namespace dns;

server::DatagramSocket::DatagramSocket () : stream (-1) 
{
   DataBlock::allocate (1024);
   memset (&clientAddress, 0, sizeof (clientAddress));
   addrLen = 0;
}

server::DatagramSocket::~DatagramSocket () 
{
   if (stream != -1) 
      close (stream);
}

void server::DatagramSocket::initialize (const int port, const char* ip) throw (Exception)
{
   stream = socket (AF_INET, SOCK_DGRAM, 0);

   sockaddr_in address;
   
   address.sin_family = AF_INET;
   address.sin_addr.s_addr = (ip == NULL) ? INADDR_ANY: inet_addr (ip);
   address.sin_port = htons(port);

   if (bind (stream, (struct sockaddr *) &address, sizeof (struct sockaddr_in)) != 0) {
      string msg ("server::DatagramSocket::initialize | Port: ");
      msg += functions::asString (port);
      if (ip != NULL) {
         msg += " | IP: ";
         msg += ip;         
      }
      msg += " | ";
      msg += strerror (errno);
      throw Exception (msg, FILE_LOCATION);
   }

   cout << endl << "DNS-Server attending at " << inet_ntoa (address.sin_addr) << ":" << port << " (fd=" << stream << ")" << endl;
}

const server::DataBlock& server::DatagramSocket::read ()
   throw (Exception)
{
   char* buffer = const_cast <char*> (DataBlock::getData());
   int maxLength = DataBlock::getMaxSize ();

   addrLen = sizeof (struct sockaddr_in);
   int nbytes = recvfrom (stream, buffer, maxLength, 0, (sockaddr *) &clientAddress, &addrLen);

   LOGDEBUG (
      string msg ("server::DatagramSocket::read | Attending to ");
      msg += functions::asString ("%s:%d (fd=%d)", inet_ntoa (clientAddress.sin_addr), ntohs (clientAddress.sin_port), stream);
      Logger::debug (msg, FILE_LOCATION)
   );

   if (nbytes < 0) {
      string msg ("recvfrom: ");
      msg += strerror (errno);
      throw Exception (msg, FILE_LOCATION);
   }

   DataBlock::setSize (nbytes);

   return *this;
}

void server::DatagramSocket::write (const server::DataBlock& message)
   throw (Exception)
{
   LOGDEBUG (
      string msg ("server::DatagramSocket::write | Responding to ");
      msg += functions::asString ("%s:%d (fd=%d)", inet_ntoa (clientAddress.sin_addr), ntohs (clientAddress.sin_port), stream);
      Logger::debug (msg, FILE_LOCATION)
   );

   int rr = sendto (stream, message.getData(), message.getSize(), 0, (sockaddr *) &clientAddress, addrLen);

   if (rr < 0) {
      string msg ("sendto: ");
      msg += strerror (errno);
      throw Exception (msg, FILE_LOCATION);
   }
}

