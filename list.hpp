#ifndef LIST_HPP
#define LIST_HPP

#include <initializer_list>
#include <iostream>
#include <iterator>

template<typename T>
class DoubleLinkedList
{
public:

  struct Node
  {
  public:
    Node* next_;
    Node* previous_;
    T item_;

    Node(const T& item, Node* next = nullptr, Node* previous = nullptr):
            item_(item),
            next_(next),
            previous_(previous)
    {}
  };

  class Iterator: public std::iterator<std::bidirectional_iterator_tag, T>
  {
  public:
    friend class DoubleLinkedList<T>;

    Iterator();
    Iterator(Node* item);

    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);

    T operator*() const;
    T* operator->() const;

    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;

  private:
    Node* node_pointer;
    Node* get_node_pointer()
    {
      return node_pointer;
    }


  };

  using Const_iterator = const Iterator;

  DoubleLinkedList();
  DoubleLinkedList(const std::initializer_list<T> arguments);
  DoubleLinkedList(const DoubleLinkedList<T>& copy);
  DoubleLinkedList(DoubleLinkedList<T>&& move) noexcept;
  DoubleLinkedList<T>& operator=(const DoubleLinkedList<T>& copy);
  DoubleLinkedList<T>& operator=(DoubleLinkedList<T>&& move) noexcept;

  void addNewElement(const T& element);

  Iterator begin();
  Iterator end();

  Const_iterator cbegin() const;
  Const_iterator cend() const;


  Iterator insert(Iterator pos, const T& element);
  Iterator erase(Iterator pos);
  Iterator erase(Iterator begin, Iterator end);
  void splice(Iterator pos, Iterator begin, Iterator end);

  ~DoubleLinkedList();

  void printList();

private:
  Node* head_;
  Node* tail_;

  void copy_elements(Node* begin, Node* end, Node*& result_begin, Node*& result_end);
  void deleteElemets();

};


