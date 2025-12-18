#pragma once
#include <iostream>
#include <fstream>
#include <cstddef>

using namespace std;

template <typename T>
struct TListNode
{
  T data;
  TListNode<T> *next;
  TListNode<T> *prev;

  TListNode(const T &value);
};

template <typename T>
inline TListNode<T>::TListNode(const T &value) : data(value), next(nullptr), prev(nullptr) {}

template <class T>
class TList
{
private:
  TListNode<T>* head;
  TListNode<T>* tail;
  size_t size;

public:
  TList();
  TList(const TList& other);
  TList(TList&& other);
  ~TList();

  size_t GetSize() const;
  TListNode<T>* GetHead() const;
  TListNode<T>* GetTail() const;

  void PushFront(const T& value);
  void PushBack(const T& value);
  T PopFront();
  T PopBack();

  void InsertAfter(TListNode<T>* node, const T& value);
  void InsertBefore(TListNode<T>* node, const T& value);

  void Remove(TListNode<T>* node);
  void Clear();

  bool IsEmpty() const;
  bool IsFull() const;

  TList& operator=(const TList& other);
  TList& operator=(TList&& other);
  bool operator==(const TList& other) const;
  bool operator!=(const TList& other) const;

  T& operator[](size_t index);
  const T& operator[](size_t index) const;

  TList operator+(const TList& other) const;

  TListNode<T>* begin();
  TListNode<T>* end();
  const TListNode<T>* begin() const;
  const TListNode<T>* end() const;

  size_t CountOccurrences(const T& value) const;
  TList<TListNode<T>*> FindOccurrences(const T& value) const;

  template<class I>
  friend ostream& operator<<(ostream& os, const TList<T>& list);

  template<class O>
  friend istream& operator>>(istream& is, TList<T>& list);
};


template <class T>
inline TList<T>::TList() : head(nullptr), tail(nullptr), size(0) {}

template <class T>
inline TList<T>::TList(const TList& other) : head(nullptr), tail(nullptr), size(0)
{
  TListNode<T>* current = other.head;
  while (current != nullptr)
  {
    PushBack(current->data);
    current = current->next;
  }
}

template <class T>
inline TList<T>::TList(TList&& other) : head(other.head), tail(other.tail), size(other.size)
{
  other.head = nullptr;
  other.tail = nullptr;
  other.size = 0;
}

template <class T>
inline TList<T>::~TList()
{
  Clear();
}

template <class T>
inline size_t TList<T>::GetSize() const
{
  return size;
}

template <class T>
inline TListNode<T>* TList<T>::GetHead() const
{
  return head;
}

template <class T>
inline TListNode<T>* TList<T>::GetTail() const
{
  return tail;
}

template <class T>
inline void TList<T>::PushFront(const T& value)
{
  TListNode<T>* newNode = new TListNode<T>(value);

  if (IsEmpty())
  {
    head = newNode;
    tail = newNode;
  }
  else
  {
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
  }
  size++;
}

template <class T>
inline void TList<T>::PushBack(const T& value)
{
  TListNode<T>* newNode = new TListNode<T>(value);

  if (IsEmpty())
  {
    head = tail = newNode;
  }
  else
  {
    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;
  }
  size++;
}

template <class T>
inline T TList<T>::PopFront()
{
  if (IsEmpty())
    throw "List is empty";

  TListNode<T>* popNode = head;
  T value = popNode->data;

  if (head == tail)
  {
    head = tail = nullptr;
  }
  else
  {
    head = head->next;
    head->prev = nullptr;
  }

  delete popNode;
  size--;
  return value;
}

template <class T>
inline T TList<T>::PopBack()
{
  if (IsEmpty())
    throw "List is empty";

  TListNode<T>* popNode = tail;
  T value = popNode->data;

  if (head == tail)
  {
    head = tail = nullptr;
  }
  else
  {
    tail = tail->prev;
    tail->next = nullptr;
  }

  delete popNode;
  size--;
  return value;
}

template <class T>
inline void TList<T>::InsertAfter(TListNode<T>* node, const T& value)
{
  if (node == nullptr)
    throw "Node error";

  if (node == tail)
  {
    PushBack(value);
  }
  else
  {
    TListNode<T>* newNode = new TListNode<T>(value);
    newNode->prev = node;
    newNode->next = node->next;
    node->next->prev = newNode;
    node->next = newNode;
    size++;
  }
}

