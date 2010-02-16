#include <stdio.h>
#include <stdlib.h>

struct list {
	int count;
	struct list *next;
};


struct list *create_node(int count)
{
	
	struct list *temp;
	temp = malloc(sizeof(struct list));

	temp->count = count;
	temp->next = NULL;
	return temp;
}

void del_node(struct list *temp)
{
	if( NULL == temp->next)
		free(temp);
}

void scp(char *src, char *dst)
{

	while(src!=NULL || dst!=NULL) {
		*(dst++) = *(src++);
	}
}

int main (int argc, char **argv)
{
	struct list *head;
	char src[]="welcome", dst[100];
	int a = 1,b = 2,c = 3;
	head = create_node(1);

	if(head != NULL ) printf("Node created node count = %d\n", head->count);
	
	del_node(head);

	printf("Node deleted\n");
	printf("hello world\n");
//	scp(src, dst);
	a=b<<=c;

	printf("a=%d, b=%d, c=%d\n",a,b,c);
	if("cat" == "cat")
		printf("ASdf\n");
	return 0;
}
