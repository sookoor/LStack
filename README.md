Compilation instructions using g++ under emacs:

1. Open a command line prompt that accepts the g++ command.
2. Change the directory to the folder containing the source code and Makefile.
3. Type 'make'.
4. When the compilation is complete and focus is returned to the user
type 'gdb' to start the debugger.
5. At the prompt 'Run gdb (like this): type 'gdb LS-test'.
6. At the debugger prompt type 'run'.
7. Follow the screen prompts.

Changes made:

1. Comment: "Yikes, you aren't checking for underflow..."

   Changes: Checked for underflow using: "if (this->is_empty ())
                                                  throw Stack::underflow ();"

2. Comment: "Please do NOT use magic numbers like "10", but instead define an enum like DEFAULT_ALLOC_NODES inside 
             of class Stack_Node and use it here."

   Changes: Defined DEFAULT_ALLOC_NODES inside of class Stack_Nodes and used it.

3. Comment: "Please make sure to check for ptr == 0 before you indirect through it..."
  
   Changes:  Checked for ptr == 0 using "if (prt != 0)

4. Comment: "Please note that size is a size_t, so it will ALWAYS be > 0, so you can omit this."

   Changes: Ommitted "if (size > 0)".

5. Comment: "This is excessive - just do this:
             LStack<T> t (s);
             this->swap (t);"

   Changes: Changed "LStack<T> t;
                     t.copy_all_nodes(s);
                     this->swap (t);"
            to      "LStack<T> t (s);
                     this->swap (t);"

6. Comment: "Please don't access the free list here, simply use delete t; and the operator delete() in class 
             Stack_node will handle things magically.."

   Changes: Changed: "t->next_ = Stack_Node<T>::free_list_;
                      Stack_Node<T>::free_list_ = t;"
            to       "delete t;"

7. Comment: "This code doesn't handle overflow exceptions properly.."

   Changes: Added try and catch blocks.

8. Comment: "The loop expression is incorrect, e.g., what happens if t1 == 0 or t2 == 0?  You will crash right away 
            since you're trying to access a NULL pointer.. The exit condition isn't correct either.."

   Changes: Rewrote operator ==

