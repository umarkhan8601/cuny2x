#include "Node.h"
//#include <cstddef>

template<class ItemType>
Node<ItemType>::Node() :next_(nullptr)
{
} // end default constructor

template<class ItemType>
Node<ItemType>::Node(const ItemType& an_item) : item_(an_item), next_(nullptr)
{
} // end constructor

template<class ItemType>
Node<ItemType>::Node(const ItemType& an_item, Node<ItemType>* next_node_ptr) :
                item_(an_item), next_(next_node_ptr)
{
} // end constructor

template<class ItemType>
void Node<ItemType>::setItem(const ItemType& an_item)
{
   item_ = an_item;
} // end setItem

template<class ItemType>
void Node<ItemType>::setNext(Node<ItemType>* next_node_ptr)
{
   next_ = next_node_ptr;
} // end setNext

template<class ItemType>
ItemType Node<ItemType>::getItem() const
{
   return item_;
} // end getItem

template<class ItemType>
Node<ItemType>* Node<ItemType>::getNext() const
{
   return next_;
} // end getNext