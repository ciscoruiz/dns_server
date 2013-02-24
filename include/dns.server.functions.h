#ifndef _dns_server_functions_h
#define _dns_server_functions_h

#include <stdlib.h>

#include <string>

#include <dns.server.defines.h>
#include <dns.server.Exception.h>

#include <time.h>
#include <sys/time.h>

namespace dns {

namespace server {

class DataBlock;

/**
   functions - Métodos básicos de conversión de datos.
   @author francisco.antonio.ruiz.rayo@ericsson.com cisco.tierra@gmail.com.
*/
struct functions {
   /**
      Indica el número de bits de un entero.
   */
   static const int intBitSize = sizeof (int) * 8;

   /*
    * Indica el número de bits de un entero largo.
    */
   static const int int64BitSize = sizeof (Integer64) * 8;

   /**
      \param number Numero a convertir.
      @return Un literal con el numero convertido a cadena decimal.
   */
   static std::string asString (const int number) throw ();

   /**
      \param number Numero a convertir.
      @return Un literal con el numero sin signo convertido a cadena decimal.
   */
   static std::string asString (const unsigned int number) throw ();

   /**
      Devuelve un literal con tel numero convertido a cadena decimal
      @return Un literal con el numero signo convertido a cadena decimal.
   */
   static std::string asString (const Integer64 number) throw ();

   /**
      Devuelve un literal con tel numero convertido a cadena decimal
      @return Un literal con el numero signo convertido a cadena decimal.
   */
   static std::string asString (const Unsigned64 number) throw ();

   /**
      \param _bool Booleano a convertir.
      \return Un literal con el boolean convertido a cadena.
   */
   static const char* asString (const bool _bool) throw () { return (_bool == true) ? "true": "false"; }

   /**
      Devuelve una cadena con el bloque de datos decodificado en grupos de 16 bytes.
      @param dataBlock Bloque de datos a interpretar.
      \param characterByLine Número de caracteres en cada línea.
      @return Devuelve una cadena con el bloque de datos decodificado en grupos de 16 bytes.
   */
   static std::string asString (const DataBlock& dataBlock, const int characterByLine = 16) throw ();

   /**
      Devuelve una cadena con el numero en coma flotante.
      \param v Numero a tratar.
      \param format Formato aplicado para convertir el numero a cadena. Ver \em man printf.
      \return una cadena con el numero en coma flotante.

   */
   static std::string asString (const double v, const char* format="%e") throw ();

   /**
      Devuelve una cadena con el numero en coma flotante.
      \param v Numero a tratar.
      \param format Formato aplicado para convertir el numero a cadena. Ver \em man printf.
      \return una cadena con el numero en coma flotante.

   */
   static std::string asString (const float v, const char* format="%f") throw ();

   /**
      \param comment Comentario que precede al valor.
      \param number Numero a convertir.
      @return Un literal con el numero convertido a cadena decimal.
   */
   static std::string asText (const char* comment, const int number)
      throw ()
   {
      std::string result (comment);
      return result += asString (number);
   }

   /**
      \param comment Comentario que precede al valor.
      \param number Numero a convertir.
      @return Un literal con el numero convertido a cadena decimal.
   */
   static std::string asText (const char* comment, const Integer64 number)
      throw ()
   {
      std::string result (comment);
      return result += asString (number);
   }

   /**
       \param comment Comentario que precede al valor.
       \param _bool Booleano a convertir.
       @return Un literal con el numero convertido a cadena decimal.
    */
    static std::string asText (const char* comment, const bool _bool)
       throw ()
    {
       std::string result (comment);
       return result += asString (_bool);
    }

    /**
       \param comment Comentario que precede al valor.
       \param dataBlock Bloque de datos a interpretar.
       \param characterByLine Número de caracteres en cada línea.
       @return Un literal con el numero convertido a cadena decimal.
    */
    static std::string asText (const char* comment, const DataBlock& dataBlock, const int characterByLine = 16)
       throw ()
    {
       std::string result (comment);
       return result += asString (dataBlock, characterByLine);
    }

    /**
       \param comment Comentario que precede al valor.
       \param value Numero a tratar.
       \param format Formato aplicado para convertir el numero a cadena. Ver \em man printf.
       \return Un literal con el numero convertido a cadena.

    */
    static std::string asText (const char* comment, const float value, const char* format="%f")
       throw ()
    {
       std::string result (comment);
       return result += asString (value, format);
    }

    /**
       \param comment Comentario que precede al valor.
       \param value Numero a tratar.
       \param format Formato aplicado para convertir el numero a cadena. Ver \em man printf.
       \return Un literal con el numero convertido a cadena.

    */
    static std::string asText (const char* comment, const double value, const char* format="%e")
       throw ()
    {
       std::string result (comment);
       return result += asString (value, format);
    }

