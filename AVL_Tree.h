/**
 *  @file AVL_Tree.h
 *
 *  Template based AVL tree.
 *
 *  !!! I USED MY OWN VECTOR CLASS FOR THE TRAVERSAL FUNKTIONS, BECAUSE THE UNIVERSITY DID NOT ALLOW TO
 *  USE THE STL LIBRARY. SO YOU HAVE TO CHANGE THAT IN YOUR PROGRAM OR USE SIMPLE ARRAYS. !!!
 *
 *  http://de.wikipedia.org/wiki/AVL-Baum
 *
 *  Copyright 2010 Stefan Hermes
 *  AVL_Tree is free software: you can redistribute it and/or modify it under
 *  the terms of the GNU General Public License as published by the Free
 *  Software Foundation, either version 3 of the License, or (at your option)
 *  any later version.
 *  AVL_Tree is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 *  more details. http://www.gnu.org/licenses/.
 *
 *  @date Created on: 15.06.2010
 *  @author Stefan Hermes
 */

#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include "iostream"
#include "Vector.h"

using namespace std;

/**
 * Template based AVL tree.
 */
template<class T> class AVL_Tree {

private:

  /**
   * T value; that is stored in the node
   */
  T value;

  /**
   * AVL_Tree<T> *left; left subtree
   */
  AVL_Tree<T> *left;

  /**
   * AVL_Tree<T> *right; right subtree
   */
  AVL_Tree<T> *right;

  /**
   * The height of the tree
   */
  int height;

  /**
   * The amount of nodes in the tree.
   */
  int size;

  /**
   * Calculates the height of the tree. Height of the biggest subtree +1
   */
  void calcHeight() {
    if (this == NULL) {
      return;
    }
      if (left->getHeight() < right->getHeight()) {
        height = right->getHeight() + 1;
      } else {
        height = left->getHeight() + 1;
      }
  }

  /**
   * Calculates the size (nodes) of the tree. Size left + size right + 1
   */
  int calcSize() {
    if (this == NULL || size == -1) {
      return 0;
    }
    size = left->calcSize() + right->calcSize() + 1;
    return size;
  }

  /**
   * Singlerotate left if tree is unbalanced.
   */
  void singlerotate_left() {
    AVL_Tree<T> *new_left = new AVL_Tree<T> (value), *rr = right->right;
    new_left->left = left;
    new_left->right = right->left;
    new_left->calcHeight();
    new_left->calcSize();
    value = right->value;
    right->right = NULL;
    right->left = NULL;
    delete right;
    right = rr;
    left = new_left;
    left->calcSize();
  }

  /**
   * Doublerotate left if tree is unbalanced.
   */
  void doublerotate_left() {
    AVL_Tree<T> *new_left = new AVL_Tree<T> (value), *rlr = right->left->right;
    new_left->left = left;
    new_left->right = right->left->left;
    new_left->calcHeight();
    new_left->calcSize();
    value = right->left->value;
    right->left->right = NULL;
    right->left->left = NULL;
    delete right->left;
    right->left = rlr;
    right->left->calcHeight();
    right->calcSize();
    left = new_left;
    left->calcSize();
  }

  /**
   * Singlerotate right if tree is unbalanced.
   */
  void singlerotate_right() {
    AVL_Tree<T> *new_right = new AVL_Tree<T> (value), *ll = left->left;
    new_right->right = right;
    new_right->left = left->right;
    new_right->calcHeight();
    new_right->calcSize();
    value = left->value;
    left->left = NULL;
    left->right = NULL;
    delete left;
    left = ll;
    right = new_right;
    right->calcSize();
  }

  /**
   * Doublerotate right if tree is unbalanced.
   */
  void doublerotate_right() {
    AVL_Tree<T> *new_right = new AVL_Tree<T> (value), *lrl = left->right->left;
    new_right->right = right;
    new_right->left = left->right->right;
    new_right->calcHeight();
    new_right->calcSize();
    value = left->right->value;
    left->right->left = NULL;
    left->right->right = NULL;
    delete left->right;
    left->right = lrl;
    left->right->calcHeight();
    left->calcSize();
    right = new_right;
    right->calcSize();
  }

  /**
   * Returns balance of the tree left height - right height.
   * If absolute value is bigger than 1 rotate.
   *
   * @return balance value
   */
  int balance() {
    if(this == NULL){
      return 0;
    }
    if (left != NULL && right != NULL) {
      return (left->height - right->height);
    }
    if (left != NULL) {
      return left->height;
    }
    if (right != NULL) {
      return (-right->height);
    }
    return 0;
  }

  /**
   * Calls rotate functions to rebalance the tree.
   */
  void rebalance() {
    int b = balance();
    if (b > 1) {
      b = left->balance();
      if (b >= 0) {
        //cout << "singelrotate_right" << endl;
        singlerotate_right();
        return;
      }
      if (b <= 0) {
        //cout << "doubelrotate_right" << endl;
        doublerotate_right();
      }
    }
    if (b < -1) {
      b = right->balance();
      if (b <= 0) {
        //cout << "singelrotate_left" << endl;
        singlerotate_left();
        return;
      }
      if (b >= 0) {
        //cout << "doubelrotate_left" << endl;
        doublerotate_left();
      }
    }
  }

public:
  /**
   * Defaultconstructor
   */
  AVL_Tree() {
    left = NULL;
    right = NULL;
    size = 0;
    height = 0;
  }

  /**
   * Constructor returns AVL_Tree<T> with T t in the first node.
   *
   * @param T &t
   */
  AVL_Tree(T t) {
    value = t;
    left = NULL;
    right = NULL;
    size = 1;
    height = 1;
  }

  /**
   * Copyconstructor
   */
  AVL_Tree(const AVL_Tree<T> &other) {
    value = other.value;
    if (other.left != NULL) {
      left = new AVL_Tree<T> (*other.left);
    } else {
      left = NULL;
    }
    if (other.right != NULL) {
      right = new AVL_Tree<T> (*other.right);
    } else {
      right = NULL;
    }
    size = other.size;
    height = other.height;
  }

  /**
   * @param const AVL_Tree<T> &other
   * @return *this
   */
  AVL_Tree<T> &operator=(const AVL_Tree<T> &other) {
    if (this != &other) {
      value = other.value;
      if (other.left != NULL) {
        if (left != NULL) {
          delete left; //free memory
        }
        left = new AVL_Tree<T> (*other.left); //allocate new memory
      } else if (left != NULL) {
        delete left;
        left = NULL;
      }
      if (other.right != NULL) {
        if (right != NULL) {
          delete right;
        }
        right = new AVL_Tree<T> (*other.right);
      } else if (right != NULL) {
        delete right;
        right = NULL;
      }
      size = other.size;
      height = other.height;
    }
    return *this;
  }

  /**
   * Destructor
   */
  virtual ~AVL_Tree() {
    delete left;
    delete right;
  }

  /**
   * Deletes all nodes but not the tree.
   */
  void makeEmpty() {
    if (this != NULL) {
      if (left != NULL) {
        delete left;
        left = NULL;
      }
      if (right != NULL) {
        delete right;
        right = NULL;
      }
      size = 0;
      height = 0;
    }
  }

  /**
   * @return true if the tree is empty
   */
  bool empty() {
    if (this != NULL) {
      calcSize();
      return (size <= 0);
    } else {
      return true;
    }
  }

  /**
   * @return false if the left subtree is empty.
   */
  bool hasLeft() {
    return (left != NULL);
  }

  /**
   * @return false if the right subtree is empty.
   */
  bool hasRight() {
    return (right != NULL);
  }

  /**
   * @return left subtree pointer
   */
  AVL_Tree<T> *getLeft() {
    return left;
  }

  /**
   @return right subtree pointer
   */
  AVL_Tree<T> *getRight() {
    return right;
  }

  /**
   * Inserts the template parameter t in the tree if its not already in.
   *
   * @param T t
   */
  void insert(T t) {
    if (size <= 0) { //tree empty
      value = T(t);
      height = 1;
      size = 1;
      return;
    }
    if (t == value) { //value is already in
      return;
    }
    //search recursivly
    if (t < value) {
      if (left == NULL) {
        left = new AVL_Tree<T> (t);
      } else {
        left->insert(t);
      }
    }
    if (t > value) {
      if (right == NULL) {
        right = new AVL_Tree<T> (t);
      } else {
        right->insert(t);
      }
    }
    rebalance(); //rebalance
    calcHeight(); //if rebalanced calc new height
    calcSize(); //if a subtree is bigger than before insert
  }

  /*
   * Removes the template parameter t from the tree.
   *
   * @param T t
   */
  void remove(T t) {
    if (this == NULL) {
      return;
    }
    //search recursivly
    if (t > value) {
      right->remove(t);
    }
    if (t < value) {
      left->remove(t);
    }
    if (t == value) { //node found
      height = 0;
      AVL_Tree<T> *tmp = find(t); //points to actual element not-const
      if (left == NULL && right == NULL) { //node is a leaf
        size = -1; //mark node to remove
      } else {
        //node is no leaf, find node to replace
        int b = 0;
        b = tmp->balance();
        if (b <= 0) { //right tree is bigger, replace with the widest left node
          tmp = tmp->right; //from the right subtree
          tmp->left->calcSize();
          while (tmp->left != NULL) {
            tmp = tmp->left;
          }
          value = tmp->value; //new value
          right->remove(value); //remove the node
        } else { //left tree is bigger
          tmp = tmp->left;
          while (tmp->right != NULL) {
            tmp = tmp->right;
          }
          value = tmp->value;
          left->remove(value);
        }
      }
    }
    //delete marked node
    if (left != NULL) { //if found delete
      if (left->size == -1) {
        delete left;
        left = NULL;
      }
    }
    if (right != NULL) {
      if (right->size == -1) {
        delete right;
        right = NULL;
      }
    }
    //calculate actual values and rebalance
    calcHeight();
    calcSize();
    rebalance();
    calcHeight();
  }

  /**
   * Finds a Pointer to the subtree with value T t if the value is in the tree.
   *
   * @param T t value to find
   * @return AVL_Tree<T>* with t in the root
   */
  AVL_Tree<T> *find(T t) {
    if (this == NULL) {
      return NULL;
    }
    if (t == value) {
      return this;
    }
    if (t > value && right != NULL) {
      return right->find(t);
    }
    if (t < value && left != NULL) {
      return left->find(t);
    }
    return NULL;
  }

  bool contains(T t) {
    return (find(t) != NULL);
  }

  /**
   * Returns the value of the root.
   *
   * @return T
   */
  T &getValue() {
    return value;
  }

  /**
   * Returns the height of the tree
   *
   * @return height
   */
  int getHeight() {
    if(this != NULL){
      calcHeight();
      return height;
    }else{
      return 0;
    }
  }

  /**
   * Returns the size (number of the nodes) of the tree
   *
   * @return size
   */
  int getSize() {
    return calcSize();
  }

  /**
   * Fills a vector with the nodes in preorder-traversal
   * at the end of the Vector.
   *
   * @param Vector<T> *vec pointer to a vector
   */
  void preOrder(Vector<T> *vec) {
    if (this != NULL) {
      vec->addLast(value);
      left->preOrder(vec);
      right->preOrder(vec);
    }
  }

  /**
   * Fills a vector with the nodes in inorder-traversal
   * at the end of the Vector.
   *
   * @param Vector<T> *vec pointer to a vector
   */
  void inOrder(Vector<T> *vec) {
    if (this != NULL) {
      left->inOrder(vec);
      vec->addLast(value);
      right->inOrder(vec);
    }
  }

  /**
   * Fills a vector with the nodes in postorder-traversal
   * at the end of the Vector.
   *
   * @param Vector<T> *vec pointer to a vector
   */
  void postOrder(Vector<T> *vec) {
    if (this != NULL) {
      left->postOrder(vec);
      right->postOrder(vec);
      vec->addLast(value);
    }
  }
};

#endif /* AVL_TREE_H_ */
