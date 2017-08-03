/*
 * BST.cpp
 * 
 * Description: Data collection Binary Search Tree ADT class.
 *              Link-based implementation.
 *
 * Class invariant: It is always a BST.
 * 
 * Author: Inspired from our textbook
 * Date of last modification: July 2017
 */

#include "BST.h"
#include "ElementAlreadyExistsInBSTException.h"
#include "ElementDoesNotExistInBSTException.h"

// Default Constructor
template <class ElementType>
BST<ElementType>::BST(){

    root = NULL;
    elementCount = 0;

}

// Parametrized Constructor
template <class ElementType>
BST<ElementType>::BST(ElementType& element){

    BSTNode<ElementType>* newNode = new BSTNode<ElementType>(element);
    root = newNode;
    elementCount++;

}

// Copy Constructor
template <class ElementType>
BST<ElementType>::BST(const BST<ElementType>& aBST){

    root = NULL;
    elementCount = 0;
    if (aBST.root != NULL){
        copyR(aBST.root);
    } else {
        cout << "Root NULL, copy ends here" << endl;
    }
}

//Description: Helper for copy (basically preOrderTraverse)
template <class ElementType>
void BST<ElementType>::copyR(BSTNode<ElementType>* current){

   insert(current->element);
    if (current->hasLeft()){
        copyR(current->left);
    }
    if (current->hasRight()){
        copyR(current->right);
    }
}

// Destructor
template <class ElementType>
BST<ElementType>::~BST(){

    if (root != NULL){
        deleteR(root);
    }
}

//Description: Helper for destructor (basically postOrderTraversal)
template <class ElementType>
void BST<ElementType>::deleteR(BSTNode<ElementType>* current){

    if (current->hasLeft()){
        deleteR(current->left);
    }
    if (current->hasRight()){
        deleteR(current->right);
    }

    delete current;
    current = NULL;
}

// Description: Returns the number of elements in the BST
// Time efficiency: O(1)
template <class ElementType>
int BST<ElementType>::getElementCount() const {
    return elementCount;
}

// Description: Inserts a new element into the BST
// Time efficiency: O(log2 n)
// Pre Condition: Element not already in BST
// Post Condition: BST is still a Binary Search Tree and element count incrememented by 1
template <class ElementType>
void BST<ElementType>::insert(const ElementType& newElement) throw(ElementAlreadyExistsInBSTException){

    if (root == NULL){
        BSTNode<ElementType>* newNode = new BSTNode<ElementType>(newElement);
        root = newNode;
        elementCount++;
    } else {

        bool success = insertR(newElement, root);
        if (!success){
            throw ElementAlreadyExistsInBSTException("Element already present in BST");
        }
    }
}

//Description: Helper for insert
template <class ElementType>
bool BST<ElementType>::insertR(const ElementType& element, BSTNode<ElementType>* current){

    if (current->element == element) {
        return false;
    } else if (current->element < element){
        if (current->hasRight()){
            return insertR(element, current->right);
        } else {
            BSTNode<ElementType>* newNode = new BSTNode<ElementType>(element);
            current->right = newNode;
        }
    } else {
        if (current->hasLeft()) {
            return insertR(element, current->left);
        } else {
            BSTNode<ElementType>* newNode = new BSTNode<ElementType>(element);
            current->left = newNode;
        }
    }

    elementCount++;
    return true;
}

// Description: Retrieves a target element from the BST
// Time efficiency: O(log2 n)
template <class ElementType>
ElementType& BST<ElementType>::retrieve(const ElementType& targetElement) const throw(ElementDoesNotExistInBSTException){
    if (root == NULL){
        throw ElementDoesNotExistInBSTException("BST is empty");
    } else {
        try {
            return retrieveR(targetElement, root);
        } catch(ElementDoesNotExistInBSTException& e){
            throw e;
        }
    }
}

//Description: Helper for retrieve
template <class ElementType>
ElementType& BST<ElementType>::retrieveR(const ElementType& targetElement, BSTNode<ElementType>* current) const throw(ElementDoesNotExistInBSTException){

    if (current->element == targetElement){
        return current->element;
    }
    if (current->element < targetElement){
        if (current->hasRight()){
            return retrieveR(targetElement, current->right);
        }
    } else {
        if (current->hasLeft()){
            return retrieveR(targetElement, current->left);
        }
    }
    throw ElementDoesNotExistInBSTException("Element not found in BST");
}

