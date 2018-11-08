#include <iostream>
#include <stdlib.h>

//==============================================================================
class CGraph
{
public:
  //------------------------------------------------
  class CVertex
  {
  public:
    //----------------------------
    CVertex(int key)
    {
      _key = key;
      _parent = nullptr;
      _leftSon = nullptr;
      _rightSon = nullptr;
    }
    //----------------------------
    void deleteSon()
    {
      if (_leftSon)
      {
        _leftSon->deleteSon();

        if (_leftSon)
          delete _leftSon;
      }

      if (_rightSon)
      {
        _rightSon->deleteSon();

        if (_rightSon)
          delete _rightSon;
      }
    }
    //----------------------------
    int _key;
    CVertex *_parent;
    CVertex *_leftSon;
    CVertex *_rightSon;
  };

  //------------------------------------------------
  CVertex *_root;

  //================================================
  CGraph()
  {
    _root = nullptr;
  }
  //------------------------------------------------
  CGraph(CVertex *root)
  {
    _root = root;
  }
  //------------------------------------------------
  ~CGraph()
  {
    if (_root)
    {
      _root->deleteSon();
      delete _root;
    }
  }
  //------------------------------------------------
  void insert(int key)
  {
    if (_root == nullptr)
    {
      _root = new CVertex(key);
      return;
    }

    CVertex *tmp = _root;
    CVertex *tmp_son;

    while (true)
    {
      if (tmp->_key > key)
        tmp_son = tmp->_leftSon;
      else
        tmp_son = tmp->_rightSon;

      if (!tmp_son)
      {
        if (tmp->_key > key)
        {
          tmp->_leftSon = new CVertex(key);
          tmp->_leftSon->_parent = tmp;
        }
        else
        {
          tmp->_rightSon = new CVertex(key);
          tmp->_rightSon->_parent = tmp;
        }
        break;
      }
      else
        tmp = tmp_son;
    }
  }
  //------------------------------------------------
  void read(int key)
  {
    CVertex *findedKey = findKey(key);

    if (!findedKey)
      std::cout << "notfound" << std::endl;
    else if (!findedKey->_parent)
      std::cout << "noparent" << std::endl;
    else
      std::cout << findedKey->_parent->_key << std::endl;
  }
  //------------------------------------------------
  void remove(int key)
  {
    CVertex *node = findKey(key);
    CVertex *tmp;

    if (!node)
      return;

    if ((!node->_leftSon && !node->_rightSon) ||
        (node->_leftSon && !node->_rightSon) ||
        (!node->_leftSon && node->_rightSon))
    {
      if (node->_leftSon)
        tmp = node->_leftSon;
      else if (node->_rightSon)
        tmp = node->_rightSon;
      else
        tmp = nullptr;

      if (node->_parent)
      {
        if (node->_key < node->_parent->_key)
          node->_parent->_leftSon = tmp;
        else
          node->_parent->_rightSon = tmp;

        if (tmp)
          tmp->_parent = node->_parent;

        return;
      }

      _root = tmp;
      if (tmp)
        tmp->_parent = nullptr;

      delete node;
    }
    else
    {
      CVertex *heir = node->_rightSon;
      while (true)
      {
        if (heir->_leftSon == nullptr)
          break;
        heir = heir->_leftSon;
      }

      remove(heir->_key);
      node->_key = heir->_key;
    }
  }
  //------------------------------------------------
  void rotate(int key)
  {
    int direction;
    std::cin >> direction;

    CVertex *node = findKey(key);

    if (!node)
    {
      std::cout << "notfound" << std::endl;
      return;
    }

    CVertex *x;
    CVertex *T2;

    // Left Rotation
    if (direction == 1)
    {
      if (!node->_rightSon)
      {
        std::cout << "norotate" << std::endl;
        return;
      }

      x = node->_rightSon;
      T2 = x->_leftSon;

      x->_leftSon = node;
      node->_rightSon = T2;
    }
    // Right Rotation
    else if (direction == 2)
    {
      if (!node->_leftSon)
      {
        std::cout << "norotate" << std::endl;
        return;
      }

      x = node->_leftSon;
      T2 = x->_rightSon;

      x->_rightSon = node;
      node->_leftSon = T2;
    }

    // Finishing recording parents
    x->_parent = node->_parent;

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
      _root = x;

    node->_parent = x;
  }
  //------------------------------------------------
  void findHeir(int key)
  {
    CVertex *node = findKey(key);

    if (!node)
    {
      std::cout << "notfound" << std::endl;
      return;
    }

    if (!node->_rightSon)
    {
      if (node->_parent)
      {
        // if key is predecessor
        if (node->_key < node->_parent->_key)
          std::cout << node->_parent->_key << std::endl;

        else if (node->_key > node->_parent->_key)
        {
          // try to find first greater key
          CVertex *tmp = node->_parent;

          while (tmp->_parent && tmp->_key > tmp->_parent->_key)
            tmp = tmp->_parent;

          if (tmp->_parent)
            std::cout << tmp->_parent->_key << std::endl;
          else
            // if "iterator" got root
            std::cout << "nosuccessor" << std::endl;
        }
      }
      // if key is root
      else
        std::cout << "nosuccessor" << std::endl;

      return;
    }

    // if key has right subtree
    CVertex *heir = node->_rightSon;
    while (true)
    {
      if (heir->_leftSon == nullptr)
        break;
      heir = heir->_leftSon;
    }

    std::cout << heir->_key << std::endl;
  }
  //------------------------------------------------
  CVertex *findKey(int key)
  {
    CVertex *tmp = _root;

    while (true)
    {
      if (tmp == nullptr || tmp->_key == key)
        break;

      // try to find key in left subtree
      else if (key < tmp->_key)
        tmp = tmp->_leftSon;

      // try to find key in right subtree
      else if (tmp->_key < key)
        tmp = tmp->_rightSon;
    }

    return tmp;
  };
};
//==============================================================================
int main()
{
  int request;
  int key;

  CGraph::CVertex *root = nullptr;
  CGraph g(root);

  while (true)
  {
    std::cin >> request >> key;

    if (request == 1)
      g.insert(key);
    else if (request == 2)
      g.remove(key);
    else if (request == 3)
      g.read(key);
    else if (request == 4)
      g.findHeir(key);
    else if (request == 5)
      g.rotate(key);
    else if (request == 6)
      break;
  }

  return 0;
}