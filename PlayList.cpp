#include "PlayList.h"

#include <iostream>
using namespace std;

PlayList::PlayList(): tail_ptr_(nullptr) {}

PlayList::PlayList(const Song& a_song){
	add(a_song);
}




PlayList::PlayList(const PlayList& a_play_list) : LinkedSet<Song>(a_play_list)
{//at least one node if this is true
			tail_ptr_ = getPointerToLastNode();
	
}






//LinkedSet<ItemType>::clear() = new PLaylist::clear();

bool PlayList::remove(const Song& a_song) {
	Node<Song> * previous_ptr = nullptr;
	Node<Song> * node_to_delete_ptr = getPointerTo(a_song, previous_ptr);


 //    // node not present , simply return false
	if (node_to_delete_ptr == NULL){
	    return false;
	}
	else{
		// if a_song is the first node....previous is null
		if(previous_ptr == NULL){
			// make headptr point to the next item
			head_ptr_ = node_to_delete_ptr->getNext();
			//make noddetodel point to nullptr
			node_to_delete_ptr ->setNext(nullptr);
			//delete asong
			delete node_to_delete_ptr;
			//node to delptr = nullptr
			node_to_delete_ptr = nullptr;
			item_count_--;
			return true;
		}
		else{
			
			if(node_to_delete_ptr->getNext() == NULL){
				tail_ptr_=previous_ptr;
				//previous_ptr->setNext(nullptr);
				previous_ptr -> setNext(node_to_delete_ptr->getNext());
				//make node to del point to nullptr
				node_to_delete_ptr ->setNext(nullptr);
				//delete the node
				delete node_to_delete_ptr;
				//nodetodel = nullptr
				node_to_delete_ptr = nullptr;
				item_count_--;
				return true;
			}
			else{
				//set the previous node to the node after node todel
				previous_ptr -> setNext(node_to_delete_ptr->getNext());
				//make node to del point to nullptr
				node_to_delete_ptr ->setNext(nullptr);
				//delete the node
				delete node_to_delete_ptr;
				//nodetodel = nullptr
				node_to_delete_ptr = nullptr;
				item_count_--;
				return true;
			}
		}
	}
}



bool PlayList::add(const Song& new_song) {

	if(!contains(new_song)){
		Node<Song>* next_node_ptr = new Node<Song>();
    	next_node_ptr->setItem(new_song);
    	//next_node_ptr->setNext(tail_ptr_);
    	if(tail_ptr_ != nullptr){
	      	// get the last node and make it point to new node
	    	tail_ptr_->setNext(next_node_ptr);
    	}
    	else{
    			head_ptr_ = next_node_ptr;
    		}

       	// make new no0de point to nullptr
    	next_node_ptr->setNext(nullptr);
       	// update tailptr
    	tail_ptr_ = next_node_ptr;          
    	item_count_++;
	
		return true;
	}

	return false;
}

Node<Song>* PlayList::getPointerTo(const Song& target, Node<Song>*& previous_ptr) const{
	bool found = false;
   Node<Song>* cur_ptr = head_ptr_;
   
   
   while (!found && (cur_ptr != nullptr))
   {
      if (target == cur_ptr->getItem()){
         found = true;
      
     	return cur_ptr;
     }
      else
      	previous_ptr = cur_ptr;
         cur_ptr = cur_ptr->getNext();
   } // end while
   
   return nullptr;
  
}

Node<Song>* PlayList::getPointerToLastNode() const{
	bool found = false;
	Node<Song>* ptr = head_ptr_;
	while (!found){
		if(ptr -> getNext() == nullptr){
			found = true;
			return ptr;
		}
		else{
			ptr = ptr->getNext();
		}
	}
	return ptr;
}
void PlayList::loop(){
	Node<Song>* last_ptr = getPointerToLastNode();
    last_ptr->setNext(head_ptr_);
}
void PlayList::unloop(){
	tail_ptr_ -> setNext(nullptr);
}


void PlayList::displayPlayList(){
	//LinkedSet<Song> vec = toVector();
	for(int i = 0; i < item_count_; i++){
		cout << "* Title:" << " " << toVector()[i].getTitle() << " " <<"*" <<   " Author:" << " "
		<< toVector()[i].getAuthor() << " "<< "* Album:" << " " << toVector()[i].getAlbum() << " *" << endl;
	}
	cout << "End of playlist" << endl;


	
}



PlayList::~PlayList(){
	unloop();
	
}


/*
Node<Song>* temp1 = head_ptr_;
	bool can_remove_item = (!isEmpty() && contains(a_song));

	if(can_remove_item == 1 )
	{
		if(item_count_ == 1)
		{
			head_ptr_ = temp1 -> getNext();
			free(temp1);
			return true;
		}		
	else
	{
	Node<Song>* temp2 = getPointerTo(a_song, temp1);

		temp1 -> setNext(temp2 -> getNext());
		temp2 = nullptr;
		delete temp2;
	}
	item_count_--;
	}
return can_remove_item;







*/