// Description: traverse the BST in order and "visit" each element
// Time efficiency: O(n)
template <class ElementType>
void BST<ElementType>::traverseInOrder(void visit(ElementType&)) const {
    if (root != NULL){
        traverseInOrderR(visit, root);
    } else {
        cout << "Root NULL, traverse ends here" << endl;
    }
}


//Description: Helper for traversInOrder
template <class ElementType>
void BST<ElementType>::traverseInOrderR(void visit(ElementType&), BSTNode<ElementType>* current) const {

    if (current->hasLeft()){
        traverseInOrderR(visit, current->left);
    }
    visit(current->element);
    if (current->hasRight()){
        traverseInOrderR(visit, current->right);
    }
}

template <class ElementType>
int BST<ElementType>::nodesCount() const {
    return countR(root);
}

template <class ElementType>
int BST<ElementType>::countR(BSTNode<ElementType>* current) const {
    if (current == NULL)
        return 0;
    else
        return 1 + countR(current->left) + countR(current->right);
}

template <class ElementType>
ElementType& BST<ElementType>::min() const {
    if (root == NULL) {
        throw ElementDoesNotExistInBSTException("No Min element");
    } else {
        return minR(root);
    }
}

template <class ElementType>
ElementType& BST<ElementType>::minR(BSTNode<ElementType>* current) const {
    if (current->hasLeft()){
        return minR(current->left);
    } else {
        return current->element;
    }
}

template <class ElementType>
ElementType& BST<ElementType>::max() const {
    if (root == NULL) {
        throw ElementDoesNotExistInBSTException("No Max element");
    } else {
        return maxR(root);
    }
}

template <class ElementType>
ElementType& BST<ElementType>::maxR(BSTNode<ElementType>* current) const {
    if (current->hasRight()){
        return maxR(current->right);
    } else {
        return current->element;
    }
}

template <class ElementType>
int BST<ElementType>::duplicate(const ElementType& targetElement) const {
    if (root == NULL){
        return 0;
    } else {
        return duplicateR(root, targetElement, 0);
    }
}

template <class ElementType>
int BST<ElementType>::duplicateR(BSTNode<ElementType>* current, const ElementType& target, int count) const {
    int newCount = count;
    if (current->element == target) {
        newCount++;
    }

    if (current->hasLeft()){
        newCount = duplicateR(current->left, target, newCount);
    }
    if (current->hasRight()){
        newCount = duplicateR(current->right, target, newCount);
    }
    return newCount;
}

template <class ElementType>
void BST<ElementType>::remove(const ElementType& targetElement) const throw(ElementDoesNotExistInBSTException) {

    if (root == NULL) {
        throw ElementDoesNotExistInBSTException("BST is empty");
    } else {
        BSTNode<ElementType>* parent = NULL;
        BSTNode<ElementType>* current = root;
        bool found = false;

        while (current != NULL && !found) {
            if (current->element == targetElement) {
                found = true;
            } else {
                parent = current;
                if (current->element < targetElement) {
                    current = current->right;
                } else {
                    current = current->left;
                }
            }
        }

        if (!found) {
            throw ElementDoesNotExistInBSTException("Element not found");
        }

        // cases
        if (current->isLeaf()) {

            cout << "Element is a leaf" << endl;

            if (parent->right->element == current->element)
                parent->right = NULL;
            else
                parent->left = NULL;
            delete current;
            current = NULL;

        } else if (current->hasLeft() && !current->hasRight()) {

            cout << "Element has empty right" << endl;

            if (parent->right->element == current->element)
                parent->right = current->left;
            else
                parent->left = current->left;
            delete current;
            current = NULL;

        } else if (!current->hasLeft() && current->hasRight()) {

            cout << "Element has empty left" << endl;

            if (parent->right->element == current->element)
                parent->right = current->right;
            else
                parent->left = current->right;
            delete current;
            current = NULL;

        } else {

            cout << "Element has no empty children" << endl;

            ElementType predecessor = findPredecessor(current);
            remove(predecessor);
            current->element = predecessor;

        }
    }
}

template <class ElementType>
ElementType& BST<ElementType>::findPredecessor(BSTNode<ElementType>* current) const {

    BSTNode<ElementType>* traversalNode = current;

    traversalNode = traversalNode->left;

    while (traversalNode->hasLeft()){
        traversalNode = traversalNode->right;
    }

    return traversalNode->element;

}