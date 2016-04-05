#include <string>
#include <vector>

using namespace std;

void print_attr(attribute* attr);

void print_attrs(vector<attribute*> attrs);

vector<attribute*> extract_attrs(string str);

char* parse_tag(char *tag, vector<attribute*>& attrs, string &text);

struct endTag* create_end_tag(char *tag);

struct startTag* create_start_tag(char *tag);

void tokenize(char *html);

