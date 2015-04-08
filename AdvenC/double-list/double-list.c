#include <stdio.h>
#include <stdlib.h>


#define offsetof(type, member) ((size_t)&((type*)0)->member)
#define list_entry(ptr, type, member) ((char*)ptr - offsetof(type, member))

typedef struct __node {
	int data; 
	struct __node *next;
	struct __node *prev;
} NODE;

NODE head = {
	.next = &head,
	.prev = &head,
};

void __insert_data(NODE *prev, NODE *next, NODE *new)
{
	new->next = next;
	new->prev = prev;
	prev->next = new;
	next->prev = new;
}

void insert_data(NODE *node, NODE *new) 
{
	__insert_data(node, node->next, new);
}

void insert_front(NODE *head, NODE *new)
{
	__insert_data(head, head->next, new);
}

void insert_back(NODE *head, NODE *new)
{
	__insert_data(head->prev, head, new);
}

void display_node(NODE *head)
{
	NODE *cur;

	printf("[head] -> ");
	for (cur = head->next; cur != head; cur = cur->next)
		printf("[%d] -> ", cur->data);
	printf("[head]\n");
}

struct abc
{
	int a;
	int b;
	int c;
};

NODE *new_node(int data)
{
	NODE *new;
	new = (NODE*)malloc(sizeof (NODE));
	new->data = data;
	return new;
}

int main()
{
	insert_front(&head, new_node(1));
	insert_front(&head, new_node(2));
	insert_front(&head, new_node(3));
	insert_back(&head, new_node(4));
	insert_back(&head, new_node(5));
	insert_back(&head, new_node(6));

	display_node(&head);

	struct abc abc;

	printf("%p\n", &abc);
	printf("%p\n", &abc.c);
	printf("%p\n", list_entry(&abc.c, struct abc, c));

	return  0;
}



