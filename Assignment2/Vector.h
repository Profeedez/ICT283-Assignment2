/**
 * @file Vector.h
 * @brief Template class implementing a dynamic array container.
 *
 * This file defines and implements a simple generic Vector class
 * that mimics a subset of functionality similar to std::vector.
 *
 * Features:
 * - Dynamic resizing (capacity grows automatically)
 * - Deep copy support (copy constructor and assignment operator)
 * - Insert and append operations
 * - Safe element access with bounds checking
 *
 * Design:
 * - Uses raw dynamic memory (no STL containers allowed)
 * - Follows Rule of Three (constructor, copy constructor, destructor, assignment)
 * - High cohesion: manages only dynamic array behaviour
 * - Low coupling: independent of application-specific logic
 *
 * Resize Strategy:
 * - Capacity doubles when needed
 * - Triggered when size exceeds half of capacity
 *
 * @author
 * Heng Kiao Woon
 *
 * @version 02
 * @date 03/04/2026
 *
 * Version History:
 * 01 01/03/2026 Heng Kiao Woon - Initial Vector implementation.
 * 02 03/04/2026 Heng Kiao Woon - Updated file header.
 */

#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

/**
 * @class VectorIndexError
 * @brief Exception-like class for handling out-of-bounds access.
 *
 * This class provides a lightweight mechanism to signal invalid
 * index access in the Vector class without using STL exceptions.
 */
class VectorIndexError
{
public:
    /**
     * @brief Returns a short error message.
     * @return C-string error message.
     */
    const char* what() const
    {
        return "Vector index out of range!";
    }
};

/**
 * @class Vector
 * @brief A minimal dynamically-resizing array container.
 *
 * @tparam T Element type stored by the container.
 *
 * Behaviour based on your provided specification:
 * - Default constructor allocates capacity 10 and size 0.
 * - Vector(int n): if n <= 0, treat as 10; allocate capacity n*2 and set size to n
 *   (elements default-constructed).
 * - Insert shifts elements right.
 * - Add appends using Insert(Size(), item).
 * - operator[] performs bounds checking.
 *
 * Resize policy (based on your notes):
 * - If size is more than half of capacity, resize (grow).
 */
template <class T>
class Vector
{
public:
//------------------------------------------------------------------------------------------------------//
    /** @name Constructors / destructor
     *  @{
     */

    /**
     * @brief Constructs an empty vector with default capacity 10.
     */
    Vector();

    /**
    * @brief Constructs a vector with capacity based on @p n.
    *
    * If @p n <= 0, it is treated as 10.
    * Initial size is 0.
    *
    * @param n Initial capacity factor.
    */
    Vector(int n);

    /**
     * @brief Copy-constructs a vector (deep copy).
     * @param other Vector to copy from.
     */
    Vector(const Vector<T>& other);

    /**
     * @brief Destroys the vector and releases owned memory.
     */
    ~Vector();

    /**
     * @brief Assigns from another vector (deep copy).
     * @param other Vector to copy from.
     * @return Reference to *this (for chaining).
     */
    Vector<T>& operator=(const Vector<T>& other);

    /** @} */
//------------------------------------------------------------------------------------------------------//
    /** @name CRUD operations
     *  @{
     */

    /**
     * @brief Inserts @p item at @p index and shifts elements to the right.
     *
     * Valid index range is 0..Size().
     *
     * @param index Zero-based insertion index.
     * @param item Item to insert.
     * @return true if inserted successfully; false if index is invalid or allocation fails.
     */
    bool Insert(int index, const T& item);

    /**
     * @brief Appends @p item to the end of the vector.
     * @param item Item to append.
     * @return true if added successfully; false otherwise.
     */
    bool Add(const T& item);

    /**
     * @brief Read-only access to an element by index.
     * @param index Zero-based index.
     * @return Const reference to the element at @p index.
     * @throw VectorIndexError If index is out of range.
     */
    const T& operator[](int index) const;

    /**
     * @brief Mutable access to an element by index.
     * @param index Zero-based index.
     * @return Reference to the element at @p index.
     * @throw VectorIndexError If index is out of range.
     */
    T& operator[](int index);

    /**
     * @brief Returns the number of elements currently stored.
     * @return Current size.
     */
    int Size() const;

