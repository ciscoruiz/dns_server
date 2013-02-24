dns_server
==========

DNS server 

The requirements are:
- It shall be executable in either Linux, Solaris or HP-UX platform C or C++ language, preferably C++.
- It shall accept a standard DNS query and generate a standard DNS response (Please consult the RFC).
- DNS query support only.
- DNS over UDP only
- The correspondence between host and name should be read from a flat text file of the type /etc/host.
- This host to name relationship can be read when the process starts. It is not necessary to support dynamic updates.
The evaluation criteria are (in order of importance):
- Robustness
- Simplicity
- Efficiency
You cannot use third party source code, at least not a complete application. In case you use some third party code snippet you have to state which one have you chosen, why you have selected it, and the adaptations you have made.
STL libraries and the like cannot be used.

1.- Ejecución
-----------------------

La siguientes archivos son los necesarios para realizar las pruebas del servidor DNS:
	- server: Ejecutable del proyecto generado sobre un kernel Linux 2.6.38 en modo 32 Bits.
	- table.dns: Archivo que contiene un ejemplo de fichero de correspondencias (Dominio, HostAddres) usadas por el servidor.
	- go: Inicia la ejecución del servidor DNS usando el fichero de ejemplo y activa la visualización de las trazas generadas por el proceso.
   	- dig-found.sh: Script que invoca a DIG para enviar una consulta de un dominio que estaría registrado en el servidor.
	- dig-fault.sh: Script que invoca a DIG para enviar una consulta de un dominio que no estaría registrado en el servidor.


2.- Generación
-----------------------

El fichero Makefile contiene las dependencias necesarias para generar el ejecutable 'server'.

El ejecutable está incluido en la entrega, pero se podría volver a generar invocando al 
comando 'make' desde el directorio que contiene el proyecto.

Para asegurar que partimos desde cero habría que invocar a 'make clean', para eliminar 
cualquier archivo intermedio y 'make' para re-generar el archivo ejecutable a partir de los 
fuentes contenidos en el proyecto.

Antes de re-generar el archivo ejecutable del servidor (server) habría que asegurarse de 
que éste no está en ejecución, ya que de otro modo se podría dar un error de escritura.


3.- Codificación
-----------------------

A la hora de codificar he seguido algunas de las técnicas explicadas en el libro:

Efficient C++ Performance Programming Techniques
By Dov Bulka, David Mayhew
Publisher : Addison Wesley
Pub Date : November 03, 1999
ISBN: 0-201-37950-3

3.1.- Nombrado de archivos
---------------------------

En la codificación del proyecto he tratado de mostrar un resumen de las técnicas que usado 
habitualmente, y que están sido usadas actualmente en grandes proyectos.

	- La correspondencia entre una clase y un archivo de cabecera es unívoca. 
	- Si una clase precisa de una archivo fuente (además del archivo de cabecera) éste 
 	  sólo contendrá la definición de esta clase.

El nombrado de la clase seguirá la regla 
	<proyecto>::{subsistema::*}{agrupacion::*}{subsistema::*}{Nombre de clase}.h

Donde proyecto, subsistema y componente correspondería a nombres de namespaces C++. Los '::' se 
traducirán como '.' en el nombre del archivo de cabecera.

El <subsistema> representa una agrupación lógica que por cualquier causa conviene al proyecto. 

El <componente> representa o librería o un ejecutable y que puede, a su vez, contener agrupaciones 
otras lógicas.

De esta forma cuando en un proyecto de tamaño medio o grande requerimos del uso de la clase 
sdp::frontend::comm::Address sabemos que el archivo de cabecera correspondiente será 
sdp.frontend.comm.Address.h, y tenemos una pista del componente (librería) en la que 
estará implementada.

3.2.- Las clases del proyecto
-------------------------------

El archivo uml.structure.gaphor contiene el diagrama de clases estático. El archivo 
uml.structure.png permite visualizar la estructura de clases sin disponer de la 
herramienta Gaphor.

A continuación presentamos un breve resumen de cada una de las clases del proyecto.

* dns::server::Application.
	- Header: ./include/dns.server.Application.h
	- Source: ./server.Application.cc
	- Núcleo principal del proyecto. Gestiona la creación, inicialización y destrucción 
	  de los objetos implicados en la solución del problema. Desarrolla la ejecución de la 
	  tarea propiamente dicha.

* dns::server::DataBlock.
	- Header: ./include/dns.server.DataBlock.h
	- Source: ./server.DataBlock.cc
	- Bloque de memoria reutilizable. 

