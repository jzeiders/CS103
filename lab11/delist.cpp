#include "delist.h"
#include <iostream>

using namespace std;

DEList::DEList(){
	start = nullptr;
	end = nullptr;
}
DEList::~DEList(){
  DEItem* item = start;
  DEItem* temp;
  while(item!= nullptr){
    temp = item;
    item = temp->next;
    delete temp;

  }
	return;
}
bool DEList::empty(){
	if(start == nullptr && end == nullptr)
		return true;
	return false;
}
int DEList::size(){
  if(empty())
    return -1;
	int size = 0;
	DEItem* item = start;
	while(item != nullptr) {
		size+=1;
		item = item->next;
	}
	return size;
}
int DEList::front(){
	if(empty())
		return -1;
	return start->val;

}
int DEList::back(){
	if(empty())
		return -1;
	return end->val;
}
void DEList::push_front(int new_val){
  DEItem *item = new DEItem();
  item->val = new_val;
  item->prev = nullptr;
  item->next = start;
	if(!empty())
		start->prev = item;
	start = item;
	if(end == nullptr)
		end = item;
	return;
}
void DEList::push_back(int new_val){
  DEItem *item = new DEItem();
  item->val = new_val;
  item->prev = end;
  item->next = nullptr;
	if(!empty())
		end->next = item;
	end = item;
	if(start == nullptr)
		start = item;
	return;
}
void DEList::pop_front(){
  DEItem *temp = start;
	if(size()>1) {
		start->next->prev = nullptr;
		start = start->next;
  }
  else {
		start = nullptr;
    end = nullptr;
  }
  delete temp;
	return;
}
void DEList::pop_back(){
  DEItem *temp = end;

	if(size()>1) {
		end->prev->next = nullptr;
		end = end->prev;
  }
  else {
		start = nullptr;
    end = nullptr;
  }
  delete temp;
	return;
}
