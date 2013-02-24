#ifndef _dns_server_DataBlock_h
#define _dns_server_DataBlock_h

#include <dns.server.Exception.h>
#include <dns.server.defines.h>

namespace dns {

namespace server {

/**
   Optimizacion de acceso a la memoria dinamica.

   Incrementa el rendimiento al acceder y reservar de memoria dinamica mediante la reutilizacion controlada.

   Para optimizar el acceso no se ha establecido ningun tipo de proteccion para ejecucion MT.

   @author francisco.antonio.ruiz.rayo@ericsson.com cisco.tierra@gmail.com.
*/
class DataBlock {
public:
   /**
     Constructor.
   */
   DataBlock () throw () :
      a_buffer (NULL),
      a_size (0),
      a_maxSize (0)
   {}

   /**
     Constructor.

     @param buffer Bloque de memoria con el que inicializar el buffer de esta instancia.
     @param size Numero de bytes del bloque de memoria recibido.
     @param deepCopy Modo de copia de esta instancia. Si activamos el modo de copia profunda al asignar
     cualquier otro bloque de memoria a este, se reserva la memoria para ubicar el buffer y despues
     realizara una copia byte a byte.
   */
   DataBlock (const char* buffer, const int size) throw (Exception);

   /**
     Constructor copia.
     El modo de copia sera el mismo que el establecido por la instancia de la que copiar.

     @param other Bloque de memoria con el que instanciar esta instancia.
   */
   DataBlock (const DataBlock& other) throw (Exception);

   /**
      Destructor.
   */
   virtual ~DataBlock ();

   // Accesores
   /**
      Éste metodo solo debe usarse en aplicaciones mono-thread o en situaciones en las que estemos seguros
      que esta bloque de datos no puede verse afectado por otro thread.

      @return Tamaño de la memoria reservada por esta instancia.
   */
   int getMaxSize () const throw () { return a_maxSize; }

   /**
      Éste metodo solo debe usarse en aplicaciones mono-thread o en situaciones en las que estemos seguros
      que esta bloque de datos no puede verse afectado por otro thread.

      @return Tamaño del bloque de memoria contenido actualmente.
   */
   int getSize () const throw () { return a_size; }

   /**
      Éste metodo solo debe usarse en aplicaciones mono-thread o en situaciones en las que estemos seguros
      que esta bloque de datos no puede verse afectado por otro thread.

      @return El contenido del bloque de memoria.
   */
   const char* getData () const throw () { return a_buffer; }

   /**
      Devuelve informacion acerca del estado de ocupacion de este bloque de memoria.

     @return \em true si el bloque de memoria esta vacio o \em false en otro caso.
   */
   bool isEmpty () const throw () { return (a_size == 0) ? true: false; }

   /**
      Establece el numero de bytes que tiene asociado a este bloque de datos.
      \param size numero de bytes que tiene asociado a este bloque de datos.
      \warning El DataBlock delega la gestion de la memoria a la clase heredada.
   */
   void setSize (const int size) throw (Exception);

   /**
     Anade el caracter recibido al bloque de memoria. Para poder usar este operador el bloque de
     memoria destino debe tener activado el modo de copia profunda. Si la memoria reservada no es
     suficiente  reservara automaticamente la cantidad de memoria necesaria.

     @param c Caracter a añadir a este bloque de memoria.

     @returns Una referencia a si mismo.
   */
   DataBlock& operator += (const char c) throw (Exception) {
      append (&c, sizeof (c));
      return *this;
   }

   /**
     Anhade el bloque de memoria recibido. Para poder usar este operador el bloque de memoria
     destino debe tener activado el modo de copia profunda. Si la memoria reservada no es
     suficiente reservara automaticamente la cantidad de memoria necesaria.

     @param right Bloque de memoria a añadir a este bloque de memoria.

     @returns Una referencia a si mismo.
   */
   DataBlock& operator += (const DataBlock& right) throw (Exception) {
      if (this != &right)
         append (right.a_buffer, right.a_size);
      return *this;
   }

   /**
     Anade la cadena recibida al bloque de memoria. Para poder usar este operador el bloque de
     memoria destino debe tener activado el modo de copia profunda. Si la memoria reservada no es
     suficiente  reservara automaticamente la cantidad de memoria necesaria.

     \param str Cadena a añadir a este bloque de memoria.

     @returns Una referencia a si mismo.

   */
   DataBlock& operator += (const std::string& str) throw (Exception) {
      append (str.c_str (), str.length ());
      return *this;
   }

