// g++ -O3 GanitaNode.c -o GanitaNode -lm
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

class GanitaNode
{
private:
  vector<string> order_name;
  long order_code;
public:
  GanitaNode();
};

GanitaEdge::GanitaNode()
{
  order_name.push_back("Index");
  order_code = 0;
}

