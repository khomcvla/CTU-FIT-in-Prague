#include <iostream>
#include <stdlib.h>

//------------------------------------------------------------------------------
class CVertex
{
public:
  //----------------------------
  CVertex(int key)
  {
    _key = key;
    _height = 1;

    _parent = nullptr;
    _leftSon = nullptr;
    _rightSon = nullptr;

    _successor = nullptr;
    _predeccessor = nullptr;

    _in_AVL = nullptr;
    _in_BST = nullptr;
    _in_LIST = nullptr;
  }
  //----------------------------
  int _key;
  int _height;

  CVertex *_parent;
  CVertex *_leftSon;
  CVertex *_rightSon;

  CVertex *_successor;
  CVertex *_predeccessor;

  CVertex *_in_AVL;
  CVertex *_in_BST;
  CVertex *_in_LIST;
};
//------------------------------------------------------------------------------
CVertex *_root_BST = nullptr;
CVertex *_root_AVL = nullptr;
CVertex *_root_LIST = nullptr;
//------------------------------------------------------------------------------
int height_AVL(CVertex *node)
{
  if (!node)
    return 0;

  return node->_height;
}
//------------------------------------------------------------------------------
int getBalance_AVL(CVertex *node)
{
  if (!node)
    return 0;

  return height_AVL(node->_leftSon) - height_AVL(node->_rightSon);
}
//------------------------------------------------------------------------------
CVertex *findKey_AVL(CVertex *root, int key)
{
  if (!root)
    return root;

  if (key < root->_key)
    return findKey_AVL(root->_leftSon, key);

  else if (key > root->_key)
    return findKey_AVL(root->_rightSon, key);

  return root;
}
//------------------------------------------------------------------------------
CVertex *rightRotate_AVL(CVertex *y)
{
  CVertex *x = y->_leftSon;
  CVertex *T2 = x->_rightSon;

  // Perform rotation
  x->_rightSon = y;
  y->_leftSon = T2;

  // Update heights
  y->_height = 1 + std::max(height_AVL(y->_leftSon),
                            height_AVL(y->_rightSon));

  x->_height = 1 + std::max(height_AVL(x->_leftSon),
                            height_AVL(x->_rightSon));

  // Return new root
  return x;
}
//------------------------------------------------------------------------------
CVertex *leftRotate_AVL(CVertex *x)
{
  CVertex *y = x->_rightSon;
  CVertex *T2 = y->_leftSon;

  // Perform rotation
  y->_leftSon = x;
  x->_rightSon = T2;

  //  Update heights
  x->_height = 1 + std::max(height_AVL(x->_leftSon),
                            height_AVL(x->_rightSon));

  y->_height = 1 + std::max(height_AVL(y->_leftSon),
                            height_AVL(y->_rightSon));

  // Return new root
  return y;
}
//------------------------------------------------------------------------------
void leftRotate_BST(CVertex *node)
{
  CVertex *y = node->_rightSon;
  CVertex *T2 = y->_leftSon;

  y->_leftSon = node;
  y->_parent = node->_parent;
  node->_rightSon = T2;

  if (T2)
    T2->_parent = node;

  if (node->_parent)
  {
    if (node->_parent->_key > node->_key)
      node->_parent->_leftSon = y;
    else
      node->_parent->_rightSon = y;
  }
  else
    _root_BST = y;

  node->_parent = y;
}
//------------------------------------------------------------------------------
void rightRotate_BST(CVertex *node)
{
  CVertex *x = node->_leftSon;
  CVertex *T2 = x->_rightSon;

  x->_rightSon = node;
  x->_parent = node->_parent;
  node->_leftSon = T2;

  if (T2)
    T2->_parent = node;

  if (node->_parent)
  {
    if (node->_parent->_key > node->_key)
      node->_parent->_leftSon = x;
    else
      node->_parent->_rightSon = x;
  }
  else
    _root_BST = x;

  node->_parent = x;
}
//------------------------------------------------------------------------------
void updateParent(CVertex *node)
{
  if (node->_leftSon)
    node->_leftSon->_parent = node;

  if (node->_rightSon)
    node->_rightSon->_parent = node;
}
//------------------------------------------------------------------------------
void updatePredecessor(CVertex *node, CVertex *son)
{
  if (node->_in_LIST)
  {
    if (!node->_in_LIST->_predeccessor)
    {
      node->_in_LIST->_predeccessor = son->_in_LIST;
      son->_in_LIST->_successor = node->_in_LIST;
    }
    else
    {
      if (node->_in_LIST->_predeccessor->_key < son->_in_LIST->_key)
      {
        son->_in_LIST->_predeccessor = node->_in_LIST->_predeccessor;
        node->_in_LIST->_predeccessor->_successor = son->_in_LIST;

        node->_in_LIST->_predeccessor = son->_in_LIST;
        son->_in_LIST->_successor = node->_in_LIST;
      }
    }
  }
}
//------------------------------------------------------------------------------
void updateSuccessor(CVertex *node, CVertex *son)
{
  if (node->_in_LIST)
  {
    if (!node->_in_LIST->_successor)
    {
      node->_in_LIST->_successor = son->_in_LIST;
      son->_in_LIST->_predeccessor = node->_in_LIST;
    }
    else
    {
      if (node->_in_LIST->_successor->_key > son->_in_LIST->_key)
      {
        node->_in_LIST->_successor->_predeccessor = son->_in_LIST;
        son->_in_LIST->_successor = node->_in_LIST->_successor;

        node->_in_LIST->_successor = son->_in_LIST;
        son->_in_LIST->_predeccessor = node->_in_LIST;
      }
    }
  }
}
//------------------------------------------------------------------------------
CVertex *insert_AVL(CVertex *node, CVertex *son)
{
  if (!node)
  {
    CVertex *son_LIST = new CVertex(son->_key);

    son->_in_LIST = son_LIST;
    son_LIST->_in_AVL = son;

    return son;
  }

  // Left Son
  if (son->_key < node->_key)
  {
    node->_leftSon = insert_AVL(node->_leftSon, son);
    updatePredecessor(node, son);
  }
  // Right Son
  else if (son->_key > node->_key)
  {
    node->_rightSon = insert_AVL(node->_rightSon, son);
    updateSuccessor(node, son);
  }
  // Similar Node
  else
    return node;

  node->_height = 1 + std::max(height_AVL(node->_leftSon),
                               height_AVL(node->_rightSon));

  int balance = getBalance_AVL(node);

  // Left Left
  if (balance > 1 && son->_key < node->_leftSon->_key)
    return rightRotate_AVL(node);

  // Right Right
  if (balance < -1 && son->_key > node->_rightSon->_key)
    return leftRotate_AVL(node);

  // Left Right
  if (balance > 1 && son->_key > node->_leftSon->_key)
  {
    node->_leftSon = leftRotate_AVL(node->_leftSon);
    return rightRotate_AVL(node);
  }

  // Right Left
  if (balance < -1 && son->_key < node->_rightSon->_key)
  {
    node->_rightSon = rightRotate_AVL(node->_rightSon);
    return leftRotate_AVL(node);
  }

  return node;
}
//------------------------------------------------------------------------------
CVertex *insert_BST(CVertex *node, CVertex *son)
{
  if (!node)
    return son;

  if (son->_key < node->_key)
    node->_leftSon = insert_BST(node->_leftSon, son);

  else if (son->_key > node->_key)
    node->_rightSon = insert_BST(node->_rightSon, son);

  updateParent(node);

  return node;
}
//------------------------------------------------------------------------------
CVertex *minValueNode(CVertex *node)
{
  CVertex *current = node;

  while (current->_leftSon)
    current = current->_leftSon;

  return current;
}
//------------------------------------------------------------------------------
CVertex *remove_AVL(CVertex *root, int key)
{
  if (!root)
    return root;

  // Jump to the left subtree and try to find key
  if (key < root->_key)
    root->_leftSon = remove_AVL(root->_leftSon, key);

  // Jump to the right subtree and try to find key
  else if (key > root->_key)
    root->_rightSon = remove_AVL(root->_rightSon, key);

  // Same key
  else
  {
    if ((!root->_leftSon) || (!root->_rightSon))
    {
      CVertex *tmp = root->_leftSon ? root->_leftSon : root->_rightSon;

      if (!tmp)
      {
        if (root->_in_LIST->_predeccessor)
          root->_in_LIST->_predeccessor->_successor = root->_in_LIST->_successor;

        if (root->_in_LIST->_successor)
          root->_in_LIST->_successor->_predeccessor = root->_in_LIST->_predeccessor;

        tmp = root;
        root = nullptr;
      }
      else
      {
        *root = *tmp;

        if (root->_in_LIST->_predeccessor)
          root->_in_LIST->_predeccessor->_successor = root->_in_LIST->_successor;

        if (root->_in_LIST->_successor)
          root->_in_LIST->_successor->_predeccessor = root->_in_LIST->_predeccessor;

        root->_in_LIST->_in_AVL = root;
      }

      delete tmp;
    }
    else
    {
      CVertex *tmp = minValueNode(root->_rightSon);

      root->_key = tmp->_key;

      if (root->_in_LIST->_predeccessor)
        root->_in_LIST->_predeccessor->_successor = tmp->_in_LIST->_successor;

      root->_in_LIST = tmp->_in_LIST;
      root->_in_LIST->_in_AVL = root;

      root->_rightSon = remove_AVL(root->_rightSon, tmp->_key);
    }
  }

  if (!root)
    return root;

  root->_height = 1 + std::max(height_AVL(root->_leftSon),
                               height_AVL(root->_rightSon));

  int balance = getBalance_AVL(root);

  // Left Left Case
  if (balance > 1 && getBalance_AVL(root->_leftSon) >= 0)
    return rightRotate_AVL(root);

  // Left Right Case
  if (balance > 1 && getBalance_AVL(root->_leftSon) < 0)
  {
    root->_leftSon = leftRotate_AVL(root->_leftSon);
    return rightRotate_AVL(root);
  }

  // Right Right Case
  if (balance < -1 && getBalance_AVL(root->_rightSon) <= 0)
    return leftRotate_AVL(root);

  // Right Left Case
  if (balance < -1 && getBalance_AVL(root->_rightSon) > 0)
  {
    root->_rightSon = rightRotate_AVL(root->_rightSon);
    return leftRotate_AVL(root);
  }

  return root;
}
//------------------------------------------------------------------------------
CVertex *remove_BST(CVertex *root, int key)
{
  if (!root)
    return root;

  // Jump to the left subtree and try to find key
  if (key < root->_key)
    root->_leftSon = remove_BST(root->_leftSon, key);

  // Jump to the right subtree and try to find key
  else if (key > root->_key)
    root->_rightSon = remove_BST(root->_rightSon, key);

  // Same key
  else
  {
    // node with only one child or no child
    if (!root->_leftSon)
    {
      CVertex *temp = root->_rightSon;

      if (temp)
      {
        if (!root->_parent)
          temp->_parent = nullptr;
        else
          temp->_parent = root->_parent;
      }

      // delete root;
      return temp;
    }
    else if (!root->_rightSon)
    {
      CVertex *temp = root->_leftSon;

      if (temp)
      {
        if (!root->_parent)
          temp->_parent = nullptr;
        else
          temp->_parent = root->_parent;
      }

      // delete root;
      return temp;
    }

    CVertex *tmp = minValueNode(root->_in_LIST->_rightSon);

    root->_key = tmp->_key;

    root->_in_LIST = tmp->_in_LIST;
    root->_in_LIST->_in_BST = root;

    root->_rightSon = remove_BST(root->_rightSon, tmp->_key);
  }

  return root;
}
//------------------------------------------------------------------------------
void insert(int key)
{
  CVertex *finded = findKey_AVL(_root_AVL, key);

  if (!finded)
  {
    CVertex *son_AVL = new CVertex(key);
    CVertex *son_BST = new CVertex(key);

    _root_AVL = insert_AVL(_root_AVL, son_AVL);
    _root_BST = insert_BST(_root_BST, son_BST);

    son_BST->_in_LIST = son_AVL->_in_LIST;
    son_AVL->_in_LIST->_in_BST = son_BST;
  }
}
//------------------------------------------------------------------------------
void remove(int key)
{
  _root_AVL = remove_AVL(_root_AVL, key);
  _root_BST = remove_BST(_root_BST, key);
}
//------------------------------------------------------------------------------
void rotate(int key)
{
  int rotation;
  std::cin >> rotation;

  CVertex *node = findKey_AVL(_root_AVL, key);

  if (!node)
  {
    std::cout << "notfound" << std::endl;
    return;
  }

  node = node->_in_LIST->_in_BST;

  if ((rotation == 1 && !node->_rightSon) ||
      (rotation == 2 && !node->_leftSon))
  {
    std::cout << "norotate" << std::endl;
    return;
  }

  if (rotation == 1)
    leftRotate_BST(node);

  else if (rotation == 2)
    rightRotate_BST(node);
}
//------------------------------------------------------------------------------
void findParent(int key)
{
  CVertex *node = findKey_AVL(_root_AVL, key);

  if (!node)
  {
    std::cout << "notfound" << std::endl;
    return;
  }

  node = node->_in_LIST->_in_BST;

  if (!node->_parent)
    std::cout << "noparent" << std::endl;
  else
    std::cout << node->_parent->_key << std::endl;
}
//------------------------------------------------------------------------------
void findSuccessor(int key)
{
  CVertex *node = findKey_AVL(_root_AVL, key);

  if (!node)
  {
    std::cout << "notfound" << std::endl;
    return;
  }

  if (!node->_in_LIST->_successor)
    std::cout << "nosuccessor" << std::endl;
  else
    std::cout << node->_in_LIST->_successor->_in_AVL->_key << std::endl;
}
//------------------------------------------------------------------------------
int main()
{
  int request;
  int key;

  while (true)
  {
    std::cin >> request >> key;

    if (request == 1)
      insert(key);
    else if (request == 2)
      remove(key);
    else if (request == 3)
      findParent(key);
    else if (request == 4)
      findSuccessor(key);
    else if (request == 5)
      rotate(key);
    else if (request == 6)
      break;
  }

  CVertex *tmp = _root_LIST;

  while (_root_LIST)
  {
    _root_LIST = tmp->_successor;
    delete tmp;
  }

  return 0;
}