#include <map>
#include <cstring>

using namespace std;

map<string, bool> m;

void populate_no_paired(){
  m["area"] = true;
  m["button"] = true;
  m["br"] = true;
  m["col"] = true;
  m["embed"] = true;
  m["hr"] = true;
	m["img"] = true;
	m["input"] = true;
  m["meta"] = true;
  m["wbr"] = true;
}
