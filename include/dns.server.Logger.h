#ifndef _dns_server_Logger_h
#define _dns_server_Logger_h

#include <syslog.h>

#include <dns.server.Exception.h>

#include <fstream>

namespace dns {

namespace server {

class DataBlock;

/**
   Facilidad para la realizacion de archivos de historico (logs) de nuestra aplicacion.

   @see Patron proxy  http://maniaco/nemesis/docs/html/DesingPatterns//pat4gfso.htm
   @author francisco.antonio.ruiz.rayo@ericsson.com cisco.tierra@gmail.com.
*/
class Logger {
public:
   /**
      Nivel de las trazas de historico.
      @author francisco.antonio.ruiz.rayo@ericsson.com cisco.tierra@gmail.com.

      Para mas informacion ver los niveles de emergencia listados en: man syslog.conf

      @see Logger
   */
   enum Level {
      Emergency = LOG_EMERG,
      Alert = LOG_ALERT, Critical = LOG_CRIT, Error = LOG_ERR, Warning = LOG_WARNING,
      Notice = LOG_NOTICE, Information = LOG_INFO, Debug = LOG_DEBUG,
      Local0 = LOG_LOCAL0, Local1 = LOG_LOCAL1, Local2 = LOG_LOCAL2, Local3 = LOG_LOCAL3,
      Local4 = LOG_LOCAL4, Local5 = LOG_LOCAL5, Local6 = LOG_LOCAL6, Local7 = LOG_LOCAL7
   };

   /**
    * Inicializa el sistema de historico de nuestra aplicacion. Solo debe invocarse una unica vez
    * al comienzo de la aplicacion.
    *
    * Este metodo no es MT-safe por lo que tenemos que estar seguros que no se puede invocar desde
    * varios thread simultaneamente. Lo mas aconsejable es invocarlo desde el comienzo de la
    * aplicacion.
    *
    * @param writer Establece el objeto encargado de transferir los datos de la aplicación
    * al sistema de trazado de operaciones. Esta instancia pasa a ser propieda exclusiva del Logger
    * por lo que será el quién se encargue de liberarla cuando ya no sea necesaria.
   */
   static void initialize (const char* fileName) throw (Exception);

   /**
      @return El nivel de trazado de nuestra aplicacion.
   */
   static Level getLevel () throw () { return st_level; }

   /**
      Establece el nivel de trazado de nuestra aplicacion. El nivel de trazado por defecto
      de nuestra aplicacion dependera del modo de compilacion, en modo depuracion el nivel
      de trazado por defecto sera  Debug, en otro caso sera  Warning.

      Solo apareceran en el historico las trazas que lleven un nivel menor que el establecido
      en este metodo.

      @param level Nivel de trazado que deseamos establecer.
   */
   static void setLevel (const Level level) throw () { st_level = (level <= Error) ? Error: level; }

   /**
      Comprueba si el nivel de trazado recibido como parametro esta activo en nuestra aplicacion.

      @param level Nivel de trazado que deseamos comprobar.

      @return @em true Si el nivel de trazado de nuestra aplicacion es mayor que el recibido como
      parametro o @em false en otro caso.
   */
   static bool isActive (const Level level) throw () {
      return (st_file != NULL && level <= Error) ? true: (level <= st_level && st_file != NULL);
   }

   /**
      Traza el texto recibido en el historico con el nivel indicado.

      La traza solo sera registrada en el historico si el nivel de trazado recibido como
      parametro esta habilitado.

      @param level Nivel de la traza que deseamos registrar.
      @param text Texto de la traza.
      @param fromFile Nombre del archivo donde se genera la traza.
      @param fromLine Numero de linea del archivo donde se genera la traza.
   */
   static void write (const Level level, const char* text, const char* fromFile, const int fromLine) throw ();

   /**
      Traza el texto recibido en el historico con el nivel indicado.

      La traza solo sera registrada en el historico si el nivel de trazado recibido como
      parametro esta habilitado.

      @param level Nivel de la traza que deseamos registrar.
      @param text Texto de la traza.
      @param fromFile Nombre del archivo donde se genera la traza.
      @param fromLine Numero de linea del archivo donde se genera la traza.
   */
   static void write (const Level level, const std::string& text, const char* fromFile, const int fromLine) throw () {
      write (level, text.c_str (), fromFile, fromLine);
   }

   /**
      Traza el texto recibido en el historico con el nivel indicado.

      La traza solo sera registrada en el historico si el nivel de trazado recibido como
      parametro esta habilitado.

      @param level Nivel de la traza que deseamos registrar.
      @param text Texto de la traza.
      @param value Contenido de una cadena.
      @param fromFile Nombre del archivo donde se genera la traza.
      @param fromLine Numero de linea del archivo donde se genera la traza.
   */
   static void write (const Level level, const char* text, const char* value, const char* fromFile, const int fromLine) throw ();

   /**
      Traza el texto recibido en el historico con el nivel indicado.

      La traza solo sera registrada en el historico si el nivel de trazado recibido como
      parametro esta habilitado.

      @param level Nivel de la traza que deseamos registrar.
      @param text Texto de la traza.
      @param value Contenido de una cadena.
      @param fromFile Nombre del archivo donde se genera la traza.
      @param fromLine Numero de linea del archivo donde se genera la traza.
   */
   static void write (const Level level, const char* text, const std::string& value, const char* fromFile, const int fromLine)
      throw ()
   {
      write (level, text, value.c_str (), fromFile, fromLine);
   }

