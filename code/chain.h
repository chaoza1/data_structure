#include "chainNode.h"
#include "linearList.h"
#include "myExceptions.h"
#include<iostream>
#include<sstream>
#include<string>
template <class T>
class chain : public linearList<T>
{
private:
  /* data */
public:
  chain(int initialCapacity = 10);
  chain(const chain<T> &);
  ~chain();

  bool empty() const { return listSize == 0; }
  int size() const { return listSize; }
  T &get(int theIndex) const;
  int indexOf(const T &theElement) const;
  void erase(int theIndex);
  void insert(int theIndex, const T &theElement);
  void output(ostream &out) const;

protected:
  void checkIndex(int theIndex) const;
  chainNode<T> *firstNode;
  int listSize;
};

template <class T>
chain<T>::chain(int initialCapacity)
{
  if (initialCapacity < 1)
  {
    
    ostringstream s;
    s << "Initial capacity = " << initialCapacity << " Must be > 0;";
    throw illegalParameterValue(s.str());
  }
  firstNode = NULL;
  listSize = 0;
}

template <class T>
chain<T>::chain(const chain<T> &theList)
{
  listSize = theList.listSize;
  if (listSize == 0)
  {
    firstNode = NULL;
    return;
  }

  //链表非空
  chainNode<T> *soureceNode = theList.firstNode;      //要复制的链表
  firstNode = new chainNode<T>(soureceNode->element); //首元素
  soureceNode = soureceNode->next;                    //下一个节点
  chainNode<T> *targetNode = firstNode;                   //新链表的最后一个节点
  while (soureceNode != NULL)
  {
    /* code */
    targetNode->next = new chainNode<T>(soureceNode->element);
    targetNode = targetNode->next;
    soureceNode = soureceNode->next;
  }
  targetNode->next = NULL;
}

template <class T>
chain<T>::~chain()
{
  while (firstNode != NULL)
  {
    /* code */
    chainNode<T> *nextNode = firstNode->next;
    delete firstNode;
    firstNode = nextNode;
  }
}

template <class T>
void chain<T>::checkIndex(int theIndex) const
{
  if (theIndex < 0 || theIndex >= listSize)
  {
    ostringstream s;
    s << "Index=" << theIndex << "size = " << listSize;
    throw illegalIndex(s.str());
  }
}

template <class T>
T &chain<T>::get(int theIndex) const
{
  checkIndex(theIndex);
  chainNode<T>* currentNode = firstNode;
  for (int i = 0; i < theIndex; i++)
  {
    currentNode = currentNode->next;
  }
  return currentNode->element;
}

template <class T>
int chain<T>::indexOf(const T &theElement) const
{
  chainNode<T> *currentNode = firstNode;
  int index = 0;
  while (currentNode != NULL && currentNode->element != theElement)
  {
    /* code */
    currentNode = currentNode->next;
    index++;
  }
  if (currentNode == NULL)
    return -1;
  else
    return index;
}

template <class T>
void chain<T>::erase(int theIndex)
{
  checkIndex(theIndex);

  chainNode<T>* deleteNode;
  if (theIndex == 0)
  {
    deleteNode = firstNode;
    firstNode = firstNode->next;
  }
  else
  {
    chainNode<T>* p = firstNode;
    for (int i = 0; i < theIndex - 1; i++)
    {
      p = p->next;
    }
    deleteNode = p->next;
    p->next = p->next->next;
  }
  listSize--;
  delete deleteNode;
}

template <class T>
void chain<T>::insert(int theIndex, const T &theElement)
{
  if (theIndex < 0 || theIndex > listSize)

  { // invalid index

    ostringstream s;

    s << "index = " << theIndex << " size = " << listSize;

    throw illegalIndex(s.str());
  }
  if (theIndex == 0)
    firstNode = new chainNode<T>(theElement, firstNode);
  else
  {
    chainNode<T> *p = firstNode;
    for (int i = 0; i < theIndex - 1; i++)
    {
      p = p->next;
    }
    cout<<p->element<<" and "<<"  "<<theIndex<<endl;
    p->next = new chainNode<T>(theElement, p -> next);
  }
  listSize++;
}

template <class T>
void chain<T>::output(ostream &out) const
{
  for (chainNode<T> *currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next)
  {
    out << currentNode->element << " ";
  }
}

// overload <<

template <class T>

ostream& operator<<(ostream& out, const chain<T>& x)

   {x.output(out); return out;}



