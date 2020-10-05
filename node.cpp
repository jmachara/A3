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
     :data(value), next_nodes()
{

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
     for(int i = 0; i < next_nodes.size(); i++)
     {
          this->next_nodes.at(i) = NULL;
     }
}

