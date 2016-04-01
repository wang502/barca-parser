#include <vector>
#include <cstring>

using namespace std;

struct DOCTYPE{
	string name;
	string publicid;
	string sysid;
	bool force_quirks;
};

struct attribute{
	string name;
	string value;
	attribute(string name, string value):name(name), value(value){}
};

struct startTag{
	string name;
	bool is_start_tag;
	bool is_end_tag;
	vector<attribute*> attrs;
	string text;
	startTag(string name, bool start, bool end, vector<attribute*> attrs):name(name), is_start_tag(start), is_end_tag(end), attrs(attrs){}
};

struct endTag{
	string name;
	bool is_end_tag;
	bool is_start_tag;
	endTag(string name, bool end, bool start):name(name),is_end_tag(end), is_start_tag(start){}
};

