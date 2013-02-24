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

1.- Ejecuci�n
-----------------------

La siguientes archivos son los necesarios para realizar las pruebas del servidor DNS:
	- server: Ejecutable del proyecto generado sobre un kernel Linux 2.6.38 en modo 32 Bits.
	- table.dns: Archivo que contiene un ejemplo de fichero de correspondencias (Dominio, HostAddres) usadas por el servidor.
	- go: Inicia la ejecuci�n del servidor DNS usando el fichero de ejemplo y activa la visualizaci�n de las trazas generadas por el proceso.
   	- dig-found.sh: Script que invoca a DIG para enviar una consulta de un dominio que estar�a registrado en el servidor.
	- dig-fault.sh: Script que invoca a DIG para enviar una consulta de un dominio que no estar�a registrado en el servidor.


2.- Generaci�n
-----------------------

El fichero Makefile contiene las dependencias necesarias para generar el ejecutable 'server'.

El ejecutable est� incluido en la entrega, pero se podr�a volver a generar invocando al 
comando 'make' desde el directorio que contiene el proyecto.

Para asegurar que partimos desde cero habr�a que invocar a 'make clean', para eliminar 
cualquier archivo intermedio y 'make' para re-generar el archivo ejecutable a partir de los 
fuentes contenidos en el proyecto.

Antes de re-generar el archivo ejecutable del servidor (server) habr�a que asegurarse de 
que �ste no est� en ejecuci�n, ya que de otro modo se podr�a dar un error de escritura.


3.- Codificaci�n
-----------------------

A la hora de codificar he seguido algunas de las t�cnicas explicadas en el libro:

Efficient C++ Performance Programming Techniques
By Dov Bulka, David Mayhew
Publisher : Addison Wesley
Pub Date : November 03, 1999
ISBN: 0-201-37950-3

3.1.- Nombrado de archivos
---------------------------

En la codificaci�n del proyecto he tratado de mostrar un resumen de las t�cnicas que usado 
habitualmente, y que est�n sido usadas actualmente en grandes proyectos.

	- La correspondencia entre una clase y un archivo de cabecera es un�voca. 
	- Si una clase precisa de una archivo fuente (adem�s del archivo de cabecera) �ste 
 	  s�lo contendr� la definici�n de esta clase.

El nombrado de la clase seguir� la regla 
	<proyecto>::{subsistema::*}{agrupacion::*}{subsistema::*}{Nombre de clase}.h

Donde proyecto, subsistema y componente corresponder�a a nombres de namespaces C++. Los '::' se 
traducir�n como '.' en el nombre del archivo de cabecera.

El <subsistema> representa una agrupaci�n l�gica que por cualquier causa conviene al proyecto. 

El <componente> representa o librer�a o un ejecutable y que puede, a su vez, contener agrupaciones 
otras l�gicas.

De esta forma cuando en un proyecto de tama�o medio o grande requerimos del uso de la clase 
sdp::frontend::comm::Address sabemos que el archivo de cabecera correspondiente ser� 
sdp.frontend.comm.Address.h, y tenemos una pista del componente (librer�a) en la que 
estar� implementada.

3.2.- Las clases del proyecto
-------------------------------

El archivo uml.structure.gaphor contiene el diagrama de clases est�tico. El archivo 
uml.structure.png permite visualizar la estructura de clases sin disponer de la 
herramienta Gaphor.

A continuaci�n presentamos un breve resumen de cada una de las clases del proyecto.

* dns::server::Application.
	- Header: ./include/dns.server.Application.h
	- Source: ./server.Application.cc
	- N�cleo principal del proyecto. Gestiona la creaci�n, inicializaci�n y destrucci�n 
	  de los objetos implicados en la soluci�n del problema. Desarrolla la ejecuci�n de la 
	  tarea propiamente dicha.

* dns::server::DataBlock.
	- Header: ./include/dns.server.DataBlock.h
	- Source: ./server.DataBlock.cc
	- Bloque de memoria reutilizable. 

* dns::server::DatagramSocket:
	- Header: ./include/dns.server.DatagramSocket.h
	- Source: ./server.DatagramSocket.cc
	- Implementaci�n del socket UDP por el que se recuperan las queries DNS.

* dns::server::Exception:
	- Header: ./include/dns.server.Exception.h
	- Source: ./server.Exception.cc
	- Excepci�n lanzada por las clases cuando se detecta alg�n problema cuyo tratamiento no est� especificado.

