#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <stdexcept>
#include <iostream>
template <typename T>
class Node {
private:
    T data;
    Node<T>* next;
    Node<T>* previous;

public:
    Node();
    explicit Node(T data);
    Node(T data, Node<T>* next, Node<T>* previous);
    T getData() const;
    void setData(T data);
    Node<T>* getNext() const;
    void setNext(Node<T>* next);
    Node<T>* getPrevious() const;
    void setPrevious(Node<T>* previous);
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    LinkedList();
    ~LinkedList();
    void addToFront(T data);
    void addToEnd(T data);
    void addAtIndex(T data, int index);
    void addBefore(Node<T>* node, T data);
    void addAfter(Node<T>* node, T data);
    T removeFromFront();
    T removeFromEnd();
    void removeTheFirst(T data);
    void removeAllOf(T data);
    T removeBefore(Node<T>* node);
    T removeAfter(Node<T>* node);
    bool elementExists(T data) const;
    Node<T>* find(T data) const;
    int indexOf(T data) const;
    T retrieveFront() const;
    T retrieveEnd() const;
    T retrieve(int index) const;
    void printList() const;
    void empty();
    int length() const;

private:
    Node<T>* createNode(T data);
    void deleteNode(Node<T>* node);
    void validateIndex(int index) const;
};

template <typename T> Node<T>::Node() : next(nullptr), previous(nullptr) {}

template <typename T>
Node<T>::Node(T data) : data(data), next(nullptr), previous(nullptr) {}

template <typename T>
Node<T>::Node(T data, Node<T> *next, Node<T> *previous)
    : data(data), next(next), previous(previous) {}

template <typename T> T Node<T>::getData() const { return data; }

template <typename T> void Node<T>::setData(T data) { this->data = data; }

template <typename T> Node<T> *Node<T>::getNext() const { return next; }

template <typename T> void Node<T>::setNext(Node<T> *next) {
  this->next = next;
}

template <typename T> Node<T> *Node<T>::getPrevious() const { return previous; }

template <typename T> void Node<T>::setPrevious(Node<T> *previous) {
  this->previous = previous;
}

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), size(0) {}

template <typename T> LinkedList<T>::~LinkedList() { empty(); }

template <typename T> void LinkedList<T>::addToFront(T data) {
  Node<T> *newNode = createNode(data);

  if (head == nullptr) {
    head = tail = newNode;
  } else {
    newNode->setNext(head);
    head->setPrevious(newNode);
    head = newNode;
  }

  size++;
}

template <typename T> void LinkedList<T>::addToEnd(T data) {
  Node<T> *newNode = createNode(data);

  if (tail == nullptr) {
    head = tail = newNode;
  } else {
    tail->setNext(newNode);
    newNode->setPrevious(tail);
    tail = newNode;
  }

  size++;
}

template <typename T> void LinkedList<T>::addAtIndex(T data, int index) {
  validateIndex(index);

  if (index == 0) {
    addToFront(data);
  } else if (index == size) {
    addToEnd(data);
  } else {
    Node<T> *newNode = createNode(data);
    Node<T> *currentNode = head;

    for (int i = 0; i < index - 1; i++) {
      currentNode = currentNode->getNext();
    }

    newNode->setNext(currentNode->getNext());
    newNode->setPrevious(currentNode);
    currentNode->getNext()->setPrevious(newNode);
    currentNode->setNext(newNode);

    size++;
  }
}

template <typename T> void LinkedList<T>::addBefore(Node<T> *node, T data) {
  if (node == nullptr) {
    return;
  }

  if (node == head) {
    addToFront(data);
  } else {
    Node<T> *newNode = createNode(data);
    Node<T> *prevNode = node->getPrevious();

    prevNode->setNext(newNode);
    newNode->setPrevious(prevNode);
    newNode->setNext(node);
    node->setPrevious(newNode);

    size++;
  }
}

template <typename T> void LinkedList<T>::addAfter(Node<T> *node, T data) {
  if (node == nullptr) {
    return;
  }

  if (node == tail) {
    addToEnd(data);
  } else {
    Node<T> *newNode = createNode(data);
    Node<T> *nextNode = node->getNext();

    node->setNext(newNode);
    newNode->setPrevious(node);
    newNode->setNext(nextNode);
    nextNode->setPrevious(newNode);

    size++;
  }
}

template <typename T> T LinkedList<T>::removeFromFront() {
  if (head == nullptr) {
    throw std::out_of_range("The list is empty.");
  }

  Node<T> *nodeToRemove = head;
  T data = nodeToRemove->getData();

  head = head->getNext();
  if (head != nullptr) {
    head->setPrevious(nullptr);
  } else {
    tail = nullptr;
  }

  deleteNode(nodeToRemove);
  size--;

  return data;
}

template <typename T> T LinkedList<T>::removeFromEnd() {
  if (tail == nullptr) {
    throw std::out_of_range("The list is empty.");
  }

  Node<T> *nodeToRemove = tail;
  T data = nodeToRemove->getData();

  tail = tail->getPrevious();
  if (tail != nullptr) {
    tail->setNext(nullptr);
  } else {
    head = nullptr;
  }

  deleteNode(nodeToRemove);
  size--;

  return data;
}

