#include <iostream>

#include <dns.server.Application.h>

using namespace std;
using namespace dns;

int main(int argc, char **argv)
{
   server::Application app;

   try {
      app.initialize (argc, argv);
      app.run ();
   }
   catch (server::Exception& ex) {
     cout << endl << ex.asString () << endl;
     ex.trace ();
   }

   cout << "DNS-Server is stopped" << endl;
}
