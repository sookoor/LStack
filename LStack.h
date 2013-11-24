/* -*- C++ -*- */

#ifndef LSTACK_H
#define LSTACK_H

#include "Stack_Exceptions.h"

namespace Stack {

// Forward declaration (use the "Cheshire Cat" approach to information
// hiding).
template <typename T>
class Stack_Node;

/**
 * @class LStack
 *
 * @brief Implement a generic LIFO abstract data type using a linked list.
 */

template <typename T>
class LStack
{
public:
  typedef T TYPE;

  // = Initialization, assignment, and termination methods.

  // Initialize a new stack so that it is empty.
  LStack (size_t size_hint = 0);

  // The copy constructor (performs initialization).
  LStack (const LStack<T> &s);

  // Assignment operator (performs assignment).
  void operator= (const LStack<T> &s);

  // Perform actions needed when stack goes out of scope.
  ~LStack (void);

  // = Classic Stack operations.

  // Place a new item on top of the stack.  Throws the
  // <Stack::overflow> exception if the stack is full.
  void push (const T &new_item) throw (Stack::overflow);

  // Remove and return the top stack item.  Throws the
  // <Stack::underflow> exception if the stack is empty.
  void pop (T &item) throw (Stack::underflow);

  // Return top stack item without removing it.  Throws the
  // <Stack::underflow> exception if the stack is empty.
  void top (T &item) const throw (Stack::underflow);

  // = Check boundary conditions for Stack operations.

  // Returns true if the stack is empty, otherwise returns 0.
  bool is_empty (void) const;

  // Checks for stack equality.
  bool operator == (const LStack<T> &s) const;

  // Checks for stack inequality.
  bool operator != (const LStack<T> &s) const;

  // Returns all dynamic memory on the LStack<T> free list to the global free store.
  static void delete_free_list (void);

private:

  // Swap the head of the linked list. Useful in implementing
  // exception-safe assignment operator.
  void swap (LStack<T>& s);

  // Delete all the nodes in the stack.
  void delete_all_nodes (void);

  // Copy all nodes from <s> to <this>.  Assumes that <this> has no
  // nodes in it.
  void copy_all_nodes (const LStack<T> &s);

  // Head of the linked list of Nodes.
  Stack_Node<T> *head_;
};

}

#if defined (__INLINE__)
#define INLINE inline
#include "LStack.inl"
#endif /* __INLINE__ */

#include "LStack.cpp"

#endif /* LSTACK_H */
