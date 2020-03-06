#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct element
{
	int data;												// head -->next
	struct element* next;	//to go to next column			//	|	
	struct element* down; 	//to go to next row				// down
};



char s = ';';
char c = ',';


typedef struct element* entry;

entry createhead(int value)  //to create first element of a column
{
	entry head = NULL;
	head = (entry)malloc(sizeof(struct element));
	head -> data = value;
	return (head);
}


int list_len(entry list)
{
	entry temp = NULL;
	int i=1;
	temp = list;
	while(temp->next != NULL)
	{
		i = i+1;
		temp = temp->next;
	}
	return i;
}

void printMat(entry head)
{
	entry temp = head;
	entry temp2 = head;
	while(temp2 != NULL){
		while(temp != NULL)
		{
			printf("%d  ",temp->data);
			temp = temp->next;
		}
		printf("\n\n");
		temp = temp2->down;
		temp2 = temp2->down;
	}
}

void insert(entry el,int value)	//to add a new elemnt beside the elemnt el (in the same colummn)
{

	entry temp = NULL;
	temp = (entry)malloc(sizeof(struct element));
	el -> next = temp;
	temp -> data = value; 

}

int n_row(entry head)
{
	int row = 0;
	entry temp = head;

	while(temp != NULL){
		temp = temp->down;
		row++;
	}
	
	return row;
		
}

int n_col(entry head)
{
	int col=0;
	entry temp = head;
	while(temp != NULL){
		temp = temp->next;
		col++;
	}

	return col;
}


entry createMat(char str[])
{	
	entry head = createhead(atoi(&str[0]));
	entry temp = NULL;		//For transversing horizontally (that is through columns)
	temp = (entry)malloc(sizeof(struct element));
	temp = head;
	entry temp2 = NULL;		//For transversing vertically (that is through rows)
	temp2 = (entry)malloc(sizeof(struct element));
	temp2 = head;


	for(int i = 1;i<strlen(str);i++){
		if (str[i] != s && str[i] != c){
			temp->next = NULL;
			temp->next = (entry)malloc(sizeof(struct element));
			temp = temp->next;
			temp->data = atoi(&str[i]);
			
			if (str[i+1] != s && str[i+1] != c){		//If more than one digit , ignore those digits for the loop
				i = i+2;
			}

		}
		if (str[i] == s){
			i++;			//to ignore ';'
			temp2->down = NULL;
			temp2->down = (entry)malloc(sizeof(struct element));
			temp = temp2-> down;
			temp->data = atoi(&str[i]);
			if (str[i+1] != s && str[i+1] != c){		//If more than one digit , ignore those digits for the loop
				i = i+2;
			}
			temp2 = temp2->down;
		}
	}
	
	
	
	temp = head->next;
	temp2 = head ->down;
	entry temp3 = temp2->next;
	for(int j = 0;j<n_row(head)-2;j++){
		for(int k = 0;k<n_col(head)-1;k++)
		{
			temp->down = temp3;
			temp = temp->next;
			temp3 = temp3->next;
		}
		temp = temp2->next;
		temp2 = temp2->down;
		temp3 = temp2->next;

	}
	
	for(int k = 0;k<n_col(head)-1;k++)
	{
		temp->down = temp3;
		temp = temp->next;
		temp3 = temp3->next;
		
	}

	
	return head;
}

entry transposeMat(char str[])
{	
	entry head = createhead(atoi(&str[0]));
	entry temp = NULL;		//For transversing horizontally (that is through columns)
	temp = (entry)malloc(sizeof(struct element));
	temp = head;
	entry temp2 = NULL;		//For transversing vertically (that is through rows)
	temp2 = (entry)malloc(sizeof(struct element));
	temp2 = head;


	for(int i = 1;i<strlen(str);i++){
		if (str[i] != s && str[i] != c){
			temp->down = NULL;
			temp->down = (entry)malloc(sizeof(struct element));
			temp = temp->down;
			temp->data = atoi(&str[i]);

		}
		if (str[i] == s){
			i++;			//to ignore ';'
			temp2->next = NULL;
			temp2->next = (entry)malloc(sizeof(struct element));
			temp = temp2-> next;
			temp->data = atoi(&str[i]);
			temp2 = temp2->next;
		}
	}
	
	
	
	temp = head->down;
	temp2 = head ->next;
	entry temp3 = temp2->down;
	for(int j = 0;j<n_row(head)-2;j++){
		for(int k = 0;k<n_col(head)-1;k++)
		{
			temp->next = temp3;
			temp = temp->down;
			temp3 = temp3->down;
		}
		temp = temp2->down;
		temp2 = temp2->next;
		temp3 = temp2->down;

	}
	
	for(int k = 0;k<n_col(head)-1;k++)			//For the last one
	{
		temp->next = temp3;
		temp = temp->down;
		temp3 = temp3->down;
		
	}

	
	return head;
}

int ifEqual(entry a,entry b)
{	

	if(n_row(a) != n_row(b) || n_col(a) != n_col(b) )
		return 0;
	int isEqual = 1;
	entry temp = a;
	entry temp2 = a;
	entry temp3 = b;
	entry temp4 = b;
	for(int j = 0;j<n_row(a)-2;j++){
		for(int k = 0;k<n_col(a)-1;k++)
		{
			if(temp->data != temp3->data){
				isEqual=0;
				break;
			}
			temp = temp->next;
			temp3 = temp3->next;
		}
		temp2 = temp2->down;
		temp4 = temp4->down;
		temp = temp2->next;
		temp3 = temp4->next;


	}
	
	for(int k = 0;k<n_col(a)-1;k++)			//For the last one
	{
		if(temp->data != temp3->data){
			isEqual=0;
			break;
		}
		temp = temp->next;
		temp3 = temp3->next;
		
	}
	
	return isEqual;
}


void ifSquare(char m[])
{
	entry head = createMat(m);
	printf("Number of rows = %d and Number of columns = %d \n",n_row(head),n_col(head));
	if(n_row(head) == n_col(head))
		printf("∴It is a square matrix\n");
	else
		printf("∴It is not a square matrix\n");
}


void ifSymmetric(char m[])
{	
	entry a = createMat(m);
	printf("A = \n");
	printMat(a);
	entry b = transposeMat(m);
	printf("Transpose(A) = \n");
	printMat(b);	
	if(n_row(a) == n_col(a)){
		
		if(ifEqual(a,b) == 1)
			printf("∴It is symmetric\n");
		else
			printf("∴It is not symmetric\n");
	}
	else
		printf(":∴It is not symmetric\n");

}

void readFile(char file[],char m[] )
{

	FILE *ptr;
	ptr = fopen(file,"r");
	if(ptr == NULL){
		printf("Could not open %s\n",file);
	
	}else{
		fscanf(ptr,"%[^\n]",m);
		fclose(ptr);
	}
}
		
int main()
{
	char m[100];
	char p[100];
	readFile("inpA.dat",m);
	readFile("inpB.dat",p);
	entry n = createMat(p);
	entry o = transposeMat(p);
	

	

}



