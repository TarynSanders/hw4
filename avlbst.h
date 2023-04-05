#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };
//credit given to geeksforgeeks for their tutorials and ofc the slides!
/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
      virtual void insertfix (AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node); // TODO
      virtual void removefix (AVLNode<Key,Value>* n, int diff); // TODO
      virtual void rotateRight (AVLNode<Key,Value>* node); // TODO
      virtual void rotateLeft (AVLNode<Key,Value>* node); // TODO


};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */

template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    /** If empty tree => set n as root, b(n) = 0, done!
      Else insert n (by walking the tree to a leaf, p, and
      inserting the new node as its child), set balance
      to 0, and look at its parent, p
        – If b(p) was -1, then b(p) = 0. Done!
        – If b(p) was +1, then b(p) = 0. Done!
        – If b(p) was 0, then update b(p) and call insert-fix(p, n)
    */

    AVLNode<Key,Value>* AVLnaurnode = new AVLNode<Key,Value>(new_item.first, new_item.second, NULL);
    AVLnaurnode->setBalance(0);

    if(this->empty()){
        this->root_ = AVLnaurnode;
        return;
    }
    else{

      //Node<Key, Value>* current = this->root_;

      AVLNode<Key, Value>* currentAVL = static_cast<AVLNode<Key, Value>*>(this->root_);
      // Traverse the tree to find the correct position to insert the node
      while(true){
        // if(new_item.first == currentAVL->getKey()){ //lets check first if it exists already since our code wants to act up omfg
        //   currentAVL->setValue(new_item.second);
        //   delete AVLnaurnode;
        //   break;
        // }
        if(new_item.first < currentAVL->getKey()){ // Go left since the left subtree of a node contains only keys that are less than the node's key
          if(currentAVL->getLeft() == nullptr){
          //  node = new Node<Key, Value>(new_item.first, new_item.second, current);
            currentAVL->setLeft(AVLnaurnode);
            AVLnaurnode->setParent(currentAVL);
            
            if(currentAVL->getBalance() == 1 || currentAVL->getBalance() == -1 ){
              currentAVL->setBalance(0);
            }
            else if(currentAVL->getBalance() == 0){
              currentAVL->setBalance(-1);
              insertfix(currentAVL, AVLnaurnode);
            }
            break;
            
          }
          else{
            currentAVL = currentAVL->getLeft();
          }
        }
        else if(new_item.first > currentAVL->getKey()){ // Go right since the right subtree contains only keys that are greater than the node's key
          if(currentAVL->getRight() == nullptr){
            currentAVL->setRight(AVLnaurnode);
            AVLnaurnode->setParent(currentAVL);

            if(currentAVL->getBalance() == -1 || currentAVL->getBalance() == 1){
              currentAVL->setBalance(0);
            }
            else if(currentAVL->getBalance() == 0){
              currentAVL->setBalance(1);
              insertfix(currentAVL, AVLnaurnode);
            }
            break;
          }
          else{
            currentAVL = currentAVL->getRight();
          }
        }
        //Key already exists, update the value
        else{
          currentAVL->setValue(new_item.second);
          delete AVLnaurnode;
          break;
        }
      }

      return;
      
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO

    if(this->empty()) {
        return; // Tree is empty, nothing to remove
    }

    // Find the node to remove
    Node<Key, Value>* nodeToRemove = this->internalFind(key);
    if (nodeToRemove == nullptr) {
        return; // Key not found, nothing to remove
    }
    int diff;

    // If nodeToRemove is the root of the tree, handle it differently
    if (nodeToRemove == this->root_) {
        if (nodeToRemove->getRight() != nullptr && nodeToRemove->getLeft() != nullptr) {
            // Find the predecessor and swap the values of the two nodes
            Node<Key, Value>* predecessor = BinarySearchTree<Key, Value>::predecessor(nodeToRemove);
    
            nodeSwap(static_cast<AVLNode<Key,Value>*>(predecessor), static_cast<AVLNode<Key,Value>*>(nodeToRemove));
        }
        else {
            // Update the root to be the non-null child or nullptr if both children are null
            if (nodeToRemove->getRight() != nullptr) {
                this->root_ = nodeToRemove->getRight();
                nodeToRemove->getRight()->setParent(nullptr);
            }
            else if(nodeToRemove->getLeft() != nullptr){
                this->root_ = nodeToRemove->getLeft();
                nodeToRemove->getLeft()->setParent(nullptr);
            }
            else{ //no children
                this->root_ = nullptr;
            }
            delete nodeToRemove;
            return;
        }
    }

    // If nodeToRemove has 2 children, swap with its predecessor
    if (nodeToRemove->getRight() != nullptr && nodeToRemove->getLeft() != nullptr) {
        Node<Key, Value>* predecessor = BinarySearchTree<Key, Value>::predecessor(nodeToRemove);
        nodeSwap(static_cast<AVLNode<Key,Value>*>(nodeToRemove), static_cast<AVLNode<Key,Value>*>(predecessor));
        // nodeToRemove = predecessor;
    }

    // If nodeToRemove is a leaf node without children
    if (nodeToRemove->getRight() == nullptr && nodeToRemove->getLeft() == nullptr) {
        if (nodeToRemove->getParent() != nullptr) {
            // if the node to be removed is the left child of its parent, make the left child of the parent nullptr
            if (nodeToRemove->getParent()->getLeft() == nodeToRemove) {
              diff = 1;
              nodeToRemove->getParent()->setLeft(nullptr);
                
            }
            else {
              diff = -1;
              nodeToRemove->getParent()->setRight(nullptr);
            }
            removefix(static_cast<AVLNode<Key,Value>*>(nodeToRemove->getParent()), diff);
            delete nodeToRemove;
        }
    }
    // If nodeToRemove has 1 child
    else{ 
        if(nodeToRemove->getLeft()!= nullptr && nodeToRemove->getParent()!= nullptr){
            // promote the left child
            //nodeSwap(nodeToRemove, nodeToRemove->getLeft());
            if (nodeToRemove->getParent()->getLeft() == nodeToRemove) {
              diff = 1;
              nodeToRemove->getParent()->setLeft(nodeToRemove->getLeft());
            }
            else {
              diff = -1;
              nodeToRemove->getParent()->setRight(nodeToRemove->getLeft());
            }
            nodeToRemove->getLeft()->setParent(nodeToRemove->getParent());
            removefix(static_cast<AVLNode<Key,Value>*>(nodeToRemove->getParent()), diff);
            delete nodeToRemove;
        }
        else if(nodeToRemove->getRight()!= nullptr && nodeToRemove->getParent()!= nullptr){
            // promote the right child
            if (nodeToRemove->getParent()->getRight() == nodeToRemove) {
                diff = -1;
                nodeToRemove->getParent()->setRight(nodeToRemove->getRight());
            }
            else {
                diff = 1;
                nodeToRemove->getParent()->setLeft(nodeToRemove->getRight());
            }
            nodeToRemove->getRight()->setParent(nodeToRemove->getParent());
            removefix(static_cast<AVLNode<Key,Value>*>(nodeToRemove->getParent()), diff);
            delete nodeToRemove;
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertfix( AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node)
{
    //todo

    if(node == nullptr || parent == nullptr || parent->getParent() == nullptr){
      return;
    }

    AVLNode<Key,Value>* grandparent = parent->getParent();

    //Assume p is left child of g [For right child swap left/right, +/-]
    

    if(parent == grandparent->getLeft()){//p is left child of g
    
      grandparent->updateBalance(-1);
      if(grandparent->getBalance() == 0){
        return;
      }
      else if(grandparent->getBalance() == -1){
        insertfix(grandparent, parent);
      }
      else if(grandparent->getBalance() == -2){

      //(grandparent->getRight() != nullptr && grandparent->getRight() == parent && parent->getRight() != nullptr && parent->getRight() == node)
      //(left-left or right right)
      //if(parent->getBalance()==-1){ 
        if((grandparent->getLeft() != nullptr && grandparent->getLeft() == parent && parent->getLeft() != nullptr && parent->getLeft() == node)){
          //rotate right grandparent
          rotateRight(grandparent);
          grandparent->setBalance(0);
          parent->setBalance(0);
        }
        //if left right
        //else if(parent->getBalance()==1){
        else if(grandparent->getLeft() != nullptr && grandparent->getLeft() == parent && parent->getRight() != nullptr && parent->getRight() == node){
          rotateLeft(parent);
          rotateRight(grandparent);

          if(node->getBalance() == -1){
            parent->setBalance(0);
            grandparent->setBalance(1);
            node->setBalance(0);
        
          }
          else if(node->getBalance() == 0){
            parent->setBalance(0);
            grandparent->setBalance(0);
            node->setBalance(0);

          }
          else if(node->getBalance() == 1){
            parent->setBalance(-1);
            grandparent->setBalance(0);
            node->setBalance(0);

          }
        }
  
      }

    }

    else if(parent == grandparent->getRight()){//p is right child of g
    
      grandparent->updateBalance(1);

      if(grandparent->getBalance() == 0){
        return;
      }
      else if(grandparent->getBalance() == 1){
        insertfix(grandparent, parent);
        return;
      }
      else if(grandparent->getBalance() == 2){
        //if right right
        //if(parent->getBalance()==1){ 
        if((grandparent->getRight() != nullptr && grandparent->getRight() == parent && parent->getRight() != nullptr && parent->getRight() == node)){
          rotateLeft(grandparent);
          grandparent->setBalance(0);
          parent->setBalance(0);
        }
        //if right left
        //else if (parent->getBalance()==-1){
        else if(grandparent->getRight() != nullptr && grandparent->getRight() == parent && parent->getLeft() != nullptr && parent->getLeft() == node){
          rotateRight(parent);
          rotateLeft(grandparent);

          if(node->getBalance() == 1){
            parent->setBalance(0);
            grandparent->setBalance(-1);
            node->setBalance(0);
        
          }
          else if(node->getBalance() == 0){
            parent->setBalance(0);
            grandparent->setBalance(0);
            node->setBalance(0);

          }
          else if(node->getBalance() == -1){
            parent->setBalance(1);
            grandparent->setBalance(0);
            node->setBalance(0);
          }

        }
        
      }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::removefix( AVLNode<Key,Value>* n, int diff)
{
  
  if(n == nullptr){
    return;
  }
  AVLNode<Key, Value>* parent = n->getParent();
  AVLNode<Key, Value>* c;
  AVLNode<Key, Value>* g; 
  int nextdiff = -1;

  if(parent != nullptr && n == parent->getLeft()){  //if parent is not null, nextdiff is positive 1 instead
    nextdiff = 1;
  }

  if(diff == -1){ //ASSUME DIFF IS -1
    if(n->getBalance() + diff == -2){ //CASE 1
      c = n->getLeft(); //the taller of the children

      if(c->getBalance() == -1){ // CASE 1A: ZIG-ZIG CASE
        rotateRight(n);
        n->setBalance(0);
        c->setBalance(0);
        removefix(parent, nextdiff);
      }
      else if(c->getBalance() == 0){ //CASE 1B: ZIG-ZIG CASE
        rotateRight(n);
        n->setBalance(-1);
        c->setBalance(1);
        return;
        //DONE!
      }
      else if(c->getBalance() == 1){ //CASE 1C: ZIG-ZAG CASE
        g = c->getRight();
        rotateLeft(c);
        rotateRight(n);

        if(g->getBalance() == 1){
          n->setBalance(0);
          c->setBalance(-1);
          
        }
        else if(g->getBalance() == 0){
          n->setBalance(0);
          c->setBalance(0);
          
        }
        else if(g->getBalance() == -1){
          n->setBalance(1);
          c->setBalance(0);
          
        }
        g->setBalance(0);
        removefix(parent, nextdiff);
      }
    }
    else if((n->getBalance() + diff) == -1){ //CASE 2
      n->setBalance(-1);
      return;
      //DONE!
    }
    else if((n->getBalance() + diff) == 0){ //CASE 3
      n->setBalance(0);
      removefix(parent, nextdiff);
    }
  }
  else{ //ASSUME DIFF IS POSITIVE 1 SO WE MIRROR 
    if((n->getBalance() + diff) == 2){ //CASE 1
      c = n->getRight(); //the taller of the children

      if(c->getBalance() == 1){ // CASE 1A: ZIG-ZIG CASE
        rotateLeft(n);
        n->setBalance(0);
        c->setBalance(0);
        removefix(parent, nextdiff);
      }
      else if(c->getBalance() == 0){ //CASE 1B: ZIG-ZIG CASE
        rotateLeft(n);
        n->setBalance(1);
        c->setBalance(-1);
        return;
      }
      else if(c->getBalance() == -1){ //CASE 1C: ZIG-ZAG CASE
        g = c->getLeft();
        rotateRight(c);
        rotateLeft(n);

        if(g->getBalance() == -1){
          n->setBalance(0);
          c->setBalance(1);
          
        }
        else if(g->getBalance() == 0){
          n->setBalance(0);
          c->setBalance(0);
          
        }
        else if(g->getBalance() == 1){
          n->setBalance(-1);
          c->setBalance(0);
          
        }
        g->setBalance(0);
        removefix(parent, nextdiff);
      }
    }
    else if((n->getBalance() + diff) == 1){ //CASE 2
      n->setBalance(1);
      return;
    }
    else if((n->getBalance() + diff) == 0){ //CASE 3
      n->setBalance(0);
      removefix(parent, nextdiff);
    }
  }

}


template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* node)
{
  /*Define a left rotation as taking a right child, making it
  the parent and making the original parent the new left
  child*/

  /*
  Create a temporary node to hold the right child of the current node (which will become the new parent node).
  Make the right child's left subtree the new right subtree of the current node (which will become the new left child).
  If the current node has a parent, make the temporary node the child of the current node's parent in place of the current node.
  Otherwise, make the temporary node the new root of the tree.*/

  
  AVLNode<Key, Value>* newParent = node->getRight();
  AVLNode<Key, Value>* lostChild = newParent->getLeft();
  AVLNode<Key, Value>* nodesParent = node->getParent();

  if(newParent == nullptr || node == nullptr){
    return;
  }

  if(nodesParent != nullptr){
    newParent->setParent(nodesParent); //take our newParent and make ITS parent what was our ORIGINAL node's parent
    node->setRight(lostChild);
    if(nodesParent->getRight() == node){ //if our node is a right child
      nodesParent->setRight(newParent);
    }
    else if(nodesParent->getLeft() == node){ //if our node is a left child
      nodesParent->setLeft(newParent);
    }
  }
  else{ //root if its parent is nullptr
    newParent->setParent(nullptr);
    this->root_ = newParent;
    node->setRight(lostChild);
  }

  if(lostChild != nullptr){
    lostChild->setParent(node);
  }
  newParent->setLeft(node);
  node->setParent(newParent);

}


template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* node)
{
  /*Define a right rotation as taking a left child, making it
  the parent and making the original parent the new right
  child*/

  /*

  Create a temporary node to hold the left child of the current node (which will become the new parent node).
  Make the left child's right subtree the new left subtree of the current node (which will become the new right child).
  If the current node has a parent, make the temporary node the child of the current node's parent in place of the current node.
  Otherwise, make the temporary node the new root of the tree.
  
  */

  AVLNode<Key, Value>* newParent = node->getLeft();

  AVLNode<Key, Value>* lostChild = newParent->getRight();

  AVLNode<Key, Value>* nodesParent = node->getParent();

  if(newParent == nullptr || node == nullptr){
    return;
  }

  if(nodesParent != nullptr){
    newParent->setParent(nodesParent); //take our newParent and make ITS parent what was our ORIGINAL node's parent
    node->setLeft(lostChild);
    if(nodesParent->getRight() == node){ //if our node is a right child
      nodesParent->setRight(newParent);
    }
    else if(nodesParent->getLeft() == node){ //if our node is a left child
      nodesParent->setLeft(newParent);
    }
  }
  else{ //root if its parent is nullptr
    newParent->setParent(nullptr);
    this->root_ = newParent;
    node->setLeft(lostChild);
  }

  if(lostChild != nullptr){
    lostChild->setParent(node);
  }
  newParent->setRight(node);
  node->setParent(newParent);

}
#endif