// Implementation of a linked list stack abstraction in C++.

#ifndef LSTACK_CPP
#define LSTACK_CPP

#include <algorithm>
#include <new>
#include <stdexcept>
#include "LStack.h"

#if !defined (__INLINE__)
#define INLINE
#include "LStack.inl"
#endif /* __INLINE__ */

namespace Stack {

    template <typename T>
    class Stack_Node
    {
        friend class Stack::LStack<T>;
    public:
        // = Initialization methods

        // Create a stack node with value i and assign it's next to point to next
        Stack_Node (const T &i,
                    Stack_Node<T> *next = 0);

        // Default constructor.
        Stack_Node (void);

        // Copy constructor.
        Stack_Node (const Stack_Node<T> &n);

        // = Class-specific freelist management methods.

        // Class specific new which amortizes the cost of dynamic memory
        // allocation by maintaining a free list.
        void *operator new (size_t bytes);

        // Class specific operator delete which adds the deleted node to the
        // free list for use in future allocation operations.
        void operator delete (void *ptr);

        // Returns all dynamic memory on the free list to the free store.
        static void free_all_nodes (void);

    private:
        // Helper to allocate a chain of n Stack_Nodes and attach them to the
        // free list.
        static void alloc_stack_nodes (size_t n = 1);

        // Head of the free list of Nodes used to speed up allocation.
        static Stack_Node<T> *free_list_;

        // Pointer to next element in the list of Stack_Nodes.
        Stack_Node<T> *next_;

        // Current value of the item in this node.
        T item_;

        // Default number of nodes to be allocated on free list by new
        enum  {DEFAULT_ALLOC_NODES = 10};
    };

    /* static */
    template <typename T> Stack_Node<T> *
    Stack_Node<T>::free_list_ = 0;

    //
    //Method name: Stack_Node.
    //Purpose: Create a stack node with value i and assign it's next to point to    //         next.
    //Parameters: <i> is of type T. 
    //            <i> is the value to be assigned to the node.
    //            <i> is passed by reference.
    //            <next> is of type Stack_Node<T> *.
    //            <next> is what the node should point to.
    //            <next> is passed by value.
    //Return value: None.
    //
    template <typename T>
    Stack_Node<T>::Stack_Node (const T &i,
                               Stack_Node<T> *next)
        : next_(next),
          item_(i)
    {  
    }

    //
    //Method name: Stack_ Node.
    //Purpose: Default constructor.
    //Parameters: void.
    //Return value: None.
    //
    template <typename T>
    Stack_Node<T>::Stack_Node (void)
        : next_(0)
    {
    }

    //
    //Method name: Stack_ Node.
    //Purpose: Copy constructor.
    //Parameters: <s> is of type Stack_Node<T>.
    //            <s> is the node to be copied.
    //            <s> is passed by reference.
    //Return value: None.
    //
    template <typename T>
    Stack_Node<T>::Stack_Node (const Stack_Node<T> &s)
        : next_(s.next_),
          item_(s.item_)
    {
    }

    //
    //Method name: operator new.
    //Purpose: Class specific new which amortizes the cost of dynamic memory
    //         allocation by maintaining a free list.
    //Parameters: <nbytes> is of type size_t.
    //            <nbytes> is passed by value.
    //Return value: void * : points to new node.
    //
    template <typename T> void *
    Stack_Node<T>::operator new (size_t nbytes)
    {
        if (free_list_ ==  0)
            {
                alloc_stack_nodes (DEFAULT_ALLOC_NODES);
            }
        void * t = free_list_;
        free_list_ = free_list_->next_;
        return t;
    }

    //
    //Method name: operator delete.
    //Purpose: Class specific operator delete which adds the deleted node to th     //         free list for use in future allocation operations.
    //Parameters: <ptr> is of type void *.
    //            <ptr> points to the node to be deleted.
    //            <ptr> is passed be value.
    //Return value: void.
    //
    template <typename T> void
    Stack_Node<T>::operator delete (void *ptr)
    {
        if (ptr != 0)
            {
                Stack_Node<T> *t = static_cast<Stack_Node<T> *> (ptr);
                t->next_ = free_list_;
                free_list_ = t;
            }
    }