* dns::server::DatagramSocket:
	- Header: ./include/dns.server.DatagramSocket.h
	- Source: ./server.DatagramSocket.cc
	- Implementación del socket UDP por el que se recuperan las queries DNS.

* dns::server::Exception:
	- Header: ./include/dns.server.Exception.h
	- Source: ./server.Exception.cc
	- Excepción lanzada por las clases cuando se detecta algún problema cuyo tratamiento no está especificado.

* dns::server::Logger:
	- Header: ./include/dns.server.Logger.h
	- Source: ./server.Logger.cc
	- Ofrece funcionalidad básica para registrar las operaciones del proceso sobre un archivo.

* dns::server::Resolver:
	- Header: ./include/dns.server.Resolver.h
	- Source: ./server.Resolver.cc
	- Implementación mínima de una tabla HASH que permite localizar el dominio que llega como 
	  consulta con una eficiencia teórica de O(1). Si el número de entradas del diccionario 
	  es muy grande la eficiencia se degradaría, pero sólo habría que repensar un poco el diseño 
	  de esta clase para que fuera capaz de reubicar más cubetas cuando detecte que el nº de 
	  colisiones de la HASH está alcanzando un nivel demasiado alto.

	  Las colisiones de la tabla HASH se soluciona mediante dns::server::SingleList<T>.

  	  La función HASH del nombre de dominio se calculará con la función dns::server::functions::hash (const char*).

* dns::server::SingleList<T>.
	- Header: ./include/dns.server.SingleList.h
	- Implementación básica de una lista enlada. Será usada por la tabla HASH para resolver las posibles colisiones.

La RFC1035 describe las operaciones y los formatos de los elementos contenidos en los mensajes 
recibidos y envíados.  Todas las clases que implementan aspectos relacionados con este RFC estarán 
definidas en el namespace rfc1035. En un proyecto a más largo plazo estarían separadas en una 
librería independiente.

* dns::server::rfc1035::Header: 
	- Header: ./rfc1035.db/include/dns.server.rfc1035.Header.h
	- Source: ./rfc1035.db/rfc1035.Header.cc
	- Estructura HEADER descrita en la RFC1035. Actuará como clase base de las peticiones 
	  y las respuestas.

* dns::server::rfc1035::Query:
	- Header: ./rfc1035.db/include/dns.server.rfc1035.Query.h
	- Source: ./rfc1035.db/rfc1035.Query.cc
	- Modela la decodificación de las peticiones descritas en la RC1035. Combina las operaciones 
	  de su clase base (rfc1035::Header) y rfc1035::QuestionSection.

* dns::server::rfc1035::Response:
	- Header: ./rfc1035.db/include/dns.server.rfc1035.Response.h
	- Source: ./rfc1035.db/rfc1035.Response.cc
	- Modela la codificación de las respuestas descritas en la RFC1035. Combina las operaciones 
	  de su clase base (rfc1035::Header), rfc1035::QuestionSection y rfc1035::AnswerSection. 
	  Por definición la respuesta contiene, a su vez, la rfc1035::QuestionSection que estaba 
	  incluida en la petición, para favorecer la reutilización he preferido separar las distintas 
	  secciones en distintas clases.

* dns::server::rfc1035::QuestionSection:
	- Header: ./rfc1035.db/include/dns.server.rfc1035.QuestionSection.h
	- Source: ./rfc1035.db/rfc1035.QuestionSection.cc
	- Modela la codificación/decodificación de la sección que contiene la petición que recibe 
	  nuestro servidor DNS. 

* dns::server::rfc1035::AnswerSection:
	- Header: ./rfc1035.db/include/dns.server.rfc1035.AnswerSection.h
	- Source: ./rfc1035.db/rfc1035.AnswerSection.cc
	- Modela la codificación de la sección que contiene la respuesta de nuestro servidor DNS. 
	  No es directamente reutilizada pero he preferido destarcala como una clase independiente 
	  por mantener la homogeneidad respecto a la sección descrita por 'QuestionSection'.

* dns::server::rfc1035::MessageBody:
	- Header: ./rfc1035.db/include/dns.server.rfc1035.MessageBody.h
	- Clase auxiliar que permite indicar dónde termina la cabecera del mensaje y dónde comienza
	  la sección con la pregunta. 


4.- Agradecimientos
------------------------

Tengo que agradecer a Tomás Orti que me ayudó a acotar hasta dónde tenía que llegar la implementación
de las RFC's que describen la actuación de un servidor DNS (RFC1035 y RFC1034).



