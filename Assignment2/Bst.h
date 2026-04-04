/**
 * @file Bst.h
 * @brief Declares and implements a minimal and complete template binary search tree.
 *
 * This header provides:
 * - A generic binary tree node structure
 * - An abstract binary tree base class
 * - A binary search tree template class derived from the base class
 *
 * The binary search tree stores data according to the BST property:
 * - Smaller values are placed in the left subtree
 * - Larger values are placed in the right subtree
 *
 * This version supports:
 * - Recursive search, insert, and delete
 * - Tree traversals
 * - Traversals using function pointers
 * - Deep copying through copy constructor and assignment operator
 * - Proper memory cleanup through destructor and destroyTree()
 *
 * @author Heng Kiao Woon
 * @version 03
 * @date 31/03/2026
 */

#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include <iostream>

/**
 * @struct nodeType
 * @brief Represents a single node in a binary tree.
 *
 * Each node stores:
 * - one data item
 * - a pointer to the left child
 * - a pointer to the right child
 *
 * @tparam T The type of data stored in the node.
 */
template <class T>
struct nodeType
{
    /**
     * @brief Default constructor.
     */
    nodeType()
        : info(), lLink(nullptr), rLink(nullptr)
    {
    }

    T info;               /**< Data stored in the node. */
    nodeType<T>* lLink;   /**< Pointer to the left child node. */
    nodeType<T>* rLink;   /**< Pointer to the right child node. */
};

/**
 * @class BinaryTree
 * @brief Abstract base class for a binary tree.
 *
 * This class provides common binary tree operations such as:
 * - checking if the tree is empty
 * - tree traversals
 * - traversals with callback functions
 * - tree destruction
 * - deep copying
 *
 * The class is abstract because search(), insert(), and deleteNode()
 * are pure virtual functions.
 *
 * @tparam T The type of data stored in the tree.
 */
template <class T>
class BinaryTree
{
public:
    /**
     * @brief Overloads the assignment operator.
     * @param otherTree The tree to copy from.
     * @return A reference to this tree after assignment.
     */
    const BinaryTree<T>& operator=(const BinaryTree<T>& otherTree);

    /**
     * @brief Determines whether the tree is empty.
     * @return True if the tree has no nodes, otherwise false.
     */
    bool isEmpty() const;

    /**
     * @brief Performs an inorder traversal and prints each node value.
     */
    void inorderTraversal() const;

    /**
     * @brief Performs a preorder traversal and prints each node value.
     */
    void preorderTraversal() const;

    /**
     * @brief Performs a postorder traversal and prints each node value.
     */
    void postorderTraversal() const;

    /**
     * @brief Performs an inorder traversal and applies a callback function.
     * @param visit Pointer to a callback function that processes each node value.
     */
    void inorderTraversal(void (*visit)(T&));

    /**
     * @brief Performs a preorder traversal and applies a callback function.
     * @param visit Pointer to a callback function that processes each node value.
     */
    void preorderTraversal(void (*visit)(T&));

    /**
     * @brief Performs a postorder traversal and applies a callback function.
     * @param visit Pointer to a callback function that processes each node value.
     */
    void postorderTraversal(void (*visit)(T&));

    /**
     * @brief Performs an inorder traversal and applies a read-only callback function.
     * @param visit Pointer to a callback function that reads each node value.
     */
    void inorderTraversal(void (*visit)(const T&)) const;

    /**
     * @brief Performs a preorder traversal and applies a read-only callback function.
     * @param visit Pointer to a callback function that reads each node value.
     */
    void preorderTraversal(void (*visit)(const T&)) const;

    /**
     * @brief Performs a postorder traversal and applies a read-only callback function.
     * @param visit Pointer to a callback function that reads each node value.
     */
    void postorderTraversal(void (*visit)(const T&)) const;

    /**
     * @brief Destroys the entire tree.
     *
     * All dynamically allocated nodes are deleted and root becomes nullptr.
     */
    void destroyTree();

    /**
     * @brief Determines whether an item exists in the tree.
     * @param searchItem The item to search for.
     * @return True if found, otherwise false.
     */
    virtual bool search(const T& searchItem) const = 0;

    /**
     * @brief Inserts an item into the tree.
     * @param insertItem The item to insert.
     * @return True if the item was inserted, false if it is a duplicate.
     */
    virtual bool insert(const T& insertItem) = 0;

    /**
     * @brief Deletes an item from the tree.
     * @param deleteItem The item to delete.
     */
    virtual void deleteNode(const T& deleteItem) = 0;

