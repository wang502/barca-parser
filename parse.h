#ifdef PARSE_H
#define PARSE_H

vector<attribute*> extract_attrs(string str);

char* parse_tag(char *tag, vector<attribute*>& attrs, string &text);

struct endTag* create_end_tag(char *tag);

struct startTag* create_start_tag(char *tag);

void tokenize(char *html);

#endif