template<typename T>
DoubleLinkedList<T>::DoubleLinkedList():
        head_(nullptr),
        tail_(nullptr)
{}

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(const std::initializer_list<T> arguments):
        head_(nullptr),
        tail_(nullptr)
{
  std::for_each(arguments.begin(), arguments.end(), [this](const T& argument)
  {
    addNewElement(argument);
  });
}

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList<T>& copy)
{
  if (copy.head_ == nullptr)
  {
    return;
  }
  else if (copy.tail_ ==  nullptr)
  {
    head_ = new Node(copy.head_->item_);
  }
  else
  {
    head_ = nullptr;
    tail_ = nullptr;
    Node* current = copy.head_->next_;
    addNewElement(copy.head_->item_);
    while (current != copy.tail_)
    {
      addNewElement(current->item_);
      current = current->next_;
    }
  }
}

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList<T>&& move) noexcept
{
  head_ = move.head_;
  tail_ = move.tail_;

  move.head_ = move.tail_ = nullptr;
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(const DoubleLinkedList<T>& copy)
{
  if (this == &copy)
  {
    return *this;
  }

  deleteElemets();
  Node* new_head = nullptr;
  Node* new_tail = nullptr;
  copy_elements(copy.head_, copy.tail_, new_head, new_tail);
  new_tail->next_ = new_head;
  new_head->previous_ = new_tail;
  head_ = new_head;
  tail_ = new_tail;

  return *this;
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(DoubleLinkedList<T>&& move) noexcept
{
  head_ = move.head_;
  tail_ = move.tail_;

  move.head_ = move.tail_ = nullptr;
}

template<typename T>
void DoubleLinkedList<T>::addNewElement(const T& element)
{
  Node* new_element = new Node(element);
  if (head_ == nullptr)
  {
    head_ = new_element;
  }
  else if (tail_ == nullptr)
  {
    tail_ = new_element;
    tail_->previous_ = head_;
    head_->next_ = tail_;
    head_->previous_ = tail_;
    tail_->next_ = head_;
  }
  else
  {
    Node* tmp = tail_;
    tail_ = new_element;
    tail_->previous_ = tmp;
    tail_->next_ = head_;
    head_->previous_ = tail_;
    tmp->next_ = tail_;
  }
}

template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
  deleteElemets();
}

template<typename T>
void DoubleLinkedList<T>::printList()
{
  Node* current = head_;

  do
  {
    std::cout << current->item_ << " ";
    current = current->next_;
  } while(current != head_);

  std::cout << "\n";
}

template<typename T>
DoubleLinkedList<T>::Iterator::Iterator():
        node_pointer(nullptr)
{}

template<typename T>
DoubleLinkedList<T>::Iterator::Iterator(Node* item):
        node_pointer(item)
{}

template<typename T>
typename DoubleLinkedList<T>::Iterator& DoubleLinkedList<T>::Iterator::operator++()
{
  node_pointer = node_pointer->next_;
  return *this;
}

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::Iterator::operator++(int)
{
  Iterator tmp = *this;
  ++*this;
  return tmp;
}

template<typename T>
typename DoubleLinkedList<T>::Iterator& DoubleLinkedList<T>::Iterator::operator--()
{
  node_pointer = node_pointer->previous_;
  return *this;
}

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::Iterator::operator--(int)
{
  Iterator tmp = *this;
  --*this;

  return tmp;
}

template<typename T>
T DoubleLinkedList<T>::Iterator::operator*() const
{
  return node_pointer->item_;
}

template<typename T>
T* DoubleLinkedList<T>::Iterator::operator->() const
{
  return &(node_pointer->item_);
}

template<typename T>
bool DoubleLinkedList<T>::Iterator::operator==(const Iterator& other) const
{
  return node_pointer->item_ == other.node_pointer->item_;
}

template<typename T>
bool DoubleLinkedList<T>::Iterator::operator!=(const Iterator& other) const
{
  return node_pointer->item_ != other.node_pointer->item_;
}

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::begin()
{
  return Iterator(head_);
}

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::end()
{
  return Iterator(tail_);
}

template<typename T>
typename DoubleLinkedList<T>::Const_iterator DoubleLinkedList<T>::cbegin() const
{
  return begin();
}

template<typename T>
typename DoubleLinkedList<T>::Const_iterator DoubleLinkedList<T>::cend() const
{
  return end();
}

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::insert(Iterator pos, const T& element)
{
  auto pos_node = pos.get_node_pointer();
  Node* new_node = new Node(element);

  bool replace_tail = false;
  if (pos_node == head_)
  {
    replace_tail = true;
  }

  new_node->previous_ = pos_node->previous_;
  new_node->next_ = pos_node;
  pos_node->previous_->next_ = new_node;
  pos_node->previous_ = new_node;

  if (replace_tail)
  {
    tail_ = new_node;
  }
  return Iterator(new_node);
}

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::erase(Iterator pos)
{
  auto return_iterator = std::next(pos);
  auto pos_node = pos.get_node_pointer();

  pos_node->previous_->next_ = pos_node->next_;
  pos_node->next_->previous_ = pos_node->previous_;

  if (pos_node == head_)
  {
    head_ = pos_node->next_;
  }
  else if (pos_node == tail_)
  {
    tail_ = pos_node->previous_;
  }

  delete pos_node;
  return return_iterator;
}


template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::erase(Iterator begin, Iterator end)
{
  auto node_begin = begin.get_node_pointer();
  auto node_end = end.get_node_pointer();

  Node* current = node_begin->next_;
  Node* tmp = nullptr;

  node_begin->next_ = node_end;
  node_end->previous_ = node_begin;

  while (current != node_end)
  {
    tmp = current->next_;
    delete current;
    current = tmp;
  }
  return end;
}

template<typename T>
void DoubleLinkedList<T>::splice(Iterator pos, Iterator begin, Iterator end)
{
  auto pos_node = pos.get_node_pointer();
  Node* node_begin = nullptr;
  Node* node_end = nullptr;
  copy_elements(begin.get_node_pointer(), end.get_node_pointer(), node_begin, node_end);


  bool replace_tail = false;
  if (pos_node == tail_)
  {
    replace_tail = true;
  }

  Node* tmp = pos_node->previous_;
  tmp->next_ = node_begin;
  node_begin->previous_ = tmp;

  pos_node->previous_ = node_end;
  node_end->next_ = pos_node;

  if (replace_tail)
  {
    tail_ = node_end;
  }

}

template<typename T>
void DoubleLinkedList<T>::copy_elements(Node* begin, Node* end, Node*& result_begin, Node*& result_end)
{
  result_begin = new Node(begin->item_);


  Node* previous = result_begin;
  Node* current = begin->next_;


  while(current != end->next_)
  {
    Node* new_node = new Node(current->item_);
    previous->next_ = new_node;
    new_node->previous_ = previous;
    previous = new_node;
    current = current->next_;
  }
  result_end = previous;
}

template<typename T>
void DoubleLinkedList<T>::deleteElemets()
{
  if (head_ == nullptr)
  {
    return;
  }
  else if (tail_ == nullptr)
  {
    delete head_;
  }
  else
  {
    Node* current = head_->next_;
    Node* tmp = nullptr;

    while(current != head_)
    {
      tmp = current->next_;
      delete current;
      current = tmp;
    }

    delete current;
  }
}

#endif
