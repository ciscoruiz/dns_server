#ifndef _dns_server_Exception_h
#define _dns_server_Exception_h

#include <string>
#include <exception>

namespace dns {

namespace server {

/**
   Excepcion generica usada en las aplicaciones functions.

   @author francisco.antonio.ruiz.rayo@ericsson.com cisco.tierra@gmail.com
*/
class Exception : public std::exception {
public:
   /**
    * Normaliza las acciones que puede tomar un método a la hora de configurar
    * el tratamiento de errores/excepciones.
    * \author francisco.antonio.ruiz.rayo@ericsson.com cisco.tierra@gmail.com
    */
   struct Mode { enum _v { Ignore, Throw, Trace }; };

   /**
      Constructor.
      @param text Texto explicativo de la excepcion.
      @param fromFile Fichero en el que se provoco la situacion de error.
      @param fromLine Linea del fichero en la que se detecto el error.
   */
   Exception (const char* text, const char* fromFile, const int fromLine);

   /**
      Constructor.
      @param text Texto explicativo de la excepcion.
      @param fromFile Fichero en el que se provoco la situacion de error.
      @param fromLine Linea del fichero en la que se detecto el error.
   */
   Exception (const std::string& text, const char* fromFile, const int fromLine);

   /**
      Constructor copia.

      @param other Instancia de la una excepcion a partir de la que vamos a obtener los datos.
   */
   Exception (const Exception& other);

   /**
      Destructor.
   */
   virtual ~Exception () throw () {;}

   // Accesores
   /**
      @return Devuelve el texto explicativo asociado a esta excepcion.
   */
   const std::string& getText () const throw () { return m_text;}

   /**
      @return El nombre del fichero donde se genero la excepcion. Coincidira con el indicado
      en el constructor.
   */
   const char* getFromFile () const { return m_fromFile.c_str (); }

   /**
      @return La linea del fichero donde se genero la excepcion. Coincidira con la indicada
      en el constructor.
   */
   int getFromLine () const throw () { return m_fromLine; }

   /**
      Establecer un codigo de error asociado a esta excepcion.

      @param errorCode Valor a establecer. El significado de este error dependera de la
      interpretacion particular que queramos darle en nuestra aplicacion.
   */
   void setErrorCode (const int errorCode) throw () { m_errorCode = errorCode; }

   /**
      @return El codigo de error asociado a esta excepcion.
   */
   int getErrorCode () const throw () { return m_errorCode; }

   /**
      Operador copia.

      @param right Instancia de la excepcion de la que vamos a obtener los datos.

      @return Referencia a esta instancia.
    */
   Exception& operator = (const Exception& right) throw ();

   /**
      Devuelve una cadena conteniendo toda la informacion referente a la excepcion
      en un formato que sea facil de interpretar.

      @return Instancia de la cadena conteniendo la informacion de la excepcion.
   */
   std::string asString () const throw ();

   /**
      Devuelve una cadena conteniendo toda la informacion referente a la excepcion
      en un formato que sea facil de interpretar.

      Sobreescribe el metodo de la clase base.

      @return Puntero a la cadena conteniendo la informacion de la excepcion.
   */
   const char* what () const throw () { return asString ().c_str (); } 

   /**
      Saca una traza de error en el fichero de log con el texto asociado a este excepcion.

      @see asString
      @see Logger#write
   */
   void trace () const throw ();

protected:
   /**
      Establece el texto asociado a esta excepcion.

      @param text Nuevo texto asociado a esta excepcion.
   */
   void setText (const char* text) throw () { m_text = text; }

   /**
      Establece el texto asociado a esta excepcion.

      @param text Nuevo texto asociado a esta excepcion.
   */
   void setText (const std::string& text) throw () { m_text = text; }

private:
   std::string m_text;
   std::string m_name;
   std::string m_fromFile;
   int m_fromLine;
   int m_errorCode;
};

}
}

#endif
