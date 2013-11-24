// Remove and return the top stack item. Does not check if stack
// is empty.

// Returns 1 if the stack is empty, otherwise returns 0.
template <typename T> INLINE bool
Stack::LStack<T>::is_empty (void) const
{
    return (head_ == 0);
}

template <typename T> INLINE void
Stack::LStack<T>::top (T &item) const throw (Stack::underflow)
{
    if (this->is_empty ())
        throw Stack::underflow ();
    item = head_->item_;
}

 
