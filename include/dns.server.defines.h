#ifndef _dns_server_defines_h
#define _dns_server_defines_h

#include <sys/types.h>

#ifdef FILE_LOCATION
#undef FILE_LOCATION
#endif
#define FILE_LOCATION (const char*)__FILE__,(const int)__LINE__

#ifndef _NOTRACE
#define LOGWARNING(a) if (dns::server::Logger::isActive (dns::server::Logger::Warning) == true) {a;}
#define LOGNOTICE(a) if (dns::server::Logger::isActive (dns::server::Logger::Notice) == true) {a;}
#define LOGINFORMATION(a) if (dns::server::Logger::isActive (dns::server::Logger::Information) == true) {a;}
#define LOG_EXCL_INFORMATION(a) if (dns::server::Logger::isActive (dns::server::Logger::Debug) == false && dns::server::Logger::isActive (dns::server::Logger::Information) == true) {a;}
#define LOGDEBUG(a) if (dns::server::Logger::isActive (dns::server::Logger::Debug) == true) {a;}
#define LOGLOCAL0(a) if (dns::server::Logger::isActive (dns::server::Logger::Local0) == true) {a;}
#define LOGLOCAL1(a) if (dns::server::Logger::isActive (dns::server::Logger::Local1) == true) {a;}
#define LOGLOCAL2(a) if (dns::server::Logger::isActive (dns::server::Logger::Local2) == true) {a;}
#define LOGLOCAL3(a) if (dns::server::Logger::isActive (dns::server::Logger::Local3) == true) {a;}
#define LOGLOCAL4(a) if (dns::server::Logger::isActive (dns::server::Logger::Local4) == true) {a;}
#define LOGLOCAL5(a) if (dns::server::Logger::isActive (dns::server::Logger::Local5) == true) {a;}
#define LOGLOCAL6(a) if (dns::server::Logger::isActive (dns::server::Logger::Local6) == true) {a;}
#define LOGLOCAL7(a) if (dns::server::Logger::isActive (dns::server::Logger::Local7) == true) {a;}
#define LOGMETHOD(a) a;
#define LOGFUNCTION(a) a;
#else
#define LOGWARNING(a)
#define LOGNOTICE(a)
#define LOGINFORMATION(a)
#define LOGDEBUG(a)
#define LOGLOCAL0(a)
#define LOGLOCAL1(a)
#define LOGLOCAL2(a)
#define LOGLOCAL3(a)
#define LOGLOCAL4(a)
#define LOGLOCAL5(a)
#define LOGLOCAL6(a)
#define LOGLOCAL7(a)
#define LOGMETHOD(a)
#define LOGFUNCTION(a)
#endif

namespace dns {

namespace server {

   /**
      Definicion de un entero con signo de 64 bits.
   */
   #ifdef __sun
      #ifndef __sparcv9
         typedef longlong_t Integer64;
         typedef u_longlong_t Unsigned64;

         /**
          * Tipo de dato requerido para convertir un puntero a un numero entero.
          */
         typedef int ptrnumber;
      #else
         #define __dns_server64__
         typedef long Integer64;
         typedef unsigned long Unsigned64;

         /**
          * Tipo de dato requerido para convertir un puntero a un numero entero.
          */
         typedef long ptrnumber;
      #endif
   #endif

   /**
      Definicion de un entero con signo de 64 bits.
   */
   #ifdef __linux__
      #ifndef __x86_64__
         typedef int64_t Integer64;
         typedef u_int64_t Unsigned64;

         /**
          * Tipo de dato requerido para convertir un puntero a un numero entero.
          */
         typedef int ptrnumber;
      #else
         #define __dns_server64__
         typedef long Integer64;
         typedef unsigned long Unsigned64;

         /**
          * Tipo de dato requerido para convertir un puntero a un numero entero.
          */
         typedef long ptrnumber;
      #endif
   #endif

typedef int Short;

}
}

/**
 * Permite realizar la conversion de puntero a numero de forma correctamente, independientemente
 * de la architectura usada.
 * En 32 bits los punteros se pueden convertir a 'int', pero en 64 bits debe convertirse a 'long'.
 */
#define dns_ptrnumber_cast(pointer) (dns::server::ptrnumber)((void*)(pointer))

#endif

