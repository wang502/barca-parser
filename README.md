# barca-parser

This is an HTML parser for C++. It parses HTML files into C++ objects. It is implemented according to the [HTML parsing algorithm.](http://www.whatwg.org/specs/web-apps/current-work/multipage/#auto-toc-12)

The reason I name it as barca-parser is because I am a big fan of [FC Barcelona.](http://www.fcbarcelona.com)

## Data structure used in parsing:

###Stack
Stack is used when processing the HTML buffer.

When reading in a starting tag, pop the last Dom object, add the current Dom to last Dom's children list, push to the stack.

When reading in a ending tag, pop the last Dom out of the stack.

The remaining Dom in the Stack is the Dom object that stores all the HTML elements.

### Tree
A Dom object is a recursive tree structure. It contains its tag elements(tag name, attribute pairs) and its list of children.

## Testing
test the parser:

    $ make testparser
    $ ./main

test the Dom object:

    $ make testdom
    $ ./main
