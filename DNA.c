#include <stdio.h> 
#include <stdlib.h>

struct dnaMolecule{
	char data;                  //For storing the values of nucleotides of Alpha chain
	char link;					//For storing the values of nucleotides of Beta chain
	struct dnaMolecule* next;
};

//~ struct DNAid
//~ {
	//~ int id;
	//~ struct 
	//~ struct dnaMolecule* head;
//~ };


	
int check(char x){   //for checking if the value of nucleotide is valid i.e A or G or T or C
	if(x == 'A' || x =='C' || x =='G' || x =='T'){
		return 1;
	}else{
		return 0;	
	}
}

char comp(char x){    //For finding the complement of given nucleotide value
	if(x == 'A'){
		return 'T';
	}else if(x == 'C'){
		return 'G';
	}else if(x == 'G'){
		return 'C';
	}else if(x == 'T'){
		return 'A';
	}else{
		printf("Error");
		return 'E';
		} 
}


	
typedef struct dnaMolecule* dna; // dna => address of one nucleotide(eg = 'A')    dna is a pointer !

dna createdna(int i,char s){   //for creating a dna molecule
	
	char c;
	dna head = NULL;
	dna temp = NULL;
	dna add = NULL;


	for( int j = 0;j<i;j++){
	
		temp = (dna)malloc(sizeof(struct dnaMolecule));
		printf("Enter Nucleotide %d value:",j+1);
		scanf(" %c",&c);
		if (check(c) == 0){					//only allowing A or G or T or C
			
			printf("Invalid value\n");
			j = j-1;
			continue;
		
		} else { 
		
			if (s == 'A'){
		
				temp->data = c;
				temp->link = comp(c);
				
			} else if (s == 'B'){
		 
				temp->data = comp(c);
				temp->link = c;
		
			} 
		} 
		
		if ( head == NULL){
		
			head = temp;
			add = head;
		
		}  else {
		
			add->next = temp;
			add = add->next;
		
		}
	}

	return (head);

} 

void printdna(dna list)			//for printing the DNA molecule
{	
	dna temp = list;
	dna temp2 = list;
	dna temp3 = list;

	printf("\n");
	printf("%c",temp3->data);
	temp3 = temp3->next;
	while(temp3 != NULL){
		printf("--%c",temp3->data);			//for printing alpha chain
		temp3 = temp3->next;
	}
	printf("\n");
	while(temp2 != NULL){
		printf("|  ");						//for printing the links between alpha and beta chains
		temp2 = temp2->next;
	}
	printf("\n");
	printf("%c",temp->link);				//for printing beta chain
	temp = temp->next;
	while(temp != NULL){
		printf("--%c",temp->link);
		temp = temp->next;
	}

}

int dnalen(dna list)
{
	dna temp = NULL;
	int i=1;
	temp = list;
	while(temp->next != NULL){
		i = i+1;
		temp = temp->next;
	}
	return i;
}

void insert(dna list,char chain,int position,char nucleotide)			//chain is for specifying chain ID (alpha = A , beta = B)
{
	if(chain == 'A'|| chain == 'B'){
		dna temp = NULL;
		dna add = NULL;
		temp = (dna)malloc(sizeof(struct dnaMolecule));

		int n = dnalen(list);
		if(position > n+1 || position <1){
			
			printf("Invalid operation.\n");
		
		}else if(position == 1){
		
			temp->next = NULL;
			if(chain == 'A'){
			
			temp->data = nucleotide;
			temp->link = comp(nucleotide);
			
			}else if(chain == 'B'){
			
			temp->link = nucleotide;
			temp->data = comp(nucleotide);		
			
			}
			temp->next = list;
			list = temp;
		}else{
		
			temp->next = NULL;
			if(chain == 'A'){
			
			temp->data = nucleotide;
			temp->link = comp(nucleotide);
			
			}else if(chain == 'B'){
			
			temp->link = nucleotide;
			temp->data = comp(nucleotide);		
			
			}
			add = list;
			for(int k=0;k<(position-2);k++){
		
				add = add->next;	
		
			}
			temp->next = add->next;
			add->next = temp;
		
		}
	}else{
	printf("Invalid ChainID");	
	}
}

