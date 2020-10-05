/* A 'string set' is defined as a 	iset of strings stored
 * in sorted order in a drop list.  See the class video
 * for details.
 *
 * For lists that do not exceed 2 ^ (max_width + 1)
 * elements, the add, remove, and contains functions are 
 * O(lg size) on average.  The operator= and get_elements 
 * functions are O(size).   
 * 
 * Jack Machara
 * U1053556
 * Assignment 3
 * September 28, 2020
 */

#include "string_set.h"
#include <iostream>  // For debugging, if needed.
#include <stdlib.h>
namespace cs3505
{
  /*******************************************************
   * string_set member function definitions
   ***************************************************** */
  
  /** Constructor:  The parameter indicates the maximum
    * width of the next pointers in the drop list nodes.
    */
  string_set::string_set(int max_next_width)
  {
      this->max_width = max_next_width;
      this->size = 0;
      this->head = new node("");
      head->next_nodes = std::vector<node*>(max_width, NULL);
  }

  
  /** Copy constructor:  Initialize this set
    * to contain exactly the same elements as
    * another set.
    */
  string_set::string_set (const string_set & other)
  { 
    head = NULL;
	  *this = other;
  }


  /** Destructor:  Release any memory allocated
    * for this object.
    */
  string_set::~string_set()
  {
      clean();	
  }
/**
 *  clears the string_set by recursively deleting nodes
 */
  void string_set::clean()
  {
    if(this->head != NULL)
    {
        delete this->head;
    }
    this->head = NULL;
    this->size = 0;
    this->max_width = 0;
  }
/**
 *  add: adds @target string value to the set via a node
 *  will not add a duplicate string.
 */
  void string_set::add(const std::string & target)
  {
    //point current at the head node and fill the previous node vector with it.
    node *current = head;
    std::vector<node*> prev_nodes = std::vector<node*>(max_width, NULL);
    for(int i = max_width-1; i >= 0; i--)
    {
      //find the node before where we want to add our node
      while((current->next_nodes.at(i) != NULL) && (target.compare(current->next_nodes.at(i)->data) > 0))
      {
          current = current->next_nodes.at(i);
      }
          prev_nodes.at(i) = current;
    } 
    //check for double adding
    if((prev_nodes.front()->next_nodes.front() != NULL) && target.compare(prev_nodes.front()->next_nodes.front()->data) == 0)
    {
      return;
    }
    //create the new node
    node *new_node = new node(target);
    new_node->next_nodes = std::vector<node*>();
    int node_width = random_width(max_width);
    //put previous nodes next nodes in the new node, and have them point to the new node
    for(int i = 0; i < node_width; i++)
    {
      new_node->next_nodes.push_back(prev_nodes.at(i)->next_nodes.at(i));
      prev_nodes.at(i)->next_nodes.at(i) = new_node;
    }
    this->size++;
          
  }
  /**
   * generates a random width for a node
   * @width_max is the biggest width the 
   */ 
  int string_set::random_width(int width_max)
  {
      int count = 1;
        srand(time(NULL));
        while(count < width_max + 1)
        {
          int num = rand() % 10;
          if(num > 4)
          {
            count++;
          }
          else
          {
            break;
          }
          
        }
        return count;
  }
/**
 *  remove: removes @target string value if it is in the string_set.
 */
  void string_set::remove(const std::string & target)
  {
    //point at the head node and creat a vector or null for them. 
    node *current = head;
    std::vector<node*> prev_nodes = std::vector<node*>(max_width, NULL);
    for(int i = max_width-1; i >= 0; i--)
    {
      while((current->next_nodes.at(i) != NULL) && (target.compare(current->next_nodes.at(i)->data) > 0))
      {
        current = current->next_nodes.at(i);
       }
       prev_nodes.at(i) = current;
    } 
    //check if the node exists in the string_set
    if(prev_nodes.front() == NULL)
    {
      return;
    }
   /*point to the node and remove it by pointing its previous pointers
    * to its next pointers, setting those to NULL and deleting it
    */

    node *node_to_remove = prev_nodes.front()->next_nodes.front();
    for(int i = 0; i < node_to_remove->next_nodes.size(); i++)
    {
      prev_nodes.at(i)->next_nodes.at(i) = node_to_remove->next_nodes.at(i);
      node_to_remove->next_nodes.at(i) = NULL;
    }
    delete node_to_remove;
    this->size--;
  }
/**
 *  contains: checks if @target is in the string_set;
 */
  bool string_set::contains(const std::string & target) const
  {
      node *current = head;
      for(int i = max_width-1; i >= 0; i--)
      {
          while((current->next_nodes.at(i) != NULL) && (target.compare(current->next_nodes.at(i)->data) >= 0))
          {
            current = current->next_nodes.at(i);
          } 
          if(target.compare(current->data) == 0)
          {
            return true;
          }
      }
      return false;
  }
/**
 * get_size: returns the size of the string_set;
 */ 
  int string_set::get_size() const
  {
	  return this->size;
  }

/**
 * string_set equals operator, translates the inputted string_set to the (this) string set.
 */
  string_set & string_set::operator=(const string_set & other)
  {
    if(this != &other)
    {
      this->clean();

      this->max_width =  other.max_width;
      this->head = new node("");
      head->next_nodes = std::vector<node*>(max_width,NULL);
      node *current = other.head;
      while(current->next_nodes.front() != NULL)
      {
        current = current->next_nodes.front();
        add(current->data);
      }
    }
      return *this;
  }
/**
 * returns a vector of string with the elements of the string_set
 */ 
  std::vector<std::string> string_set::get_elements()
  {
    std::vector<std::string> element_vector = std::vector<std::string>();
    node *current = this->head;
    int i = 0;
      while(current->next_nodes.front() != NULL)
      {
        current = current->next_nodes.front();
        element_vector.push_back(current->data);
        i++;
      }   
      return element_vector;
  }
}
