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
	char html[] = "<html><head><script></script></head><body><a href='http://google.com'>redirect to</a><div><a href='http://twitter.com'></a></div><div><a href='http://facebook.com'></a></div><p>The test html</p></body></html>";
	//char html[] = "<body><a href='http://google.com'></a><p>The test html</p></body>";
	/*
	Dom *d = tokenize(html);
	cout<<d->get_name()<<endl; //html
	cout<<d->get_children().size()<<endl;  //2
	cout<<d->get_children()[0]->get_name()<<endl;  //head
	cout<<d->get_children()[0]->get_children().size()<<endl;  //1
	cout<<d->get_children()[1]->get_name()<<endl;  //body
	cout<<d->get_children()[1]->get_children().size()<<endl;  //4
	cout<<d->get_children()[1]->get_children()[0]->getLink()<<endl; // 'http//google.com'
	cout<<d->get_children()[1]->get_children()[0]->getText()<<endl; // 'resirect to'
	cout<<d->get_children()[1]->get_children()[3]->getText()<<endl; // 'The test html'
	cout<<d->find("href")[0]->getLink()<<endl;  // 'http://google.com'
	cout<<d->find("href")[1]->getLink()<<endl;  // 'http://twitter.com'
	cout<<d->find("a")[2]->getLink()<<endl;    // 'http://facebook.com'
	*/
	/*
	char html2[] = "<html><head><script><img src='/images/second.png'></script></head><body><div class='header-top'><div class='logo'><a href='/'><img src='/images/logooo.png'></a></div><div class='header-search'><form action='/search' id='header-search-form'><input type='text' id='search-box' name='school' class='school' placeholder='搜索学校,如: Stanford University'><ul class='search-dropdown'></ul><span type='submit' id='search-button'><i class='icon icon-search'></i></span></form></div></div></body></html>";
	Dom *d = tokenize(html2);
	*/
	char filename[] = "test.html";
	Dom *d = parse_html(filename);
	cout<<d->get_name()<<endl; //html
	cout<<d->get_children().size()<<endl;  //2
	cout<<d->get_children()[0]->get_name()<<endl;  //head
	cout<<d->get_children()[0]->get_children().size()<<endl; // 1
	cout<<d->get_children()[0]->get_children()[0]->get_name()<<endl; //script
	cout<<d->get_children()[1]->get_children()[0]->get_children()[0]->find("a")[0]->getLink()<<endl;  // '/'
	cout<<d->find("img")[1]->getImg()<<endl;	// '/images/logooo.png'
	cout<<d->get_children()[1]->get_children()[0]->get_attrs()[0]->value<<endl;
	cout<<d->find("\"logo\"")[0]->find("a")[0]->getLink()<<endl;  //  /
	delete(d);
	// issue solved: img, input, form tag has no terminate tag

}
