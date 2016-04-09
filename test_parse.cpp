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
	char html[] = "<html><head><script></script></head><body><a href='http://google.com'>redirect to</a><div><a href='http://twitter.com'></a></div><div></div><p>The test html</p></body></html>";
	//char html[] = "<body><a href='http://google.com'></a><p>The test html</p></body>";
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
	//print_attrs(d->get_children()[1]->get_children()[0]->get_attrs());
	delete(d);
}