   /**
      Traza el texto recibido en el historico con el nivel indicado.

      La traza solo sera registrada en el historico si el nivel de trazado recibido como
      parametro esta habilitado.

      @param level Nivel de la traza que deseamos registrar.
      @param text Texto de la traza.
      @param value Contenido de una cadena.
      @param fromFile Nombre del archivo donde se genera la traza.
      @param fromLine Numero de linea del archivo donde se genera la traza.
   */
   static void write (const Level level, const std::string& text, const std::string& value, const char* fromFile, const int fromLine)
      throw ()
   {
      write (level, text.c_str (), value.c_str (), fromFile, fromLine);
   }

   /**
      Traza el texto recibido en el historico con el nivel indicado.

      La traza solo sera registrada en el historico si el nivel de trazado recibido como
      parametro esta habilitado.

      @param level Nivel de la traza que deseamos registrar.
      @param text Texto de la traza.
      @param value Valor numerico.
      @param fromFile Nombre del archivo donde se genera la traza.
      @param fromLine Numero de linea del archivo donde se genera la traza.
   */
   static void write (const Level level, const char* text, const int value, const char* fromFile, const int fromLine)
      throw ();

   /**
      Traza el texto recibido en el historico con el nivel indicado.

      La traza solo sera registrada en el historico si el nivel de trazado recibido como
      parametro esta habilitado.

      @param level Nivel de la traza que deseamos registrar.
      @param text Texto de la traza.
      @param value Bloque de datos a transferir al log del sistema.
      @param fromFile Nombre del archivo donde se genera la traza.
      @param fromLine Numero de linea del archivo donde se genera la traza.
   */
   static void write (const Level level, const char* text, const DataBlock& value, const char* fromFile, const int fromLine)
      throw ();

   /**
      Si el nivel \em Debug esta activado traza el texto recibido en el historico.
      @param text Texto de la traza.
      @param fromFile Nombre del archivo donde se genera la traza.
      @param fromLine Numero de linea del archivo donde se genera la traza.
   */
   static void debug (const std::string& text, const char* fromFile, const int fromLine)
      throw ()
   {
      write (Logger::Debug, text, fromFile, fromLine);
   }

   /**
      Si el nivel \em Information esta activado traza el texto recibido en el historico.
      @param text Texto de la traza.
      @param fromFile Nombre del archivo donde se genera la traza.
      @param fromLine Numero de linea del archivo donde se genera la traza.
   */
   static void information (const std::string& text, const char* fromFile, const int fromLine)
      throw ()
   {
      write (Logger::Information, text, fromFile, fromLine);
   }

   /**
      Si el nivel \em Notice esta activado traza el texto recibido en el historico.
      @param text Texto de la traza.
      @param fromFile Nombre del archivo donde se genera la traza.
      @param fromLine Numero de linea del archivo donde se genera la traza.
   */
   static void notice (const std::string& text, const char* fromFile, const int fromLine)
      throw ()
   {
      write (Logger::Notice, text, fromFile, fromLine);
   }

  /**
      Si el nivel \em Warning esta activado traza el texto recibido en el historico.
      @param text Texto de la traza.
      @param fromFile Nombre del archivo donde se genera la traza.
      @param fromLine Numero de linea del archivo donde se genera la traza.
   */
   static void warning (const std::string& text, const char* fromFile, const int fromLine)
      throw ()
   {
      write (Logger::Warning, text, fromFile, fromLine);
   }

  /**
      Si el nivel \em Error esta activado traza el texto recibido en el historico.
      @param text Texto de la traza.
      @param fromFile Nombre del archivo donde se genera la traza.
      @param fromLine Numero de linea del archivo donde se genera la traza.
   */
   static void error (const std::string& text, const char* fromFile, const int fromLine)
      throw ()
   {
      write (Logger::Error, text, fromFile, fromLine);
   }

  /**
      Si el nivel \em Critical esta activado traza el texto recibido en el historico.
      @param text Texto de la traza.
      @param fromFile Nombre del archivo donde se genera la traza.
      @param fromLine Numero de linea del archivo donde se genera la traza.
   */
   static void critical (const std::string& text, const char* fromFile, const int fromLine)
      throw ()
   {
      write (Logger::Critical, text, fromFile, fromLine);
   }

  /**
      Si el nivel \em Alert esta activado traza el texto recibido en el historico.
      @param text Texto de la traza.
      @param fromFile Nombre del archivo donde se genera la traza.
      @param fromLine Numero de linea del archivo donde se genera la traza.
   */
   static void alert (const std::string& text, const char* fromFile, const int fromLine)
      throw ()
   {
      write (Logger::Alert, text, fromFile, fromLine);
   }

  /**
      Si el nivel \em Emergency esta activado traza el texto recibido en el historico.
      @param text Texto de la traza.
      @param fromFile Nombre del archivo donde se genera la traza.
      @param fromLine Numero de linea del archivo donde se genera la traza.
   */
   static void emergency (const std::string& text, const char* fromFile, const int fromLine)
      throw ()
   {
      write (Logger::Emergency, text, fromFile, fromLine);
   }

   /**
      @return La cadena que identifica al nivel recibido como parametro.

   */
   static const char* asString (const Level level) throw ();

   /**
      Traduce la cadena recibida al nivel correspondiente.

      @param level Cadena que deberia contener un nombre de nivel (emerg, alert, crit, err, warning, notice, info, debug).

      \warning Debe de ser alguno de los siguiente literales: emerg, alert, crit, err, warning, notice, info, debug
   */
   static Level asLevel (const char* level) throw (Exception);

private:
   static Level st_level;
   static std::ofstream* st_file;

   Logger ();
};

}
}

#endif