    template <typename T> void
    Stack_Node<T>::alloc_stack_nodes (size_t n)
    {
        for (size_t i = 0; i < n; i++)
            {
                Stack_Node<T> *t = ::new Stack_Node<T>;
                t->next_ = free_list_;
                free_list_ = t;
            }
    }

    template <typename T> void
    Stack_Node<T>::free_all_nodes (void)
    {
        while (free_list_ != 0)
            {
                // It was allocated as a linked list of Stack_Node<T> .
                Stack_Node<T> *t = free_list_;
                free_list_ = free_list_->next_;
                ::delete (t);
            }
    }

}

template <typename T>
Stack::LStack<T>::LStack (size_t size)
    : head_(0)
{
    Stack_Node<T>:: alloc_stack_nodes (size);
}

template <typename T>
Stack::LStack<T>::LStack (const Stack::LStack<T> &s)
{
    this->copy_all_nodes (s);
}

template <typename T> void
Stack::LStack<T>::operator= (const Stack::LStack<T> &s)
{
    if (this->head_ != s.head_) // Check for self-allocation.
        {
            Stack::LStack<T> t (s);
            this->swap (t);
        }   
}

template <typename T>
Stack::LStack<T>::~LStack (void)
{
    this->delete_all_nodes ();
}

template <typename T> void
Stack::LStack<T>::delete_all_nodes (void)
{
    while (head_ != 0)
        {
            Stack_Node<T> *t = head_;
            head_ = head_->next_;
            delete t;
        }
}

template <typename T> void
Stack::LStack<T>::copy_all_nodes (const Stack::LStack<T> &s)
{
    if (s.is_empty()==0)
        {	 	
            Stack_Node<T> * this_head = new Stack_Node<T>(s.head_->item_,0);		
            Stack_Node<T> * s_temphead = s.head_;
            Stack_Node<T> * temp = this_head;

            try 
                {
                    while(s_temphead->next_ != 0)
                        {
                            s_temphead=s_temphead->next_;
                            temp->next_ = new Stack_Node<T>(s_temphead->item_,0);
                            temp = temp->next_;
                        }
                }

            catch (std::bad_alloc &)
                {
                    delete_all_nodes ();
                }
            this->head_ = this_head;
        }
}

template <typename T> void
Stack::LStack<T>::delete_free_list (void)    
{
    Stack_Node<T>::free_all_nodes ();
}

template <typename T> void
Stack::LStack<T>::push (const T &new_item) throw (Stack::overflow)
{
    try
        {
            Stack_Node<T> * t = new Stack_Node<T> (new_item, head_);
            head_ = t;
        }

    catch (std::bad_alloc &)
        {
            throw Stack::overflow ();
        }

   
}

template <typename T> void
Stack::LStack<T>::pop (T &item) throw (Stack::underflow)
{
    if (is_empty ())
        throw Stack::underflow ();
    top (item);
    Stack_Node<T> * t = head_;
    head_ = head_->next_;
    delete t;
}

// Swap the members of "this" with the members of rhs. Since all the
// operations involve basic pointer arithmetic, they cannot throw.
template <typename T> void
Stack::LStack<T>::swap (Stack::LStack<T> &rhs)
{
    std::swap(this->head_, rhs.head_);
}

template <typename T> bool
Stack::LStack<T>::operator == (const Stack::LStack<T> &s) const
{
    Stack_Node<T> *t1;
    Stack_Node<T> *t2;
    for (t1 = head_, t2 = s.head_; t1 != 0 && t2 != 0; t1 = t1->next_, t2 = t2->next_)
        {
            if (t1->item_ != t2->item_)
                return false;
        }
    return t1 == t2;
}

template <typename T> bool
Stack::LStack<T>::operator != (const Stack::LStack<T> &s) const
{
    return !(*this == s);
}

#endif /* LSTACK_CPP */
