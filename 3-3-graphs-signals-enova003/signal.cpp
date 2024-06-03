#include <iomanip>
#include <fstream>
#include <iostream>

#include "switch.h"
#include "network.h"

using namespace std;


void signalStrength (istream& in)
{
	  Network netw;
	  netw.read (in);
	  double s = netw.findSignalStrength ();
	  cout << "Final signal strength: " << setprecision(4)
	       << s << endl;
}

int main (int argc, char** argv)
{
  if (argc == 1)
    signalStrength(cin);
  else
    { // Debugging option
      ifstream in (argv[1]);
      signalStrength (in);
    }
  return 0;
}
