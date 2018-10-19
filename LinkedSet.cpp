//Â  Created by Frank M. Carrano and Timothy M. Henry.
//Â  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
//  Modified by Tiziana Ligorio 2018

/** ADT set: Link-based implementation.
    @file LinkedSet.cpp */

#include "LinkedSet.h"
#include "Node.h"
//#include <cstddef>
#include <vector>

template<class ItemType>
LinkedSet<ItemType>::LinkedSet() : head_ptr_(nullptr), item_count_(0)
{
}  // end default constructor

template<class ItemType>
LinkedSet<ItemType>::LinkedSet(const LinkedSet<ItemType>& a_set)
{
	item_count_ = a_set.item_count_;
   Node<ItemType>* orig_chain_ptr = a_set.head_ptr_;  // Points to nodes in original chain
   
   if (orig_chain_ptr == nullptr)
      head_ptr_ = nullptr;  // Orciginal Set is empty
   else
   {
      // Copy first node
      head_ptr_ = new Node<ItemType>();
      head_ptr_->setItem(orig_chain_ptr->getItem());
      
      // Copy remaining nodes
      Node<ItemType>* new_chain_ptr = head_ptr_;      // Points to last node in new chain
      orig_chain_ptr = orig_chain_ptr->getNext();     // Advance original-chain pointer
      
      while (orig_chain_ptr != nullptr)
      {
         // Get next item from original chain
         ItemType nextItem = orig_chain_ptr->getItem();
              
         // Create a new node containing the next item
         Node<ItemType>* new_node_ptr = new Node<ItemType>(nextItem);
         
         // Link new node to end of new chain
         new_chain_ptr->setNext(new_node_ptr);
         
         // Advance pointer to new last node
         new_chain_ptr = new_chain_ptr->getNext();

         // Advance original-chain pointer
         orig_chain_ptr = orig_chain_ptr->getNext();
      }  // end while
      
      new_chain_ptr->setNext(nullptr);  // Flag end of chain
   }  // end if
}  // end copy constructor

template<class ItemType>
LinkedSet<ItemType>::~LinkedSet()
{
   clear();
}  // end destructor

template<class ItemType>
bool LinkedSet<ItemType>::isEmpty() const
{
	return item_count_ == 0;
}  // end isEmpty

template<class ItemType>
int LinkedSet<ItemType>::getCurrentSize() const
{
	return item_count_;
}  // end getCurrentSize

template<class ItemType>
bool LinkedSet<ItemType>::add(const ItemType& new_entry)
{
    if(!contains(new_entry))
    {
       // Add to beginning of chain: new node references rest of chain;
       // (head_ptr_ is null if chain is empty)
       Node<ItemType>* next_node_ptr = new Node<ItemType>();
       next_node_ptr->setItem(new_entry);
       next_node_ptr->setNext(head_ptr_);  // New node points to chain

       head_ptr_ = next_node_ptr;          // New node is now first node
       item_count_++;
    
       return true;
    }else
        return false;
}  // end add

template<class ItemType>
std::vector<ItemType> LinkedSet<ItemType>::toVector() const
{
   std::vector<ItemType> set_contents;
   Node<ItemType>* cur_ptr = head_ptr_;
   int counter = 0;
	while ((cur_ptr != nullptr) && (counter < item_count_))
   {
		set_contents.push_back(cur_ptr->getItem());
      cur_ptr = cur_ptr->getNext();
      counter++;
   }  // end while
   
   return set_contents;
}  // end toVector

template<class ItemType>
bool LinkedSet<ItemType>::remove(const ItemType& an_entry)
{
   Node<ItemType>* entry_node_ptr = getPointerTo(an_entry);
   bool can_remove_item = !isEmpty() && (entry_node_ptr != nullptr);
   if (can_remove_item)
   {
      // Copy data from first node to located node
      entry_node_ptr->setItem(head_ptr_->getItem());
      
      // Delete first node
      Node<ItemType>* node_to_delete_ptr = head_ptr_;
      head_ptr_ = head_ptr_->getNext();
      
      // Return node to the system
      node_to_delete_ptr->setNext(nullptr);
      delete node_to_delete_ptr;
      node_to_delete_ptr = nullptr;
      
      item_count_--;
   } // end if
   
	return can_remove_item;
}  // end remove

template<class ItemType>
void LinkedSet<ItemType>::clear()
{
   Node<ItemType>* node_to_delete_ptr = head_ptr_;
   while (head_ptr_ != nullptr)
   {
      head_ptr_ = head_ptr_->getNext();

      // Return node to the system
      node_to_delete_ptr->setNext(nullptr);
      delete node_to_delete_ptr;
      
      node_to_delete_ptr = head_ptr_;
   }  // end while
   // head_ptr_ is nullptr; nodeToDeletePtr is nullptr
   
	item_count_ = 0;
}  // end clear



template<class ItemType>
bool LinkedSet<ItemType>::contains(const ItemType& anEntry) const
{
	return (getPointerTo(anEntry) != nullptr);
}  // end contains



// private
// Returns either a pointer to the node containing a given entry 
// or the null pointer if the entry is not in the set.
template<class ItemType>
Node<ItemType>* LinkedSet<ItemType>::getPointerTo(const ItemType& an_entry) const
{
   bool found = false;
   Node<ItemType>* cur_ptr = head_ptr_;
   
   while (!found && (cur_ptr != nullptr))
   {
      if (an_entry == cur_ptr->getItem())
         found = true;
      else
         cur_ptr = cur_ptr->getNext();
   } // end while
   
   return cur_ptr;
} // end getPointerTo