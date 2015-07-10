#ifndef __vec_h
#define __vec_h

// Vec class from Accelerated C++
#include <memory>

// This class is a stripped-down version of std::vector
template <class T> class Vec {
    public:
        typedef T* iterator;
        typedef const T* const_iterator;
        typedef std::size_t size_type;
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T& reference;
        typedef const T& const_reference;

        Vec() { create(); }
        explicit Vec(size_type n, const T& val = T()) { create(n, val); }

        // copy constructor
        Vec(const Vec& v) { create(v.begin(), v.end()); }
        // assignment operator
        Vec& operator=(const Vec&);
        // destructor
        ~Vec() { uncreate(); }

        // index operator
        T& operator[](size_type i) { return data[i]; }
        const T& operator[](size_type i) const { return data[i]; }

        iterator begin() { return data; }
        const_iterator begin() const { return data; }

        iterator end() { return avail; }
        const_iterator end() const { return avail; }

        size_type size() const { return avail - data; }

        void push_back(const T& val) {
            if (avail == limit) //get space if needed
                grow();
            unchecked_append(val); // append the new element
        }

    private:
        iterator data; // first element
        iterator avail; // first unused element
        iterator limit; // one past last element

        // for memory allocation
        std::allocator<T> alloc;

        // allocate and initialize the underlying array
        void create();
        void create(size_type, const T&);
        void create(const_iterator, const_iterator);

        // destroy elements in underlying array and free memeory
        void uncreate();

        // used by push_back
        void grow();
        void unchecked_append(const T&);
};

// source for vec class

// assignment operator
template <class T> Vec<T>& Vec<T>::operator=(const Vec& rhs)
{
    // check for self-assignment
    if (&rhs != this) {

        // free the array in the left-hand side
        uncreate();

        // copy elements from the right to the left side
        create(rhs.begin(), rhs.end());
    }
    return *this;
}

// for allocating and initializing underlying array
template <class T> void Vec<T>::create()
{
    data = avail = limit = 0;
}

template <class T> void Vec<T>::create(size_type n, const T& val)
{
    data = alloc.allocate(n);
    limit = avail = data + n;
    std::uninitialized_fill(data, limit, val);
}

template <class T> void Vec<T>::create(const_iterator i, const_iterator j)
{
    data = alloc.allocate(j - i);
    limit = avail = std::uninitialized_copy(i, j, data);
}

template <class T> void Vec<T>::uncreate()
{
    if (data) {
        // destory (in reverse order) the elements that were constructed)
        iterator it = avail;
        while (it != data)
            alloc.destroy(--it);

        // return space that was allocated
        alloc.deallocate(data, limit - data);
    }
    // indicate Vec is empty
    data = limit = avail = 0;
}

// functions used by push_back
template <class T> void Vec<T>::grow()
{
    // chose to double in size each time we need to grow
    size_type new_size = std::max(2 * (limit - data), difference_type(1));

    // allocate new space and copy over old elements
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);

    // return the old space
    uncreate();

    // update pointers
    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

// assumes avail points at allocated, uninitialized space
template <class T> void Vec<T>::unchecked_append(const T& val)
{
    alloc.construct(avail++, val);
}
#endif