template <class T>
inline void TList<T>::InsertBefore(TListNode<T>* node, const T& value)
{
  if (node == nullptr)
    throw "Node error";

  if (node == head)
  {
    PushFront(value);
  }
  else
  {
    TListNode<T>* newNode = new TListNode<T>(value);
    newNode->next = node;
    newNode->prev = node->prev;
    node->prev->next = newNode;
    node->prev = newNode;
    size++;
  }
}

template <class T>
inline void TList<T>::Remove(TListNode<T>* node)
{
  if (node == nullptr)
    throw "Node error";

  if (node == head)
  {
    PopFront();
  }
  else if (node == tail)
  {
    PopBack();
  }
  else
  {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    size--;
  }
}

template <class T>
inline void TList<T>::Clear()
{
  while (!IsEmpty())
  {
    PopFront();
  }
}

template <class T>
inline bool TList<T>::IsEmpty() const
{
  return size == 0;
}

template <class T>
inline bool TList<T>::IsFull() const
{
  return false;
}

template <class T>
inline TList<T>& TList<T>::operator=(const TList& other)
{
  if (this != &other)
  {
    Clear();

    TListNode<T>* current = other.head;
    while (current != nullptr)
    {
      PushBack(current->data);
      current = current->next;
    }
  }
  return *this;
}

template <class T>
inline TList<T>& TList<T>::operator=(TList&& other)
{
  if (this != &other)
  {
    Clear();

    head = other.head;
    tail = other.tail;
    size = other.size;

    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
  }
  return *this;
}

template <class T>
inline bool TList<T>::operator==(const TList& other) const
{
  if (size != other.size)
    return false;

  TListNode<T>* current1 = head;
  TListNode<T>* current2 = other.head;

  while (current1 != nullptr)
  {
    if (current1->data != current2->data)
      return false;
    current1 = current1->next;
    current2 = current2->next;
  }
  return true;
}

template <class T>
inline bool TList<T>::operator!=(const TList& other) const
{
  return !(*this == other);
}

template <class T>
inline T& TList<T>::operator[](size_t index)
{
  if (index >= size)
    throw "Index out of range";

  TListNode<T>* current = head;
  for (size_t i = 0; i < index; i++)
  {
    current = current->next;
  }
  return current->data;
}

template <class T>
inline const T& TList<T>::operator[](size_t index) const
{
  if (index >= size)
    throw "Index out of range";

  TListNode<T>* current = head;
  for (size_t i = 0; i < index; i++)
  {
    current = current->next;
  }
  return current->data;
}

template <class T>
inline TList<T> TList<T>::operator+(const TList& other) const
{
  TList<T> result(*this);

  TListNode<T>* current = other.head;
  while (current != nullptr)
  {
    result.PushBack(current->data);
    current = current->next;
  }

  return result;
}

template <class T>
inline TListNode<T>* TList<T>::begin()
{
  return head;
}

template <class T>
inline TListNode<T>* TList<T>::end()
{
  return nullptr;
}

template <class T>
inline const TListNode<T>* TList<T>::begin() const
{
  return head;
}

template <class T>
inline const TListNode<T>* TList<T>::end() const
{
  return nullptr;
}

template <class T>
inline size_t TList<T>::CountOccurrences(const T& value) const
{
  size_t count = 0;
  TListNode<T>* current = head;

  while (current != nullptr)
  {
    if (current->data == value)
      count++;
    current = current->next;
  }
  return count;
}

template <class T>
inline TList<TListNode<T>*> TList<T>::FindOccurrences(const T& value) const
{
  TList<TListNode<T>*> result;
  TListNode<T>* current = head;

  while (current != nullptr)
  {
    if (current->data == value)
    {
      result.PushBack(current);
    }
    current = current->next;
  }
  return result;
}

template <class T>
ostream& operator<<(ostream& os, const TList<T>& list)
{
  os << "[";
  TListNode<T>* current = list.GetHead();
  while (current != nullptr)
  {
    os << current->data;
    if (current->next != nullptr)
      os << ", ";
    current = current->next;
  }
  os << "]";
  return os;
}

template <class T>
istream& operator>>(istream& is, TList<T>& list)
{
  list.Clear();

  size_t count;
  is >> count;

  for (size_t i = 0; i < count; ++i)
  {
    T value;
    is >> value;
    list.PushBack(value);
  }

  return is;
}