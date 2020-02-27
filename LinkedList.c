#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node
{
	int data;
	struct node* next;
};

struct node* createList()
{
	int i;
	struct node* head = NULL;
	struct node* temp = NULL;
	struct node* add = NULL;
	printf("Enter the values for the Linked lists:");
	scanf("%d",&i);
	for( int j = 0;j<i;j++)
	{
		temp = (struct node*)malloc(sizeof(struct node));
		printf("Enter position %d value:\n",j+1);
		scanf("%d",&temp->data);
		if ( head == NULL)
		{
			head = temp;
			add = head;
		}
		else
		{
			add->next = temp;
			add = add->next;
		}
	}
	printf("List is successfully added.\n");
	return (head);
}

void printList(struct node* list)
{
	printf("The list is:\n");
	while(list != NULL)
	{
		printf("%d\n",list->data);
		list = list->next;
	}
}

int list_len(struct node* list)
{
	struct node* temp = NULL;
	int i=1;
	temp = list;
	while(temp->next != NULL)
	{
		i = i+1;
		temp = temp->next;
	}
	return i;
}

void Insert(struct node* list,int position,int value)
{

	struct node* temp = NULL;
	struct node* add = NULL;
	temp = (struct node*)malloc(sizeof(struct node));

	int n = list_len(list);
	if(position > n+1 || position <1)
	{
		printf("Invalid operation.\n");
	}
	else if(position == 1)
	{
		temp->next = NULL;
		temp->data = value;
		temp->next = list;
		list = temp;
		printList(list);
	}
	else if(position == INT_MAX)
	{
		printf("Cannot exceed the INT limit\n");
	}
	else
	{
		temp->next = NULL;
		temp->data = value;
		add = list;
		for( int k=0;k<(position -1);k++)
		{
			add = add->next;	
		}
		temp->next = add->next;
		add->next = temp;
		printList(list);
	}	
}

void Delete(struct node* list,int position)
{
	struct node* add = NULL;
	int n = list_len(list);
	
	add = (struct node*)malloc(sizeof(struct node));
	
	if(position < 1 || position > n)
		printf("Invalid Operation\n");
		
	else if(position == 1 )
	{
		add->next =NULL;
		add = list->next;
		//temp->data = list->next->data;
		list = add;
		printList(list);
	}
	
	else if(position == n)
	{
		add = list;
		for(int k = 0;k< (n - 1);k++)
			add = add->next;
		add->next = NULL;
		printList(list);
	}
		
	else
	{
		add = list;
		for(int k = 0;k< (position -1);k++)
			add = add->next;
		add->next = add->next->next;
		printList(list);
	}
}

int find(struct node* list,int value)
{
	struct node* temp = NULL;
	temp = (struct node*)malloc(sizeof(struct node));
	int a;
	int j = 0;
	temp = list;
	for(int i =0;i<list_len(list);i++)
	{
		if(value == temp->data)
		{
			a = i+1;
			j = 1;
		}
		temp = temp->next;
	}
	if(j == 0)
	{
		printf("No such element exists\n");
		return 0;
	}
	else
		return a+1;
}

void FindAndDelete(struct node* list,int value)
{
	int p = find(list,value);
	if( p != 0)
	{
		Delete(list,p);
	}
	//printList(list);
}
		
	
		
		
		
int main()
{
	struct node* n;
	n = createList();
	//printf("%d\n",list_len(n));
	printList(n);
	Insert(n,1,878);
	Delete(n,1);
	//~ printf("%d",find(n,5));

}
			
	