    /**
     * @brief Copy constructor.
     * @param otherTree The tree to copy from.
     */
    BinaryTree(const BinaryTree<T>& otherTree);

    /**
     * @brief Default constructor.
     *
     * Creates an empty tree.
     */
    BinaryTree();

    /**
     * @brief Destructor.
     *
     * Releases all dynamically allocated memory used by the tree.
     */
    virtual ~BinaryTree();

protected:
    nodeType<T>* root; /**< Pointer to the root node of the tree. */

private:
    /**
     * @brief Makes a deep copy of a subtree.
     * @param copiedTreeRoot Reference to the copied subtree root pointer.
     * @param otherTreeRoot Pointer to the source subtree root.
     */
    void copyTree(nodeType<T>*& copiedTreeRoot, nodeType<T>* otherTreeRoot);

    /**
     * @brief Destroys a subtree.
     * @param pointer Reference to the subtree root pointer.
     *
     * After destruction, @p pointer becomes nullptr.
     */
    void destroy(nodeType<T>*& pointer);

    /**
     * @brief Performs an inorder traversal of a subtree.
     * @param pointer Pointer to the subtree root.
     */
    void inorder(nodeType<T>* pointer) const;

    /**
     * @brief Performs a preorder traversal of a subtree.
     * @param pointer Pointer to the subtree root.
     */
    void preorder(nodeType<T>* pointer) const;

    /**
     * @brief Performs a postorder traversal of a subtree.
     * @param pointer Pointer to the subtree root.
     */
    void postorder(nodeType<T>* pointer) const;

    /**
     * @brief Performs an inorder traversal and applies a callback.
     * @param pointer Pointer to the subtree root.
     * @param visit Pointer to a callback function.
     */
    void inorder(nodeType<T>* pointer, void (*visit)(T&));

    /**
     * @brief Performs a preorder traversal and applies a callback.
     * @param pointer Pointer to the subtree root.
     * @param visit Pointer to a callback function.
     */
    void preorder(nodeType<T>* pointer, void (*visit)(T&));

    /**
     * @brief Performs a postorder traversal and applies a callback.
     * @param pointer Pointer to the subtree root.
     * @param visit Pointer to a callback function.
     */
    void postorder(nodeType<T>* pointer, void (*visit)(T&));

    /**
     * @brief Performs an inorder traversal and applies a read-only callback.
     * @param pointer Pointer to the subtree root.
     * @param visit Pointer to a callback function.
     */
    void inorder(nodeType<T>* pointer, void (*visit)(const T&)) const;

    /**
     * @brief Performs a preorder traversal and applies a read-only callback.
     * @param pointer Pointer to the subtree root.
     * @param visit Pointer to a callback function.
     */
    void preorder(nodeType<T>* pointer, void (*visit)(const T&)) const;

    /**
     * @brief Performs a postorder traversal and applies a read-only callback.
     * @param pointer Pointer to the subtree root.
     * @param visit Pointer to a callback function.
     */
    void postorder(nodeType<T>* pointer, void (*visit)(const T&)) const;
};

/**
 * @class Bst
 * @brief Binary search tree template class derived from BinaryTree.
 *
 * This class provides recursive BST operations for:
 * - searching
 * - insertion
 * - deletion
 *
 * Duplicate items are not inserted.
 *
 * @tparam T The type of data stored in the tree.
 */
template <class T>
class Bst : public BinaryTree<T>
{
public:
    /**
     * @brief Determines whether an item exists in the BST.
     * @param searchItem The item to search for.
     * @return True if found, otherwise false.
     */
    bool search(const T& searchItem) const;

    /**
     * @brief Inserts an item into the BST.
     * @param insertItem The item to insert.
     * @return True if inserted successfully, false if duplicate.
     */
    bool insert(const T& insertItem);

    /**
     * @brief Deletes an item from the BST.
     * @param deleteItem The item to delete.
     */
    void deleteNode(const T& deleteItem);

private:
    /**
     * @brief Recursively inserts an item into the BST.
     * @param current Reference to the root pointer of the current subtree.
     * @param insertItem The item to insert.
     * @return True if inserted, false if duplicate.
     */
    bool insertRec(nodeType<T>*& current, const T& insertItem);

    /**
     * @brief Recursively searches for an item in the BST.
     * @param current Pointer to the root of the current subtree.
     * @param searchItem The item to search for.
     * @return True if found, otherwise false.
     */
    bool searchRec(nodeType<T>* current, const T& searchItem) const;

