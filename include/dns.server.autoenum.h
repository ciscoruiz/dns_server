#ifndef _dns_server_autoenum_h
#define _dns_server_autoenum_h

#include <string.h>
#include <string>

#include <dns.server.Exception.h>

#define declare_enum(name) \
   static const char* literal []; \
   static _v asEnum (const char* str) throw () { \
      for (int ii = 0; literal [ii] != NULL; ii ++) { \
         if (strcasecmp (str, literal [ii]) == 0) \
            return (_v) ii; \
      } \
      return None; \
   } \
   static _v asEnumEx (const char* str) throw (dns::server::Exception) { \
      if (str == NULL) { \
         std::string msg (#name); \
         msg += "::asEnumEx | str can not be null"; \
         throw dns::server::Exception (msg, __FILE__,__LINE__); \
      } \
      _v result = asEnum (str); \
      if (result == None) { \
         std::string msg (#name); \
         msg += " | Value: '"; \
         msg += str; \
         msg += "' is not valid | Valid values: "; \
         msg += asList (); \
         throw dns::server::Exception (msg, __FILE__, __LINE__); \
      } \
      return result; \
   } \
   static _v asEnum (const std::string& str) throw () { return asEnum (str.c_str ()); } \
   static _v asEnumEx (const std::string& str) throw (dns::server::Exception) { return asEnumEx (str.c_str ()); } \
   static const char* asCString (const _v v) throw () { return (v != None) ? literal [v]: NULL; } \
   static const char* asNotNullCString (const _v v) throw () { return (v != None) ? literal [v]: "<none>"; } \
   static std::string asList () throw () {\
      std::string result;\
      for (register int ii = 0; literal [ii] != NULL; ii ++) { \
         if (ii == 0 && strcmp (literal [ii], "None") == 0) continue; \
         if (ii > 1) result += ' '; \
         result += "'"; result += literal [ii]; result += "'"; \
      } \
      return result; \
   }

/**
 * \page assign_enum
 *
 * Establece los literales asociados a cada uno de los valores de la enumeración.
 *
 * Hay que completar el enumerado asignando los literales asociados a cada uno de los valores:
 *
 * \code
 * assign_enum (diameter::avp::DiameterURI::Transport) = { "tcp", "sctp", "udp", NULL };
 * \endcode
 *
 * \ref declare_enum
 * \warning Debe incluir el valor \em NULL para indicar el fin de la lista de valores.
 */
#define assign_enum(name) const char* name::literal []

/**
 * \page item_enum
 * Accede al literal definido por el Enumado y la posicion indicada como parámetro
 */
#define item_enum(name,ii) name::literal[ii]


#endif 
