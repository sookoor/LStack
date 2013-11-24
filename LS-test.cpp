// Uses a stack to reverse a name. 
#include <iostream>
#include <string>
#include <assert.h>
#include "LStack.h"

typedef Stack::LStack<char> STACK;

int
main (void)
{
  try
    {
      std::string name;

      STACK s1;

      std::cout << "please enter your name..: ";
      std::getline (std::cin, name);
	
      std::cout << "read in: " << name.length () << std::endl;

      std::cout << "your name is..: " << name << std::endl;
  
      for (int i = 0; i < name.length (); i++)
        {
          s1.push (name[i]);

          char t;
          s1.top (t);
          // Check to make sure the top () method works...
          assert (name[i] == t);
        }
 
      // Test the copy constructor.
       STACK s2 (s1);
       assert (s1 == s2);

       std::cout << std::endl;
    
      // Test the assignment operator
      s1 = s2;
      assert (s1 == s2);
    
      std::cout << "your name backwards is..: ";

      while (!s1.is_empty ())
        {
          STACK::TYPE t;
          STACK::TYPE p;
          s1.top (t);
          s1.pop (p);
          // Check to make sure the top () method works...
          assert (t == p);
          std::cout << p;
        }
     
      // Purge all the elements on the free list.
      STACK::delete_free_list ();

      std::cout << std::endl;
      assert (s1.is_empty ());
      assert (!s2.is_empty ());
      assert (s1 != s2);

      // Testing resize () function
      STACK s3 (1);
      STACK::TYPE item;
      while (!s2.is_empty ())
        {
          s2.pop (item);
          s3.push (item);
        }

      // S3 will be reverse of s2
      assert (s2 != s3);

      std::cout << "your name spelled correctly is..: ";

      while (!s3.is_empty ())
        {
          s3.pop (item);
          std::cout << item;
        }

      std::cout << std::endl;

      try
        {
          // Generate an underflow exception. 
          s3.top (item);
          std::cerr << "ERROR: stack underflow not caught" << std::endl;
        }
      catch (Stack::underflow &)
        {
          std::cout.flush ();
          std::cerr << "stack underflow correctly caught" << std::endl;
        }

      try
        {
          // Generate an underflow exception. 
          s3.pop (item);
          std::cerr << "ERROR: stack underflow not caught" << std::endl;
        }
      catch (Stack::underflow &)
        {
          std::cout.flush ();
          std::cerr << "stack underflow correctly caught" << std::endl;
        }
     
    }
  catch (Stack::overflow &)
    {
      std::cout.flush ();
      std::cerr << "stack overflow" << std::endl;
    }
  catch (Stack::underflow &)
    {
      std::cout.flush ();
      std::cerr << "stack underflow" << std::endl;
    }
 
  return 0;
}