    /**
     * @brief Recursively deletes an item from the BST.
     * @param current Reference to the root pointer of the current subtree.
     * @param deleteItem The item to delete.
     */
    void deleteRec(nodeType<T>*& current, const T& deleteItem);

    /**
     * @brief Deletes the node pointed to by current.
     * @param current Reference to the node pointer to delete from.
     *
     * The BST order property is preserved after deletion.
     */
    void deleteFromTree(nodeType<T>*& current);
};

// ========================= BinaryTree Implementation =========================

template <class T>
bool BinaryTree<T>::isEmpty() const
{
    return this->root == nullptr;
}

template <class T>
BinaryTree<T>::BinaryTree()
    : root(nullptr)
{
}

template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& otherTree)
    : root(nullptr)
{
    if (otherTree.root != nullptr)
    {
        copyTree(root, otherTree.root);
    }
}

template <class T>
BinaryTree<T>::~BinaryTree()
{
    destroy(root);
}

template <class T>
const BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& otherTree)
{
    if (this != &otherTree)
    {
        destroy(root);

        if (otherTree.root != nullptr)
        {
            copyTree(root, otherTree.root);
        }
        else
        {
            root = nullptr;
        }
    }

    return *this;
}

template <class T>
void BinaryTree<T>::destroyTree()
{
    destroy(root);
}

template <class T>
void BinaryTree<T>::inorderTraversal() const
{
    inorder(root);
}

template <class T>
void BinaryTree<T>::preorderTraversal() const
{
    preorder(root);
}

template <class T>
void BinaryTree<T>::postorderTraversal() const
{
    postorder(root);
}

template <class T>
void BinaryTree<T>::inorderTraversal(void (*visit)(T&))
{
    inorder(root, visit);
}

template <class T>
void BinaryTree<T>::preorderTraversal(void (*visit)(T&))
{
    preorder(root, visit);
}

template <class T>
void BinaryTree<T>::postorderTraversal(void (*visit)(T&))
{
    postorder(root, visit);
}

template <class T>
void BinaryTree<T>::inorderTraversal(void (*visit)(const T&)) const
{
    inorder(root, visit);
}

template <class T>
void BinaryTree<T>::preorderTraversal(void (*visit)(const T&)) const
{
    preorder(root, visit);
}

template <class T>
void BinaryTree<T>::postorderTraversal(void (*visit)(const T&)) const
{
    postorder(root, visit);
}

template <class T>
void BinaryTree<T>::inorder(nodeType<T>* pointer) const
{
    if (pointer != nullptr)
    {
        inorder(pointer->lLink);
        std::cout << pointer->info << " ";
        inorder(pointer->rLink);
    }
}

template <class T>
void BinaryTree<T>::preorder(nodeType<T>* pointer) const
{
    if (pointer != nullptr)
    {
        std::cout << pointer->info << " ";
        preorder(pointer->lLink);
        preorder(pointer->rLink);
    }
}

template <class T>
void BinaryTree<T>::postorder(nodeType<T>* pointer) const
{
    if (pointer != nullptr)
    {
        postorder(pointer->lLink);
        postorder(pointer->rLink);
        std::cout << pointer->info << " ";
    }
}

template <class T>
void BinaryTree<T>::inorder(nodeType<T>* pointer, void (*visit)(T&))
{
    if (pointer != nullptr)
    {
        inorder(pointer->lLink, visit);
        visit(pointer->info);
        inorder(pointer->rLink, visit);
    }
}

template <class T>
void BinaryTree<T>::preorder(nodeType<T>* pointer, void (*visit)(T&))
{
    if (pointer != nullptr)
    {
        visit(pointer->info);
        preorder(pointer->lLink, visit);
        preorder(pointer->rLink, visit);
    }
}

template <class T>
void BinaryTree<T>::postorder(nodeType<T>* pointer, void (*visit)(T&))
{
    if (pointer != nullptr)
    {
        postorder(pointer->lLink, visit);
        postorder(pointer->rLink, visit);
        visit(pointer->info);
    }
}

template <class T>
void BinaryTree<T>::inorder(nodeType<T>* pointer, void (*visit)(const T&)) const
{
    if (pointer != nullptr)
    {
        inorder(pointer->lLink, visit);
        visit(pointer->info);
        inorder(pointer->rLink, visit);
    }
}

