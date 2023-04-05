#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <iostream>

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int* heightCounter(Node * node, char direction, int* depths);

int* heightCounter(Node * node, char direction, int* depths)
{
    if(node == NULL){
      return depths;
    }
    if(node->left != NULL || node->right != NULL){
      if(direction == 'l' ){
        depths[0] += 1;
        heightCounter(node->left, 'l', depths);
        heightCounter(node->right, 'l', depths);
      }
      else if(direction == 'r' ){
        depths[1] += 1;
        heightCounter(node->right, 'r', depths);
        heightCounter(node->left, 'r', depths);
      }
      else if(direction == 'x' && (node->right != NULL || node->left != NULL)){
        depths[0]+= 1;
        depths[1]+= 1;
        heightCounter(node->right, 'r', depths);
        heightCounter(node->left, 'l', depths);
      }

    }
    
    return depths;

}
  
bool equalPaths(Node * root)
{
  
    int* heights = new int[2]{0, 0};
    int* newHeights;

    newHeights = heightCounter(root, 'x', heights);

    if(root != NULL && ((root->left != NULL && root->right != NULL) || (root->left != NULL || root->right != NULL))){
      if(newHeights[1] != newHeights[0]){
        delete[] heights;
        return false;
      }
    }
    
    delete[] heights;

    return true;

}