template <typename T> void LinkedList<T>::removeTheFirst(T data) {
  Node<T> *currentNode = head;

  while (currentNode != nullptr) {
    if (currentNode->getData() == data) {
      Node<T> *nextNode = currentNode->getNext();
      Node<T> *prevNode = currentNode->getPrevious();

      if (prevNode != nullptr) {
        prevNode->setNext(nextNode);
      } else {
        head = nextNode;
      }

      if (nextNode != nullptr) {
        nextNode->setPrevious(prevNode);
      } else {
        tail = prevNode;
      }

      deleteNode(currentNode);
      size--;
      return;
    }

    currentNode = currentNode->getNext();
  }
}

template <typename T> void LinkedList<T>::removeAllOf(T data) {
  Node<T> *currentNode = head;

  while (currentNode != nullptr) {
    if (currentNode->getData() == data) {
      Node<T> *nextNode = currentNode->getNext();
      Node<T> *prevNode = currentNode->getPrevious();

      if (prevNode != nullptr) {
        prevNode->setNext(nextNode);
      } else {
        head = nextNode;
      }

      if (nextNode != nullptr) {
        nextNode->setPrevious(prevNode);
      } else {
        tail = prevNode;
      }

      Node<T> *nodeToDelete = currentNode;
      currentNode = nextNode;

      deleteNode(nodeToDelete);
      size--;
    } else {
      currentNode = currentNode->getNext();
    }
  }
}

template <typename T> T LinkedList<T>::removeBefore(Node<T> *node) {
  if (node == nullptr || node == head || node->getPrevious() == nullptr) {
    throw std::out_of_range("Cannot remove the node before the given node.");
  }

  Node<T> *nodeToRemove = node->getPrevious();
  T data = nodeToRemove->getData();

  Node<T> *prevNode = nodeToRemove->getPrevious();
  prevNode->setNext(node);
  node->setPrevious(prevNode);

  deleteNode(nodeToRemove);
  size--;

  return data;
}

template <typename T> T LinkedList<T>::removeAfter(Node<T> *node) {
  if (node == nullptr || node == tail || node->getNext() == nullptr) {
    throw std::out_of_range("Cannot remove the node after the given node.");
  }

  Node<T> *nodeToRemove = node->getNext();
  T data = nodeToRemove->getData();

  Node<T> *nextNode = nodeToRemove->getNext();
  node->setNext(nextNode);
  if (nextNode != nullptr) {
    nextNode->setPrevious(node);
  } else {
    tail = node;
  }

  deleteNode(nodeToRemove);
  size--;

  return data;
}

template <typename T> bool LinkedList<T>::elementExists(T data) const {
  Node<T> *currentNode = head;

  while (currentNode != nullptr) {
    if (currentNode->getData() == data) {
      return true;
    }
    currentNode = currentNode->getNext();
  }

  return false;
}

template <typename T> Node<T> *LinkedList<T>::find(T data) const {
  Node<T> *currentNode = head;

  while (currentNode != nullptr) {
    if (currentNode->getData() == data) {
      return currentNode;
    }
    currentNode = currentNode->getNext();
  }

  return nullptr;
}

template <typename T> int LinkedList<T>::indexOf(T data) const {
  Node<T> *currentNode = head;
  int index = 0;

  while (currentNode != nullptr) {
    if (currentNode->getData() == data) {
      return index;
    }
    currentNode = currentNode->getNext();
    index++;
  }

  return -1;
}

template <typename T> T LinkedList<T>::retrieveFront() const {
  if (head == nullptr) {
    throw std::out_of_range("The list is empty.");
  }

  return head->getData();
}

template <typename T> T LinkedList<T>::retrieveEnd() const {
  if (tail == nullptr) {
    throw std::out_of_range("The list is empty.");
  }

  return tail->getData();
}

template <typename T> T LinkedList<T>::retrieve(int index) const {
  validateIndex(index);

  Node<T> *currentNode = head;

  for (int i = 0; i < index; i++) {
    currentNode = currentNode->getNext();
  }

  return currentNode->getData();
}

template <typename T> void LinkedList<T>::printList() const {
  Node<T> *currentNode = head;

  while (currentNode != nullptr) {
    std::cout << "["<<currentNode->getData() << "]";
    currentNode = currentNode->getNext();
    if(currentNode != nullptr)
      std::cout<<"=";
  }

  std::cout << std::endl;
}

template <typename T> void LinkedList<T>::empty() {
  Node<T> *currentNode = head;

  while (currentNode != nullptr) {
    Node<T> *nextNode = currentNode->getNext();
    deleteNode(currentNode);
    currentNode = nextNode;
  }

  head = nullptr;
  tail = nullptr;
  size = 0;
}

template <typename T> int LinkedList<T>::length() const { return size; }

template <typename T> Node<T> *LinkedList<T>::createNode(T data) {
  return new Node<T>(data);
}

template <typename T> void LinkedList<T>::deleteNode(Node<T> *node) {
  delete node;
}

template <typename T> void LinkedList<T>::validateIndex(int index) const {
  if (index < 0 || index > size) {
    throw std::out_of_range("Invalid index.");
  }
}

// Explicit instantiations of the template classes
template class Node<int>;
template class LinkedList<int>;


#endif  // LINKEDLIST_HPP
