#pragma once
#include <Wire.h>

typedef uint8_t byte;
template<typename T>
class ListNode
{
  public:
    ListNode(T* el, ListNode* p) : element(el),prev(p){};
    ~ListNode(){delete element;}
  public:
    T* element;
    ListNode* prev;
};

template<typename T>
class LinkedList
{
  public:
    LinkedList(): m_nSize(0), head(nullptr), tail(nullptr){}
    ~LinkedList();
  public:
    void push(T* element);
    int size();
    int find(T* element);
    T* operator[](size_t index);
  private:
    ListNode<T>* head;
    ListNode<T>* tail;
    int m_nSize;
};

template<typename T>
LinkedList<T>::~LinkedList()
{
  ListNode<T> * tmp = tail;
  for(int i=0;i<m_nSize;++i)
  {
    tmp = tail->prev;
    delete tail;
    if(i<m_nSize-1)tail = tmp;
  }

}

template<typename T>
int LinkedList<T>::size()
{
  return m_nSize;
}

template<typename T>
void LinkedList<T>::push(T* element)
{
  tail = new ListNode<T>(element, tail);
  m_nSize++;
}

template<typename T>
T* LinkedList<T>::operator[](size_t index)
{
  ListNode<T>* tmp=tail;
  for(int i=0;i<index;++i)
  {
    tmp = tmp->prev;
  }
  return tmp->element;
}

template<typename T>
int LinkedList<T>::find(T* element)
{
  ListNode<T>* tmp=tail;
  for(int i=0;i<m_nSize;++i)
  {
    if(*(tmp->element)==*element) return i;
    tmp = tmp->prev;
  }
  return -1;


}
template<typename T>
String ToHexT(T val)
{
  union
  {
    T input;
    long long output;
  } data;

  data.output =0;
  data.input = val;
  String ret;
  char buff[5];
  uint8_t foo;
  //std::cout<<data.output<<std::endl;
  for(int i=0,e=sizeof(data.input);i<e;++i)
  {
    uint8_t x = (uint8_t)((data.output>>((e-1-i)*8)));
    //std::cout<<(int)x<<std::endl;
    if(x<16) ret+='0';
    memset(buff,'\0',5);
    itoa(x,buff,16);
    ret+=buff;
  }
  return ret;
}

template<typename T>
String ToHexTU(T val)
{
  union
  {
    T input;
    unsigned long long output;
  } data;

  data.output =0;
  data.input = val;
  String ret;
  char buff[5];
  uint8_t foo;
  //std::cout<<data.output<<std::endl;
  for(int i=0,e=sizeof(data.input);i<e;++i)
  {
    uint8_t x = (uint8_t)((data.output>>((e-1-i)*8)));
    //std::cout<<(int)x<<std::endl;
    if(x<16) ret+='0';
    memset(buff,'\0',5);
    itoa(x,buff,16);
    ret+=buff;
  }
  return ret;
}

String ToHex(String x);
String ToHex(int x);
String ToHex(long x);
String ToHex(float x);
String ToHex(double x);
String ToHex(long long x);
String ToHex(int8_t x);

String ToHex(unsigned int x);
String ToHex(unsigned long x);
String ToHex(unsigned long long x);
String ToHex(uint8_t x);


/******************************************************************************
   PMIC constants
 ******************************************************************************/

#if defined ARDUINO_SAMD_MKRWIFI1010 || defined ARDUINO_SAMD_MKRGSM1400 || defined ARDUINO_SAMD_MKRNB1500
#define PMIC_ADDRESS 0x6B
#else
#define PMIC_ADDRESS 0x60
#endif
#define SYSTEM_STATUS_REGISTER 0x08
#define PMIC_VERSION_REGISTER 0x0A

byte readRegister(byte address);
void batteryBegin();