#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <exception>
#include <vector>
#include "Dom.h"
#include "parse.h"

using namespace std;

int main(){
	//char html[] = "<html><head><body><a href='http://google.com'><p>The test html</p></body></head></html>";
	//tokenize(html);
	//char tag[] = "div id='layout1' name='l1'>";
	//char *tagName = getTagName(tag);
	//struct startTag *st = createStartTag(tag);
	char chars[] = "<ll name=layout id='l1'>This is paragraph";
	//string str(chars);
	//string sep = "=";
	//cout<<str.find(sep);
	//str = str.substr(0, str.find(sep));
	//cout<<str<<endl;
		
	vector<attribute*> attrs;
	string text;
	char *tagname = parse_tag(chars, attrs, text);
	cout<<tagname<<endl;	
	print_attrs(attrs);
	cout<<"text: "<<text<<endl;
	cout<<endl;
}