* dns::server::Logger:
	- Header: ./include/dns.server.Logger.h
	- Source: ./server.Logger.cc
	- Ofrece funcionalidad b�sica para registrar las operaciones del proceso sobre un archivo.

* dns::server::Resolver:
	- Header: ./include/dns.server.Resolver.h
	- Source: ./server.Resolver.cc
	- Implementaci�n m�nima de una tabla HASH que permite localizar el dominio que llega como 
	  consulta con una eficiencia te�rica de O(1). Si el n�mero de entradas del diccionario 
	  es muy grande la eficiencia se degradar�a, pero s�lo habr�a que repensar un poco el dise�o 
	  de esta clase para que fuera capaz de reubicar m�s cubetas cuando detecte que el n� de 
	  colisiones de la HASH est� alcanzando un nivel demasiado alto.

	  Las colisiones de la tabla HASH se soluciona mediante dns::server::SingleList<T>.

  	  La funci�n HASH del nombre de dominio se calcular� con la funci�n dns::server::functions::hash (const char*).

* dns::server::SingleList<T>.
	- Header: ./include/dns.server.SingleList.h
	- Implementaci�n b�sica de una lista enlada. Ser� usada por la tabla HASH para resolver las posibles colisiones.

La RFC1035 describe las operaciones y los formatos de los elementos contenidos en los mensajes 
recibidos y env�ados.  Todas las clases que implementan aspectos relacionados con este RFC estar�n 
definidas en el namespace rfc1035. En un proyecto a m�s largo plazo estar�an separadas en una 
librer�a independiente.

* dns::server::rfc1035::Header: 
	- Header: ./rfc1035.db/include/dns.server.rfc1035.Header.h
	- Source: ./rfc1035.db/rfc1035.Header.cc
	- Estructura HEADER descrita en la RFC1035. Actuar� como clase base de las peticiones 
	  y las respuestas.

* dns::server::rfc1035::Query:
	- Header: ./rfc1035.db/include/dns.server.rfc1035.Query.h
	- Source: ./rfc1035.db/rfc1035.Query.cc
	- Modela la decodificaci�n de las peticiones descritas en la RC1035. Combina las operaciones 
	  de su clase base (rfc1035::Header) y rfc1035::QuestionSection.

* dns::server::rfc1035::Response:
	- Header: ./rfc1035.db/include/dns.server.rfc1035.Response.h
	- Source: ./rfc1035.db/rfc1035.Response.cc
	- Modela la codificaci�n de las respuestas descritas en la RFC1035. Combina las operaciones 
	  de su clase base (rfc1035::Header), rfc1035::QuestionSection y rfc1035::AnswerSection. 
	  Por definici�n la respuesta contiene, a su vez, la rfc1035::QuestionSection que estaba 
	  incluida en la petici�n, para favorecer la reutilizaci�n he preferido separar las distintas 
	  secciones en distintas clases.

* dns::server::rfc1035::QuestionSection:
	- Header: ./rfc1035.db/include/dns.server.rfc1035.QuestionSection.h
	- Source: ./rfc1035.db/rfc1035.QuestionSection.cc
	- Modela la codificaci�n/decodificaci�n de la secci�n que contiene la petici�n que recibe 
	  nuestro servidor DNS. 

* dns::server::rfc1035::AnswerSection:
	- Header: ./rfc1035.db/include/dns.server.rfc1035.AnswerSection.h
	- Source: ./rfc1035.db/rfc1035.AnswerSection.cc
	- Modela la codificaci�n de la secci�n que contiene la respuesta de nuestro servidor DNS. 
	  No es directamente reutilizada pero he preferido destarcala como una clase independiente 
	  por mantener la homogeneidad respecto a la secci�n descrita por 'QuestionSection'.

* dns::server::rfc1035::MessageBody:
	- Header: ./rfc1035.db/include/dns.server.rfc1035.MessageBody.h
	- Clase auxiliar que permite indicar d�nde termina la cabecera del mensaje y d�nde comienza
	  la secci�n con la pregunta. 


4.- Agradecimientos
------------------------

Tengo que agradecer a Tom�s Orti que me ayud� a acotar hasta d�nde ten�a que llegar la implementaci�n
de las RFC's que describen la actuaci�n de un servidor DNS (RFC1035 y RFC1034).