void delete(dna list,int position)
{
	dna add = NULL;
	int n = dnalen(list);
	
	add = (dna)malloc(sizeof(struct dnaMolecule));
	
	if(position < 1 || position > n){
	
		printf("Invalid Operation\n");
	
	}else if(position == 1 ){
	
		add->next =NULL;
		add = list->next;
		list = add;
	
	}else if(position == n){
	
		add = list;
		for(int k = 0;k< (n - 1);k++){
			add = add->next;
		}
		add->next = NULL;
	
	}else{
	
		add = list;
		for(int k = 0;k< (position -2);k++)
			add = add->next;
		add->next = add->next->next;
	
	}
}
void split(dna list)
{
	
	dna new;
	new = (dna)malloc(sizeof(struct dnaMolecule));
	new = list;

}

//~ int find(struct DNAid * list,int value)
//~ {
	//~ struct DNAid * temp = NULL;
	//~ temp = (struct DNAid *)malloc(sizeof(struct DNAid));
	//~ int a;
	//~ int j = 0;
	//~ temp = list;
	//~ for(int i =0;i<list_len(list);i++)
	//~ {
		//~ if(value == temp->id)
		//~ {
			//~ a = i+1;
			//~ j = 1;
		//~ }
		//~ temp = temp->next;
	//~ }
	//~ if(j == 0)
	//~ {
		//~ printf("DNA not found\n");
		//~ return 0;
	//~ }
	//~ else
		//~ return a+1;
//~ }

int main()
{
	
		dna dnaid[30];     //Array for storing DNA molecule ID's
		int i;
		int count = 0;
	start:					//for goto function , To comeback to the menu after the below functions are completed
		
		printf("****************************************\n");
		printf("Menu:\n");
		printf("1 . Create DNA\n");
		printf("2 . Insert\n");
		printf("3 . Delete\n");
		printf("4 . Split\n");
		printf("5 . Print DNA\n");
		printf("6 . Print all DNA\n");
		printf("****************************************\n");
		printf("Select any option - \n");
		scanf("%d",&i);
		if (i == 1){
			int in;
			char s;
			printf("Enter number of nucleotides : ");
			scanf("%d",&in);
			printf("Select chain (alpha = A , beta = B) : ");
			scanf(" %c",&s);
			//~ if(s != 'A' || s != 'B'){
				//~ printf("Invalid chain ID (Choose 'A' or 'B') \n");
				//~ goto start;
			//~ }
			dnaid[count] = createdna(in,s);
			printf("DNA%d Created : \n",count);
			printf("ID = %d",count);
			printdna(dnaid[count]);
			printf("\n");
			count++;
			goto start;
		}else if (i == 2){
			 
			int id;
			char cid;
			int p;
			char n;
			printf("Select DNA Molecule ID :");
			scanf("%d",&id);
			printf("Select Chain ID (alpha = A , beta = B): ");
			scanf(" %c",&cid);
			if(cid != 'A' || cid != 'B'){
				printf("Invalid chain ID");
				goto start;
			}
			printf("Select position to insert : ");
			scanf("%d",&p);
			printf("Select Nuceleotide to insert : ");
			scanf(" %c",&n);
			insert(dnaid[id],cid,p,n);
			printf("DNA%d: \n",id);
			printdna(dnaid[id]);
			printf("\n");
			goto start;
			
		}else if (i == 3){
			
			int id;
			int p;
			
			printf("Select DNA Molecule ID :");
			scanf("%d",&id);
			printf("Select position to delete : ");
			scanf("%d",&p);
			delete(dnaid[id],p);
			printf("DNA%d: \n",id);
			printdna(dnaid[id]);
			printf("\n");
			goto start;
		
		}else if (i == 5){
			
			int id;

			printf("Select DNA Molecule ID :");
			scanf("%d",&id);
			printf("DNA%d: \n",id);
			printdna(dnaid[id]);
			printf("\n");
			goto start;
		}else if (i == 6){
			
			for(int j = 0;j<count;j++){
				printf("DNA%d: ",j);
				printdna(dnaid[j]);
				printf("\n");
				printf("\n");

			}
			printf("\n");
			goto start;
		
		}

}
