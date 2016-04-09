#ifndef DOM_H
#define DOM_H
#include "tag_object.h"

class Dom{
		startTag *self;
		Dom *parent;
		vector<Dom*> children;
	public:
		Dom(startTag*, Dom*);

		vector<attribute*> get_attrs();

		string get_name();

		string getText();

		Dom* get_parent();

		void set_parent(Dom *p);

		vector<Dom*> get_children();

		void add_child(Dom *d);

		// check whether the str is same as
		// the tag name, name attribute of id attribute
		bool is_tag(string str);

		bool is_name(string n);

		bool is_id(string i);

		bool is_href(string link);

		bool has_attribute(string attr_name);
		
		bool has_link();

		string getLink();

		vector<Dom*> find(string filter);

		~Dom();
};

void find_helper(Dom *me, vector<Dom*> &result, string filter);

#endif
