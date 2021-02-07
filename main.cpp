#include <iostream>
#include <algorithm>
#include <iterator>
#include <list>
#include "list.hpp"

int main()
{
  DoubleLinkedList<int> test;
  test.addNewElement(3);
  test.addNewElement(4);
  test.addNewElement(5);
  test.addNewElement(6);
  test.addNewElement(7);
  test.addNewElement(10);

  DoubleLinkedList<int> test2;
  test2.addNewElement(14);
  test2.addNewElement(15);
  test2.addNewElement(16);
  test2.addNewElement(17);
  test2.addNewElement(18);
  test2.addNewElement(19);

  std::cout << "Insert at the beggining - insert as tail\n";
  test.insert(test.begin(), 3954);
  test.printList();

  std::cout << "\nErase 7, since list is looped and there is no end iterator that points to the section "
               "after the last element\n";
  test.erase(----test.end()); 
  test.printList();

  std::cout << "\nSplice\n";
  test.splice(++++++test.begin(), test2.begin(), test2.end());
  test.printList();

  std::cout << "\nCompatibility with STL algs, again since end iterator cant be implemented"
               " as STL one last element is not printed\n";
  std::ostream_iterator<DoubleLinkedList<int>::Iterator::value_type> out(std::cout, " ");
  std::copy(test.begin(), test.end(), out);
  std::cout << "\n\n";
  std::reverse_copy(test.begin(), test.end(), out);
}