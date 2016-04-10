#include <map>
#include <cstring>

using namespace std;

map<string, bool> m;

void populate_no_paired(){
  m["button"] = true;
  m["br"] = true;
  m["col"] = true;
  m["hr"] = true;
	m["img"] = true;
	m["input"] = true;
}