    /** @} */
//------------------------------------------------------------------------------------------------------//
private:
    int m_size;      /// Number of elements in use.
    int m_capacity;  /// Allocated capacity of @ref m_vector.
    T*  m_vector;    /// Owned dynamic array storage.

    /**
     * @brief Grows capacity (typically doubles) while preserving existing elements.
     * @return true if resize succeeded; false if allocation fails.
     */
    bool Resize();
};

///// -------------------------------Start of implementation--------------------------------------- /////

template <class T>
Vector<T>::Vector()
    : m_size(0), m_capacity(0), m_vector(nullptr)
{
    m_vector = new T[10];
    if (m_vector != nullptr)
    {
        m_capacity = 10;
    }
    else
    {
        m_capacity = 0;
    }
}

template <class T>
Vector<T>::Vector(int n)
    : m_size(0), m_capacity(0), m_vector(nullptr)
{
    if (n <= 0)
    {
        n = 10;
    }

    m_capacity = n * 2;
    m_vector = new T[m_capacity];

    if (m_vector == nullptr)
    {
        m_capacity = 0;
        m_size = 0;
    }
}

template <class T>
Vector<T>::Vector(const Vector<T>& other)
    : m_size(other.m_size), m_capacity(other.m_capacity), m_vector(nullptr)
{
    if (m_capacity < 1)
    {
        m_capacity = 1;
    }

    m_vector = new T[m_capacity];
    if (m_vector != nullptr)
    {
        for (int i = 0; i < m_size; ++i)
        {
            m_vector[i] = other.m_vector[i];
        }
    }
    else
    {
        m_capacity = 0;
        m_size = 0;
    }
}

template <class T>
Vector<T>::~Vector()
{
    if (m_vector != nullptr)
    {
        delete[] m_vector;
        m_vector = nullptr;
    }
    m_size = 0;
    m_capacity = 0;
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
    if (this == &other)
    {
        return *this;
    }

    // Allocate first (safer if allocation fails).
    T* newBlock = new T[other.m_capacity];
    if (newBlock == nullptr)
    {
        // If allocation fails, keep current object unchanged.
        return *this;
    }

    for (int i = 0; i < other.m_size; ++i)
    {
        newBlock[i] = other.m_vector[i];
    }

    delete[] m_vector;
    m_vector = newBlock;
    m_capacity = other.m_capacity;
    m_size = other.m_size;

    return *this;
}

template <class T>
bool Vector<T>::Resize()
{
    int newCapacity = (m_capacity < 1) ? 1 : (m_capacity * 2);

    T* newBlock = new T[newCapacity];
    if (newBlock == nullptr)
    {
        return false;
    }

    for (int i = 0; i < m_size; ++i)
    {
        newBlock[i] = m_vector[i];
    }

    delete[] m_vector;
    m_vector = newBlock;
    m_capacity = newCapacity;
    return true;
}

template <class T>
bool Vector<T>::Insert(int index, const T& item)
{
    // Validate insertion index: allowed 0..m_size
    if (index < 0 || index > m_size)
    {
        return false;
    }

    // Resize rule from your notes: if size > capacity/2 then grow.
    // Also ensure we never exceed capacity on insert.
    if (m_capacity == 0 || (m_size + 1) > m_capacity || (m_size + 1) > (m_capacity / 2))
    {
        if (!Resize())
        {
            return false;
        }
    }

    // Shift right from the end down to index
    for (int i = m_size; i > index; --i)
    {
        m_vector[i] = m_vector[i - 1];
    }

    m_vector[index] = item;
    ++m_size;
    return true;
}

template <class T>
bool Vector<T>::Add(const T& item)
{
    return Insert(Size(), item);
}

template <class T>
const T& Vector<T>::operator[](int index) const
{
    if (index < 0 || index >= m_size)
    {
        throw VectorIndexError();
    }
    return m_vector[index];
}

template <class T>
T& Vector<T>::operator[](int index)
{
    if (index < 0 || index >= m_size)
    {
        throw VectorIndexError();
    }
    return m_vector[index];
}

template <class T>
int Vector<T>::Size() const
{
    return m_size;
}

#endif // VECTOR_H_INCLUDED
