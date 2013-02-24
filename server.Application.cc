#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

#include <dns.server.Application.h>
#include <dns.server.Logger.h>
#include <dns.server.functions.h>

#include <dns.server.DatagramSocket.h>
#include <dns.server.Resolver.h>

#include <dns.server.rfc1035.Query.h>
#include <dns.server.rfc1035.Response.h>

using namespace std;
using namespace dns;

server::Application::Application() :
   datagramSocket (NULL),
   resolver (NULL),
   query (NULL),
   response (NULL)
{
}   

server::Application::~Application() 
{
   delete datagramSocket;
   delete resolver;
   delete query;
   delete response;
}

void server::Application::initialize (const int argc, char* argv [])
   throw (Exception)
{
   int opt;
   const char* traceLevel (NULL);
   char* ipAddress (NULL);
   char* dictionaryName (NULL);
   int port = -1;
   bool isOk = true;
   
   while (isOk == true && (opt = getopt (argc, argv, "d:p:a:t:")) != -1) {
      switch (opt) {
      case 'd':
         if (optarg == NULL) {
            isOk = false;
            break;
         }
         dictionaryName = strdup (optarg);
         break;
      case 'p':
         if (optarg == NULL) {
            isOk = false;
            break;
         }
         if ((port = atoi (optarg)) < 0) {
            isOk = false;
            break;
         }
         break;
      case 'a':
         if (optarg == NULL) {
            isOk = false;
            break;
         }
         ipAddress = strdup (optarg);
         break;
      case 't':
         if (optarg == NULL) {
            isOk = false;
            break;
         }
         Logger::setLevel (Logger::asLevel (optarg));
         break;
      default:
         isOk = false;
         break;
      }
   }

   if (isOk == false || dictionaryName == NULL || port == -1)
      throw Exception ("Usage: -d <dictionary file> -p <port> [-a <UDP address>] [-t <trace level>]", FILE_LOCATION);

   try {
      Logger::initialize ("file.trace");
      
      datagramSocket = new DatagramSocket;
      datagramSocket->initialize (port, ipAddress /* Remember this could be NULL */);
      
      resolver = new Resolver;
      resolver->initialize (dictionaryName);

      query = new rfc1035::Query;
      response = new rfc1035::Response;
   }
   catch (Exception&) {
      free (dictionaryName);
      if (ipAddress != NULL)
         free (ipAddress);
      throw;
   }
}

void server::Application::run () 
   throw (Exception)
{
   const in_addr* hostAddress;
   
   while (true) {
      try {
         query->decode (datagramSocket->read ());
         LOGINFORMATION (Logger::information (query->asString (), FILE_LOCATION));
      }
      catch (Exception& ex){
         ex.trace ();
         continue;
      }
      
      // Links request and response
      response->setID (query->getID ());
      response->setQuestionSection (query->getQuestionSection());
      response->setAnswerSection (query->getQuestionSection());
      response->clearHostAddress ();
      
      if (query->isValid () == true) {
         hostAddress = resolver->apply (query->getQName());

         if (hostAddress != NULL){
            response->setResponseCode (rfc1035::Response::ResponseCode::Ok);
            response->setHostAddress (hostAddress);
         }
         else
            response->setResponseCode (rfc1035::Response::ResponseCode::ServerFailure);
      }
      else
         response->setResponseCode (rfc1035::Response::ResponseCode::Refused);
      
      // If response does not contain domain data, then it will return one error response
      LOGINFORMATION (Logger::information (response->asString (), FILE_LOCATION));
      datagramSocket->write (response->encode ());
   }
}


