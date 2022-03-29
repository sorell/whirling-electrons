#include <stdio.h>
#include <cassert>
#include "linkedlist.h"


struct TestItem
{
	struct ListHead head;
	int num;
};


static void testInit(void)
{
	LIST_HEAD(list);
	assert(list.next != NULL);
	assert(list.prev != NULL);
	assert(list.next == list.prev);
}


static void testAdd(void)
{
	LIST_HEAD(list);
	struct TestItem item1 { INIT_LIST_HEAD(item1.head), 1 };
	struct TestItem item2 { INIT_LIST_HEAD(item2.head), 2 };
	struct TestItem item3 { INIT_LIST_HEAD(item3.head), 3 };
	struct TestItem item4 { INIT_LIST_HEAD(item4.head), 4 };
	struct TestItem item5 { INIT_LIST_HEAD(item5.head), 5 };
	ListAdd(&item1.head, &list);
	ListAdd(&item2.head, &list);
	ListAdd(&item3.head, &list);
	ListAdd(&item4.head, &list);
	ListAdd(&item5.head, &list);

	int num = 1;
	for (ListHead *ptr = list.next; ptr = ptr->next; ptr != &list)
	{
		struct TestItem *item = ListEntry(ptr->head, struct TestItem, head);
	}
}


int main(void)
{
	testInit();
	testAdd();
	return 0;
}
