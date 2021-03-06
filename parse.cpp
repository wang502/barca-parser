#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <exception>
#include <stack>
#include <unordered_map>
#include "Dom.h"
#include "no_end_tag_map.h"

using namespace std;

#define MAX_BUF_SIZE 10000

extern map<string, bool> m;

// print an attribute of html tag
void print_attr(attribute* attr){
	cout<<"name: "<<attr->name<<" ";
	cout<<"value: "<<attr->value<<endl;
}

// print a vector of attribute of html tag
void print_attrs(vector<attribute*> attrs){
	for (int i=0; i<attrs.size();i++){
		print_attr(attrs[i]);
	}
}

// extract the attributes in a start tag
vector<attribute*> extract_attrs(string str){
	vector<attribute*> attrs;
	vector<string> words;
	string sep1 = "=";
	string sep2 = " ";
	int start = 0, end1=0, end2=0;

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

		// contains '=', then contains attributes
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
					//cout<<"text: "<<text<<endl;
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
			// having text
			if (*(strtag.end()-1) != '>'){
				// extract text
				string extracted_text = strtag.substr(strtag.find(">")+1);
				text = extracted_text;
			}
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

// Read HTML text into buffer
void read_html(char *filename, char *buf){
	FILE *fp = fopen(filename, "r");
	if (fp != NULL){
		size_t newLen = fread(buf, sizeof(char), MAX_BUF_SIZE, fp);
		if (newLen == 0){
			cout<<"Error reading HTML file"<<endl;
		}
		else {
			buf[newLen++] = '\0';
		}
	}
	else {
		cout<<"File not found"<<endl;
	}
	fclose(fp);
}

 //🤓//Tokenize the HTML buffer and parse the elements to Dom object
Dom* tokenize(char *html_buf){
	// populate m with no-paired tag names
	populate_no_paired();

	char *pch;
	pch = strtok(html_buf, "<");
	string current_tag;
	stack<Dom*> s;
	Dom *current_dom = NULL;
	Dom *last_dom = NULL;
	Dom *result = NULL;
	s.push(last_dom);
	while (pch != NULL){
		if (*pch == '/'){
			struct endTag *et = create_end_tag(pch);
			last_dom = s.top();
			if (last_dom->get_name() == et->name){
				  result = s.top();
					s.pop();
			}
		}
		else {
			struct startTag *st = create_start_tag(pch);
			last_dom = s.top();
			current_dom = new Dom(st, last_dom);
			if (last_dom != NULL){
				last_dom->add_child(current_dom);
			}
			if (m.find(st->name)==m.end()){
				s.push(current_dom);
			}
			//s.push(current_dom);
		}
		//cout<<pch<<endl;
		pch = strtok(NULL, "<");
	}
	return result;
}

// Parse html
Dom* parse_html(char *filename){
	char html_buf[MAX_BUF_SIZE+1];
	read_html(filename, html_buf);
	Dom *d = tokenize(html_buf);
	return d;
}