   /**
      Devuelve la posicion i-esima del bloque de datos.
      \param pos Posicion a la que acceder.
      \return La posicion i-esima del bloque de datos.
   */
   const char operator [] (const int pos) const throw (Exception);

   /**
      Devuelve la posicion i-esima del bloque de datos.
      \param pos Posicion a la que acceder.
      \return La posicion i-esima del bloque de datos.
   */
   char& operator [] (const int pos) throw (Exception);

   /**
      Anade el bloque de memoria recibido. Para poder usar este operador el bloque de memoria
      destino debe tener activado el modo de copia profunda. Si la memoria reservada no es
      suficiente reservara automaticamente la cantidad de memoria necesaria.

      \param data Direccion donde comienza el bloque de datos.
      \param len Longitud del bloque de datos.
   */
   void append (const char* data, const int len) throw (Exception);

   /**
      Anade el bloque de memoria recibido. Para poder usar este operador el bloque de memoria
      destino debe tener activado el modo de copia profunda. Si la memoria reservada no es
      suficiente reservara automaticamente la cantidad de memoria necesaria.

      \param other Bloque de memoria a añadir.
   */
   void append (const DataBlock& other) throw (Exception) { append (other.a_buffer, other.a_size); }

   /**
     Copia el contenido del bloque recibido como parámetro.
     @param right Bloque de memoria del que copiar.
     @returns Una referencia a si mismo.
   */
   void assign (const DataBlock& right) throw (Exception) { *this = right; }

   /**
     Copia o direcciona el contenido del bloque recibido como parámetro.
     \param buffer Dirección de memoria a direcionar.
     \param size Tamaño de la memoria.
     @returns Una referencia a si mismo.
   */
   void assign (const char* buffer, const int size) throw (Exception);

   /**
     operador copia. El modo de copiar vendra definido por el modo copia con el que hayamos
     iniciado la instancia destino.
     @param right Bloque de memoria del que copiar.
     @returns Una referencia a si mismo.
   */
   DataBlock& operator = (const DataBlock& right) throw (Exception);

   /**
     Operador de inicializacion. El bloque destino debera tener activado el sistema de
     copia profunda.
     @param c Caracter con el que vamos a inicializar el contenido del bloque.
     @returns Una referencia a si mismo.
   */
   DataBlock& operator = (const char c) throw (Exception) { clear (); (*this) += c; return *this; }

   /**
     Operador de inicializacion. El bloque destino debera tener activado el sistema de
     copia profunda.
     @param str Cadena con el que vamos a inicializar el contenido del bloque.
     @returns Una referencia a si mismo.

   */
   DataBlock& operator = (const std::string& str) throw (Exception) { clear (); (*this) += str; return *this; }

   // Metodos
   /**
      Reserva el numero de bytes indicado por el parametro recibido. Si la cantidad de memoria preasignada es mayor
      que la solicitada no se realiza ninguna llamada al sistema operativo.

      @param nbytes Numero de bytes a reservar.
   */
   void allocate (const int nbytes) throw (Exception);

   /**
     La reserva de memoria actual pasa a ser memoria pre-asignada, asi libera el bloque
     de memoria reservado hasta el momento, pero de forma que si posteriormente vuelve a
     ser necesario puede reutilizarlo sin tener que volver a realizar una llamada al
     sistema para obtener memoria dinamica.
   */
   void clear () throw (Exception) { a_size = 0; }

   /**
      Elimina del bloque de memoria unos determinados bytes.

      @param pos Posicion del bloque donde empezar a eliminar.
      @param nbytes Numero de bytes a descartar a partir de la posicion indicada.
   */
   void remove (const int pos, const int nbytes) throw (Exception);

   /**
      Elimina del bloque de memoria los n primeros bytes.
      @param nbytes Numero de bytes a descartar a partir de la posicion indicada.
   */
   void remove (const int nbytes) throw (Exception);

   /**
    * Muestra el contenido de este buffer en forma de buffer hexadecimal vs bytes.
    */
   std::string asString (const int characterByLine = 24) const throw ();

protected:
   /**
      Inicializa el contenido de este bloque de datos. Si fue instancia con copia
      profunda copia el contenido del buffer, en otro caso solo se queda con el
      valor de la referencia de memoria a la que apunta.

      @param buffer Bloque de memoria con el que inicializar el buffer de esta instancia.
      @param size Numero de bytes del bloque de memoria recibido.

   */
   void initialize (const char* buffer, const int size) throw (Exception);

private:
   char* a_buffer;
   int a_size;
   int a_maxSize;

   void extend (const int nbytes) throw (Exception);
};

} 
}

#endif