template <class T>
void BinaryTree<T>::preorder(nodeType<T>* pointer, void (*visit)(const T&)) const
{
    if (pointer != nullptr)
    {
        visit(pointer->info);
        preorder(pointer->lLink, visit);
        preorder(pointer->rLink, visit);
    }
}

template <class T>
void BinaryTree<T>::postorder(nodeType<T>* pointer, void (*visit)(const T&)) const
{
    if (pointer != nullptr)
    {
        postorder(pointer->lLink, visit);
        postorder(pointer->rLink, visit);
        visit(pointer->info);
    }
}

template <class T>
void BinaryTree<T>::copyTree(nodeType<T>*& copiedTreeRoot, nodeType<T>* otherTreeRoot)
{
    if (otherTreeRoot == nullptr)
    {
        copiedTreeRoot = nullptr;
    }
    else
    {
        copiedTreeRoot = new nodeType<T>;
        copiedTreeRoot->info = otherTreeRoot->info;
        copiedTreeRoot->lLink = nullptr;
        copiedTreeRoot->rLink = nullptr;

        copyTree(copiedTreeRoot->lLink, otherTreeRoot->lLink);
        copyTree(copiedTreeRoot->rLink, otherTreeRoot->rLink);
    }
}

template <class T>
void BinaryTree<T>::destroy(nodeType<T>*& pointer)
{
    if (pointer != nullptr)
    {
        destroy(pointer->lLink);
        destroy(pointer->rLink);
        delete pointer;
        pointer = nullptr;
    }
}

// ========================= Bst Implementation =========================

template <class T>
bool Bst<T>::search(const T& searchItem) const
{
    return searchRec(this->root, searchItem);
}

template <class T>
bool Bst<T>::searchRec(nodeType<T>* current, const T& searchItem) const
{
    if (current == nullptr)
    {
        return false;
    }

    if (current->info == searchItem)
    {
        return true;
    }

    if (searchItem < current->info)
    {
        return searchRec(current->lLink, searchItem);
    }

    return searchRec(current->rLink, searchItem);
}

template <class T>
bool Bst<T>::insert(const T& insertItem)
{
    return insertRec(this->root, insertItem);
}

template <class T>
bool Bst<T>::insertRec(nodeType<T>*& current, const T& insertItem)
{
    if (current == nullptr)
    {
        current = new nodeType<T>;
        current->info = insertItem;
        current->lLink = nullptr;
        current->rLink = nullptr;
        return true;
    }
    else if (insertItem < current->info)
    {
        return insertRec(current->lLink, insertItem);
    }
    else if (insertItem > current->info)
    {
        return insertRec(current->rLink, insertItem);
    }
    else
    {
        return false;
    }
}

template <class T>
void Bst<T>::deleteNode(const T& deleteItem)
{
    deleteRec(this->root, deleteItem);
}

template <class T>
void Bst<T>::deleteRec(nodeType<T>*& current, const T& deleteItem)
{
    if (current == nullptr)
    {
        std::cout << "The item to be deleted is not in the tree." << std::endl;
    }
    else if (deleteItem < current->info)
    {
        deleteRec(current->lLink, deleteItem);
    }
    else if (deleteItem > current->info)
    {
        deleteRec(current->rLink, deleteItem);
    }
    else
    {
        deleteFromTree(current);
    }
}

template <class T>
void Bst<T>::deleteFromTree(nodeType<T>*& current)
{
    nodeType<T>* currentNode = current;

    if (current == nullptr)
    {
        std::cout << "Error: The node to be deleted is nullptr." << std::endl;
    }
    else if (current->lLink == nullptr && current->rLink == nullptr)
    {
        delete current;
        current = nullptr;
    }
    else if (current->lLink == nullptr)
    {
        current = current->rLink;
        delete currentNode;
    }
    else if (current->rLink == nullptr)
    {
        current = current->lLink;
        delete currentNode;
    }
    else
    {
        nodeType<T>* trailCurrent = current->lLink;
        nodeType<T>* trailParent = nullptr;

        while (trailCurrent->rLink != nullptr)
        {
            trailParent = trailCurrent;
            trailCurrent = trailCurrent->rLink;
        }

        current->info = trailCurrent->info;

        if (trailParent == nullptr)
        {
            current->lLink = trailCurrent->lLink;
        }
        else
        {
            trailParent->rLink = trailCurrent->lLink;
        }

        delete trailCurrent;
    }
}

#endif // BST_H_INCLUDED
