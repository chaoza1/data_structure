#ifndef linearList_
#define linearList_
#include <iostream>
using namespace std;

template <class T>

class linearList
{
  private:
    /* data */
  public:
    virtual ~linearList() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T &get(int theIndex) const = 0;
    virtual int indexOf(const T &theElement) const = 0; //return the element first chuxian index
    virtual void erase(int theIndex) = 0;
    virtual void insert(int theIndex, const T &theElement) = 0;
    virtual void output(ostream &out) const = 0;
};

#endif