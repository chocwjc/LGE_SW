#include <stdio.h>


typedef struct _node {int data; struct _node *next;} NODE;

NODE head1 = {.next = &head1};
NODE head2 = {.next = &head2};

void insert_data(NODE *head, NODE *temp)
{
	temp->next = head->next;
	head->next = temp;
}

void display_node(NODE *head)
{
	NODE *cur;
	printf("[head] -> ");
	for (cur = head->next; cur != head; cur = cur->next) {
		printf("[%d] -> ", cur->data);
	}
	printf("[head]\n");
}

void reverse(NODE *head)
{

	NODE *cur, *next, *prev;

	prev = head;
	cur = head->next;
	while (cur != head) {

		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	head->next = prev;

}

int main()
{

	NODE *node;
	node = malloc(sizeof (NODE));
	node->data = 1;
	insert_data(&head1, node);
	node = malloc(sizeof (NODE));
	node->data = 2;
	insert_data(&head1, node);
	node = malloc(sizeof (NODE));
	node->data = 3;
	insert_data(&head1, node);
	node = malloc(sizeof (NODE));
	node->data = 4;
	insert_data(&head1, node);
	node = malloc(sizeof (NODE));
	node->data = 5;
	insert_data(&head1, node);
	node = malloc(sizeof (NODE));
	node->data = 6;
	insert_data(&head1, node);
	node = malloc(sizeof (NODE));
	node->data = 7;
	insert_data(&head1, node);


	display_node(&head1);
	reverse(&head1);
	display_node(&head1);

	return 0;
}
