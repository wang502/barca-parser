#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <exception>
#include "tag_object.h"
#include "parse.h"

using namespace std;

void print_attr(attribute* attr){
	cout<<"name: "<<attr->name<<" ";
	cout<<"value: "<<attr->value<<endl;
}

void print_attrs(vector<attribute*> attrs){
	for (int i=0; i<attrs.size();i++){
		print_attr(attrs[i]);
	}
}

/*
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
	startTag(string name, bool start, bool end, vector<attribute*> attrs):name(name), is_start_tag(start), is_end_tag(end), attrs(attrs){}
};

struct endTag{
	string name;
	bool is_end_tag;
	bool is_start_tag;
	endTag(string name, bool end, bool start):name(name),is_end_tag(end), is_start_tag(start){}
};
*/

// extract the attributes in a start tag
vector<attribute*> extract_attrs(string str){
	vector<attribute*> attrs;
	vector<string> words;
	string sep1 = "=";
	string sep2 = " ";
	int start = 0, end1=0, end2=0;;

	while ((str.find(sep1) != string::npos) || (str.find(sep2) != string::npos)){
		end1 = str.find(sep1);
		end2 = str.find(sep2);
		//cout<<end1<<" "<<end2<<endl;		
		if (end1 != string::npos && end2 != string::npos){
			if (end1 < end2){		
				//cout<<end1<<endl;
				words.push_back(str.substr(0, end1));
				str = str.substr(end1+1);
			}
			else {
				//cout<<end2<<endl;
				words.push_back(str.substr(0, end2));
				str = str.substr(end2+1);
			}
		}
		else if (end1 != string::npos){
			//cout<<end1<<endl;
			words.push_back(str.substr(0, end1));
			str = str.substr(end1+1);
		}
		else if (end2 != string::npos){
			//cout<<end2<<endl;
			words.push_back(str.substr(0, end2));
			str = str.substr(end2+1);
		}
		else {
			cout<<"Parsing Error..."<<endl;
		}
	}
	words.push_back(str.substr(start));
	for (int i=0; i<words.size()-1;i+=2){
		attribute *attr = new attribute(words[i], words[i+1]);
		attrs.push_back(attr);
	}
	return attrs;
}


// parse the start/end tag
// returen the tag name & store attributes in attrs
char* parse_tag(char *tag, vector<attribute*>& attrs, string &text){
	if (*tag == '/'){
		tag++;
		char *tagName = new char[10];
		int i=0;
		while (*tag != '>'){
			tagName[i] = *tag;
			tag++;
			i++;
		}
		tagName[i] = '\0';
 		return tagName;
	}
	else {
		string toFind = "=";
		string strtag(tag);
		char *tagName = new char[10];
		
		// contains =, then contains attributes
		if (strtag.find(toFind)!=string::npos){
			int i=0;
			while (strtag[i] != ' '){
				tagName[i] = strtag[i];
				i++;
			}
			tagName[i] = '\0';

			// skip the space
			i++;
			// having texts followed
			if (*(strtag.end()-1) != '>'){
				int sep;
				if ((sep = strtag.find(">")) != string::npos){
					// extract attributes
					string terminate = ">";
					int size = strtag.find(terminate) - (strlen(tagName)+1);
					//cout<<"size "<<size<<endl;
					//cout<<strlen(tagName)<<endl;
					string to_extract_attrs = strtag.substr(i, size);
					attrs = extract_attrs(to_extract_attrs);

					// extract text
					string extracted_text = strtag.substr(strtag.find(">")+1);
					text = extracted_text; 
					return tagName;
				}
				else {
					cout<<"Parsing Error";
					return tagName;
				}
			}
			// not havinf texts followeds
			else{
				string terminate = ">";
				int size = strtag.find(terminate) - (strlen(tagName)+1);
				string to_extract_attrs = strtag.substr(i, size);
				attrs = extract_attrs(to_extract_attrs);
				return tagName;
			}
		}
		// wothout attributes
		else {
			int i=0; 	
			while (strtag[i] != '>'){
				tagName[i] = strtag[i];
				i++;
			}
			tagName[i] = '\0';
			return tagName;
		}
	}
}

// create tag object for start tag
struct endTag* create_end_tag(char *tag){
	char *tagName;
	vector<attribute*> attrs;
	string text;
	try{
		tagName = parse_tag(tag, attrs, text);
	}
	catch(exception& e){
		cout<<"Get tag name exception: "<<e.what()<<endl;
	}
	struct endTag *et;
	if (tagName != NULL){
		string strName(tagName);
		//cout<<strName<<endl;
		et = new endTag(strName, true, false);
	}
	//cout<<et->name<<endl;
	//cout<<et->is_end_tag<<endl;
	return et;
}

// Create tag object for start tag
struct startTag* create_start_tag(char *tag){
	char *tagName;
	vector<attribute*> attrs;
	string t;
	try{
		// when parsing the tag, read in the attributes and text to the tag object
		tagName = parse_tag(tag, attrs, t);
	}
	// catch exeption
	catch(exception& e){
		cout<<"Parse start tag exception: "<<e.what()<<endl;
	}
	struct startTag *st;
	if (tagName != NULL){
		string strName(tagName);
		//cout<<strName<<endl;
		st = new startTag(strName, true, false, attrs);
		st->text = t;
	}
	// cout<<st->name<<endl;
	// cout<<st->is_start_tag<<endl;
	// cout<<st->is_end_tag<<endl;
	// cout<<st->attrs.size()<<endl;
	return st;
}

void tokenize(char *html){
	char *pch;
	pch = strtok(html, "<");
	while (pch != NULL){
		if (*pch == '/'){

		}
		//cout<<pch<<endl;
		pch = strtok(NULL, "<");
	}
}

/*
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
}*/
