// g++ -O3 GanitaEdge.c -o GanitaEdge -lm
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

class GanitaEdge
{
private:
  vector<string> order_name;
  long order_code;
public:
  GanitaEdge();
  long minCheck();
};

GanitaEdge::GanitaEdge()
{
  order_name.push_back("Node-Index");
  order_code = 0;
}

long GanitaEdge::minCheck()
{
  
}

