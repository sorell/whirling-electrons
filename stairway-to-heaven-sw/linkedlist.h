#ifndef _SS_LINKEDLIST_H
#define _SS_LINKEDLIST_H


#define INIT_LIST_HEAD(name) { &(name), &(name) }
#define LIST_HEAD(name) struct ListHead name = INIT_LIST_HEAD(name)

#define ListEntry(headPtr, type2, member) \
	ContainerOf(headPtr, type2, member)
	
#define ContainerOf(ptr, type2, member) ({ \
    const type2of( ((type2 *)0)->member ) *__mptr = (ptr); \
    (type2 *)( (char *)__mptr - OffsetOf(type2,member) );})

#define OffsetOf(type2, member) \
    ((unsigned int)((unsigned char*)&((type2*)0)->member - (unsigned char*)0))


struct ListHead
{
	ListHead *next;
	ListHead *prev;
};


static inline void ListAdd(ListHead *item, ListHead *head)
{
	head->next->prev = item;
	item->next = head->next;
	item->prev = head;
	head->next = item;
}


static inline void ListAddTail(ListHead *item, ListHead *head)
{
	head->prev = item;
	item->next = head;
	item->prev = head->prev;
	head->prev->next = item;
}


static inline void ListDel(ListHead *item)
{
	item->next->prev = item->prev;
	item->prev->next = item->next;
}


#endif  // _SS_LINKEDLIST_H
