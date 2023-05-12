/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:51:57 by ulee              #+#    #+#             */
/*   Updated: 2022/04/11 20:04:27 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <deque>
#include <iostream>
#include <string>

#if USE_STL // CREATE A REAL STL EXAMPLE
#include <map>
#include <stack>
#include <vector>
namespace ft = std;
#else
#include <../includes/map.hpp>
#include <../includes/stack.hpp>
#include <../includes/vector.hpp>
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer {
  int idx;
  char buff[BUFFER_SIZE];
};

#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template <typename T> class MutantStack : public ft::stack<T> {
public:
  MutantStack() {}

  MutantStack(const MutantStack<T> &src) { *this = src; }

  MutantStack<T> &operator=(const MutantStack<T> &rhs) {
    this->c = rhs.c;
    return *this;
  }

  ~MutantStack() {}

  typedef typename ft::stack<T>::container_type::iterator iterator;

  iterator begin() { return this->c.begin(); }

  iterator end() { return this->c.end(); }
};

int main() {
  const int seed = 0;
  srand(seed);
  ft::vector<std::string> vector_str;
  ft::vector<int> vector_int;
  ft::stack<int> stack_int;
  ft::vector<Buffer> vector_buffer;
  ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
  ft::map<int, int> map_int;

  for (int i = 0; i < COUNT; i++) {
    vector_buffer.push_back(Buffer());
  }

  for (int i = 0; i < COUNT; i++) {
    const int idx = rand() % COUNT;
    vector_buffer[idx].idx = 5;
  }
  ft::vector<Buffer>().swap(vector_buffer);

  try {
    for (int i = 0; i < COUNT; i++) {
      const int idx = rand() % COUNT;
      vector_buffer.at(idx);
      std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" << std::endl;
    }
  } catch (const std::exception &e) {
    // NORMAL ! :P
    std::cout << e.what() << std::endl;
  }

  for (int i = 0; i < COUNT; ++i) {
    map_int.insert(ft::make_pair(rand(), rand()));
  }

  int sum = 0;
  for (int i = 0; i < 10000; i++) {
    int access = rand();
    sum += map_int[access];
  }

  { ft::map<int, int> copy = map_int; }
  MutantStack<char> iterable_stack;
  for (char letter = 'a'; letter <= 'z'; letter++)
    iterable_stack.push(letter);
  for (MutantStack<char>::iterator it = iterable_stack.begin();
       it != iterable_stack.end(); it++) {
    std::cout << *it;
  }
  std::cout << std::endl;

  return (0);
}