   /**
      \param number Numero a convertir.
      @return Un literal con el numero convertido a cadena hexadecimal.
   */
   static std::string asHexString (const int number) throw ();

   /**
      \param number Numero a convertir.
      @return Un literal con el numero convertido a cadena hexadecimal.
   */
   static std::string asHexString (const Integer64 number) throw ();

   /**
      \param number Numero a convertir.
      @return Un literal con el numero convertido a cadena hexadecimal.
   */
   static std::string asHexString (const Unsigned64 number) throw () { return asHexString ((Integer64) number); }

   /**
      \param comment Comentario que precede al valor.
      \param number Numero a convertir.
      @return Un literal con el numero convertido a cadena decimal.
   */
   static std::string asHexText (const char* comment, const int number)
      throw ()
   {
      std::string result (comment);
      return result += asHexString (number);
   }

   /**
      \param comment Comentario que precede al valor.
      \param number Numero a convertir.
      @return Un literal con el numero convertido a cadena decimal.
   */
   static std::string asHexText (const char* comment, const Integer64 number)
      throw ()
   {
      std::string result (comment);
      return result += asHexString (number);
   }

  /**
    * Devuelve un cadena con el contenido del bloque de datos interpretado como BCD, pero pasa
    * cada valor binario a su correspondiente carácter. Por ejemplo, el buffer aa210c quedará como una cadena "AA210C".
    *
    * \param dataBlock Bloque a codificar.
    * \return La cadena que contiene el valor literal del buffer de datos.
    *
    */
   static std::string asHexString (const DataBlock& dataBlock) throw ();

   /**
    * Devuelve una cadena indicado las unidades de medida (bytes, KB - Kilobytes MB - Megabytes)
    * en las que está expresada la cantidad.
    */
   static std::string asByte (const int value) throw ();

   /**
      Devuelve la cadena que contiene el resultado de aplicar la especificacion \em format
      sobre el resto de los parametros.

      \param format especificacion de formato similiar al empleado en las funciones \em printf,
      \em scanf, etc.

      \return la cadena que contiene el resultado de aplicar la especificacion \em format
      sobre el resto de los parametros.
   */
   static std::string asString (const char* format, ...) throw ();

   /**
      Interpreta la cadena recibida como parametro como un dato de tipo boolean.

      Si la cadena vale NULL, o contiene los literales "false" o "0" devolvera \em false,
      si contiene los literales "true" o "1" devolvera \em true, en otro caso devolvera un excepcion.

      \param str Cadena a interpretar.

      \return El valor booleano correspondiente a la cadena recibida.
   */
   static bool asBool (const char* str) throw (Exception);

   /**
      Interpreta la cadena recibida como parametro como un entero de 32 bits.
      \return
    */
   static int asInteger (const char* str) throw () { return atoi (str); }

   /**
      Interpreta la cadena recibida como parametro como un entero de 32 bits.
      \return
    */
   static Integer64 asInteger64 (const char* str) throw ();

   /**
    * Devuelve el número de bits necesarios para representar el valor recibido como parámetro.
    * \param n Valor a estudiar.
    * \return el número de bits necesarios para representar el valor recibido como parámetro.
    *
    */
   static int bitsize (const int n) throw () {  return (n == 0) ? 1: functions::log2 (n) + 1; }

   /**
    * Devuelve el número de bits necesarios para representar el valor recibido como parámetro.
    * \param n Valor a estudiar.
    * \return el número de bits necesarios para representar el valor recibido como parámetro.
    *
    */
   static int bitsize (const Integer64 n) throw () {
      register int aux = n >> intBitSize;
      return (aux != 0) ? (bitsize (aux) + intBitSize): bitsize ((int) n);
   }

   /**
    * Calcula el logaritmo en base 2 del número recibo como parámetro.
    * \param v Valor a calcular.
    * \return El algoritmo en base 2 del número recibido como parámetro o -1 si el parámetro recibido es 0.
    */
   static int log2 (const unsigned int v) throw ();
   
   /**
      Calcula la funcion hash de la cadena recibida como parametro.
      \param str Cadena a la que aplicar la funcion hash.
   */
   static Integer64 hash (const char* str) throw ();

   static const DataBlock& encodeShort (const Short value) throw (Exception);
   static const DataBlock& encodeInteger (const int value) throw (Exception);
   static const DataBlock& encode (const std::string& domain) throw (Exception);

   static Short decodeShort (const char*& buffer) throw ();
//   static int decodeInteger (const char*& buffer) throw ();
};

}
}

#endif


