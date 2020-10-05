 /*This node class is used to build linked lists for the
 * string_set class.
 *
 * Jack Machara
 * U1053556
 * Assignment 3
 * September 28, 2020
 */

#include "node.h"
#include <string>
/*
* node constructor
* stores a string value and a vector of pointers to other nodes.
*/
cs3505::node::node(const std::string & value)
{
     this->data = value;
     this->next_nodes;
}
/*
* node destructor
* sets all next pointers to NULL
*/
cs3505::node::~node()
{
     if((this->next_nodes.size() > 0) && (this->next_nodes.front() != NULL))
     {
          delete this->next_nodes.front();
     }
     next_nodes.clear();
}

