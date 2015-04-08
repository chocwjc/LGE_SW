#include <stdio.h>
#include <stdlib.h>


int logbase2(unsigned num)
{
	int i;
	for (i = 31; ((1UL << i) & num) == 0;  i--);
	return i;
}


typedef enum {BLACK, RED} COLOR;

typedef struct __node {
	int data;
	COLOR color;
	struct __node *parent;
	struct __node *left;
	struct __node *right;
} NODE;

size_t num_nodes = 0;
NODE *root = NULL;

NODE *insert_data(int data)
{
	NODE *temp;
	NODE **p;

	temp = (NODE*)malloc(sizeof (NODE));
	temp->color = RED;
	temp->data = data;
	temp->right = temp->left = NULL;

	num_nodes++;
	
	p = &root;

	while (*p) {

		if (data > (*p)->data)
			p = &(*p)->right;
		else 
			p = &(*p)->left;
		
	}
	*p = temp;


	return temp;
}

static int row = -1, col = -1;

void  __display(NODE *temp, int **arr)
{

	if (!temp) return;

	row++;
	__display(temp->left, arr);
	arr[row][++col] = temp->data;
	__display(temp->right, arr);
	row--;
}

void display(NODE *temp)
{
	int i, j, h;
	int **arr;

	h = num_nodes;

	arr = (int**)malloc(sizeof (int*) * h);

	for (i = 0; i < h;  i++) 
		arr[i] = (int*)malloc(sizeof (int) * num_nodes);

	for (i = 0; i < h; i++) {
		for (j = 0; j < num_nodes; j++) {
			arr[i][j] = -1;
		}
	}

	row = -1;
	col = -1;
	__display(temp, arr);

	for (i = 0; i < h; i++) {
		for (j = 0; j < num_nodes; j++) {
			if (arr[i][j] >= 0)
				printf("%3d", arr[i][j]);
			else
				printf("   ");
		}
		printf("\n");
	}
	for (i = 0; i < h;  i++)
		free(arr[i]);
	free(arr);
}



int main()
{
	int i;
	NODE *node;
	int a[20] = {
		1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20
	};


	for (i = 0; i <20; i++) {
		insert_data(a[i]);
		system("clear");
		display(root);
		getchar();
	}
}

		
