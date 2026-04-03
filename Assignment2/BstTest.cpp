// BstTest.cpp
//
// Console test program for the template Binary Search Tree class.
// Tests insertion, duplicate handling, searching, deletion,
// traversals, copy construction, assignment, and function pointer traversal.
//
// Version
// 01 31/03/2026 Heng Kiao Woon - Initial BST test implementation.
// 02 03/04/2026 Heng Kiao Woon - Expanded tests.
//---------------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Includes
#include "Bst.h"
#include <iostream>

//----------------------------------------------------------------------------
// Helper visit functions
void PrintValue(int& value)
{
    std::cout << value << " ";
}

void PrintConstValue(const int& value)
{
    std::cout << value << " ";
}

//----------------------------------------------------------------------------
// Main test program
int main()
{
    std::cout << "===== BstTest =====" << std::endl << std::endl;

    Bst<int> tree;

    //------------------------------------------------------------------------
    std::cout << "-- Test 1 (Empty tree) --" << std::endl;
    std::cout << "Tree empty? "
              << (tree.isEmpty() ? "Yes" : "No")
              << std::endl << std::endl;

    //------------------------------------------------------------------------
    std::cout << "-- Test 2 (Insert root) --" << std::endl;
    std::cout << "Insert 50: "
              << (tree.insert(50) ? "Success" : "Failed")
              << std::endl << std::endl;

    //------------------------------------------------------------------------
    std::cout << "-- Test 3 (Insert more values) --" << std::endl;
    std::cout << "Insert 30: " << (tree.insert(30) ? "Success" : "Failed") << std::endl;
    std::cout << "Insert 70: " << (tree.insert(70) ? "Success" : "Failed") << std::endl;
    std::cout << "Insert 20: " << (tree.insert(20) ? "Success" : "Failed") << std::endl;
    std::cout << "Insert 40: " << (tree.insert(40) ? "Success" : "Failed") << std::endl;
    std::cout << "Insert 60: " << (tree.insert(60) ? "Success" : "Failed") << std::endl;
    std::cout << "Insert 80: " << (tree.insert(80) ? "Success" : "Failed") << std::endl;
    std::cout << std::endl;

    //------------------------------------------------------------------------
    std::cout << "-- Test 4 (Duplicate insert) --" << std::endl;
    std::cout << "Insert duplicate 30: "
              << (tree.insert(30) ? "Success" : "Rejected")
              << std::endl << std::endl;

    //------------------------------------------------------------------------
    std::cout << "-- Test 5 (Search existing and missing values) --" << std::endl;
    std::cout << "Search 40: " << (tree.search(40) ? "Found" : "Not found") << std::endl;
    std::cout << "Search 100: " << (tree.search(100) ? "Found" : "Not found") << std::endl;
    std::cout << std::endl;

    //------------------------------------------------------------------------
    std::cout << "-- Test 6 (Inorder traversal) --" << std::endl;
    std::cout << "Expected sorted order: 20 30 40 50 60 70 80" << std::endl;
    std::cout << "Actual: ";
    tree.inorderTraversal();
    std::cout << std::endl << std::endl;

    //------------------------------------------------------------------------
    std::cout << "-- Test 7 (Preorder traversal) --" << std::endl;
    std::cout << "Actual: ";
    tree.preorderTraversal();
    std::cout << std::endl << std::endl;

    //------------------------------------------------------------------------
    std::cout << "-- Test 8 (Postorder traversal) --" << std::endl;
    std::cout << "Actual: ";
    tree.postorderTraversal();
    std::cout << std::endl << std::endl;

    //------------------------------------------------------------------------
    std::cout << "-- Test 9 (Function pointer inorder traversal) --" << std::endl;
    std::cout << "Actual: ";
    tree.inorderTraversal(PrintValue);
    std::cout << std::endl << std::endl;

    //------------------------------------------------------------------------
    std::cout << "-- Test 10 (Const function pointer inorder traversal) --" << std::endl;
    std::cout << "Actual: ";
    const Bst<int>& constTree = tree;
    constTree.inorderTraversal(PrintConstValue);
    std::cout << std::endl << std::endl;

    //------------------------------------------------------------------------
    std::cout << "-- Test 11 (Delete leaf node: 20) --" << std::endl;
    tree.deleteNode(20);
    std::cout << "After deleting 20: ";
    tree.inorderTraversal();
    std::cout << std::endl << std::endl;

    //------------------------------------------------------------------------
    std::cout << "-- Test 12 (Delete node with one child: 30) --" << std::endl;
    tree.deleteNode(30);
    std::cout << "After deleting 30: ";
    tree.inorderTraversal();
    std::cout << std::endl << std::endl;

    //------------------------------------------------------------------------
    std::cout << "-- Test 13 (Delete node with two children: 70) --" << std::endl;
    tree.deleteNode(70);
    std::cout << "After deleting 70: ";
    tree.inorderTraversal();
    std::cout << std::endl << std::endl;

    //------------------------------------------------------------------------
    std::cout << "-- Test 14 (Delete root node: 50) --" << std::endl;
    tree.deleteNode(50);
    std::cout << "After deleting 50: ";
    tree.inorderTraversal();
    std::cout << std::endl << std::endl;

    //------------------------------------------------------------------------
    std::cout << "-- Test 15 (Delete missing item) --" << std::endl;
    tree.deleteNode(999);
    std::cout << std::endl;

    //------------------------------------------------------------------------
    std::cout << "-- Test 16 (Copy constructor) --" << std::endl;
    Bst<int> copyTree(tree);
    std::cout << "Copied tree inorder: ";
    copyTree.inorderTraversal();
    std::cout << std::endl << std::endl;

    //------------------------------------------------------------------------
    std::cout << "-- Test 17 (Assignment operator) --" << std::endl;
    Bst<int> assignedTree;
    assignedTree.insert(1);
    assignedTree.insert(2);
    assignedTree.insert(3);

    assignedTree = tree;
    std::cout << "Assigned tree inorder: ";
    assignedTree.inorderTraversal();
    std::cout << std::endl << std::endl;

    //------------------------------------------------------------------------
    std::cout << "-- Test 18 (Destroy tree) --" << std::endl;
    assignedTree.destroyTree();
    std::cout << "Assigned tree empty after destroyTree()? "
              << (assignedTree.isEmpty() ? "Yes" : "No")
              << std::endl << std::endl;

    return 0;
}
