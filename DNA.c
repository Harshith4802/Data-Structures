#include <stdio.h> 
#include <stdlib.h>

struct dnaMolecule{
	char data;                  //For storing the values of nucleotides of Alpha chain
	char link;					//For storing the values of nucleotides of Beta chain
	struct dnaMolecule* next;
};
	
int check(char x){   //for checking if the value of nucleotide is valid i.e A or G or T or C
	if(x == 'A' || x =='C' || x =='G' || x =='T')
		return 1;
	else
		return 0;	
	
}

char comp(char x){    //For finding the complement of given nucleotide value
	if(x == 'A')
		return 'T';
	else if(x == 'C')
		return 'G';
	else if(x == 'G')
		return 'C';
	else if(x == 'T')
		return 'A';
	else{
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
		printf("Enter Nucleotide %d value(A or G or T or C):",j+1);
		scanf(" %c",&c);
		if (check(c) == 0){					//only allowing A or G or T or C
			
			printf("Invalid value\n");
			j = j-1;
			continue;
		
		} else { 
		
			if (s == 'A'){				//Inserting the values of nucleotide in alpha chain
		
				temp->data = c;
				temp->link = comp(c);
				
			} else if (s == 'B'){		//Inserting the values of nucleotide in beta chain
		 
				temp->data = comp(c);
				temp->link = c;
		
			} 
		} 
		
		if ( head == NULL){				//If dna has no nucleotides yet 
		
			head = temp;
			add = head;
		
		}  else {						//If dna already has some nucleotides
		
			add->next = temp;
			add = add->next;
		
		}
	}

	return (head);

} 

void printdna(dna head)			//for printing the DNA molecule
{	
	dna temp = head;
	
	printf("\n");
	printf("%c",temp->data);
	temp = temp->next;
	while(temp != NULL){
		printf("--%c",temp->data);			//for printing alpha chain
		temp = temp->next;				//Transversing through the nucleotides
	}
	printf("\n");
	temp = head;
	while(temp != NULL){
		printf("|  ");						//for printing the links between alpha and beta chains
		temp = temp->next;
	}
	printf("\n");
	temp = head;
	printf("%c",temp->link);				//for printing beta chain
	temp = temp->next;
	while(temp != NULL){
		printf("--%c",temp->link);
		temp = temp->next;
	}

}

int dnalen(dna head)		//For finding the number of nucleotides in a dna molecule
{
	dna temp = NULL;
	int i=1;
	temp = head;
	while(temp->next != NULL){
		i = i+1;
		temp = temp->next;
	}
	return i;
}

void insert(dna head,char chain,int position,char nucleotide)			//chain is for specifying chain ID (alpha = A , beta = B)
{
	if(chain == 'A'|| chain == 'B'){			//checking if chain ID is correct
		dna temp = NULL;
		dna add = NULL;
		temp = (dna)malloc(sizeof(struct dnaMolecule));

		int n = dnalen(head);
		if(position > n+1 || position <1){
			
			printf("Invalid operation.\n");
		
		}
		//~ else if(position == 1){				//inserting at the beginning of the dna
		
			
			//~ temp->next = NULL;
			//~ if(chain == 'A'){
			
			//~ temp->data = nucleotide;
			//~ temp->link = comp(nucleotide);
			
			//~ }else if(chain == 'B'){							//It was not working when kept in this function , so i kept it directly in the main
			
			//~ temp->link = nucleotide;
			//~ temp->data = comp(nucleotide);		
			
			//~ }
			//~ temp->next = head;
			//~ head = temp;
		//~ }
		else{
		
			temp->next = NULL;
			if(chain == 'A'){					//Inserting the values of nucleotide  in alpha chain
			
			temp->data = nucleotide;
			temp->link = comp(nucleotide);
			
			}else if(chain == 'B'){				//Inserting the values of nucleotide in beta chain
			
			temp->link = nucleotide;
			temp->data = comp(nucleotide);		
			
			}
			add = head;
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

void delete(dna head,int position)
{
	dna add = NULL;
	int n = dnalen(head);
	
	add = (dna)malloc(sizeof(struct dnaMolecule));
	
	if(position < 1 || position > n){
	
		printf("Invalid Operation\n");
	
	}else{
	
		add = head;
		for(int k = 0;k< (position -2);k++)
			add = add->next;
		add->next = add->next->next;
	
	}
}
dna split(dna head)
{
	dna temp;
	dna nbeta;
	dna beta;
	temp = NULL;
	
	beta = (dna)malloc(sizeof(struct dnaMolecule));
	nbeta = (dna)malloc(sizeof(struct dnaMolecule));
	
	int n = dnalen(head);
	temp = head;
	nbeta = beta;
	
	while(temp != NULL){
		nbeta->next = (dna)malloc(sizeof(struct dnaMolecule));
		nbeta->link = temp->link ;
		temp->link = 'NULL';				//Breaking out the beta chain of the old one
		temp = temp->next;
		nbeta = nbeta->next;
	}

	nbeta = beta;

	
	for (int i = 0;i < n;i++){				//creating the alpha chain for the newly broken beta chain
		
		nbeta->data = comp(nbeta->link);
		nbeta = nbeta->next;
		if(i == n-2){
			nbeta->next = NULL;
		}
	
	}
	
	temp = head;
	
	while(temp != NULL){				//creating back the beta chain for the old one
		temp->link = comp(temp->data);
		temp = temp->next;
	}
 
	
	return beta;

}

int main()
{
		printf("All the written functions are case sensitive(Only capital letters allowed).Please switch ON your caps lock.\n");
		dna dnaid[30];     //Array for storing DNA molecule ID's
		int i;
		int count = 0;		//For storing the number of dna's created
	start:					//for goto function , To comeback to the menu after any one of the below functions is completed
		
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
		
		
		
		
		if (i == 1){				//For creating the dna moleculse
			int in;
			char s;
			printf("Enter number of nucleotides : ");
			scanf("%d",&in);
			re1:
			printf("Select chain (alpha = A , beta = B) : ");
			scanf(" %c",&s);
			if(s != 'A' && s != 'B'){
				printf("Invalid chain ID (Choose  'A' or 'B') \n");
				goto re1;
			}
			dnaid[count] = createdna(in,s);
			printf("DNA%d Created (ID = %d): \n",count,count);
			printdna(dnaid[count]);
			printf("\n");
			count++;
			goto start;
		}else if (i == 2){				//For inserting a nucleotide
			
			int id;
			char cid;
			int p;
			char n;
			re_0:
			printf("Select DNA Molecule ID :");
			scanf("%d",&id);
			if (id > count-1){		//If wrong dna id is entered
			
				printf("DNA not found.\n");
				goto re_0;
			}
			re2_1:
			printf("Select Chain ID (alpha = A , beta = B): ");
			scanf(" %c",&cid);
			if(cid != 'A' && cid != 'B'){
				printf("Invalid chain ID.Enter A or B\n");
				goto re2_1;
			}
			re2_2:
			printf("Select position to insert : ");
			scanf("%d",&p);
			int no = dnalen(dnaid[id]);
			if(p < 1 || p > no+1){
	
				printf("Invalid Operation\n");
				goto re2_2;
			}
			re2_3:
			printf("Select Nuceleotide to insert : ");
			scanf(" %c",&n);
			if(check(n)==0){

				printf("Invalid Nucleotide.Enter A or G or C or T\n");
				goto re2_3;
			}
			
			if(p== 1){				//For inserting at the beginning
				
				dna temp = NULL;
				temp = (dna)malloc(sizeof(struct dnaMolecule));
				temp->next = NULL;
				if(cid == 'A'){		//insering in alpha chain
				
					temp->data = n;
					temp->link = comp(n);
				
				}else if(cid == 'B'){		//insering in beta chain
				
					temp->link = n;
					temp->data = comp(n);		
				
				}
				temp->next = dnaid[id];
				dnaid[id] = temp;
				printf("DNA%d: \n",id);				
				printdna(dnaid[id]);
				printf("\n");
				goto start;
			}else{
				
				insert(dnaid[id],cid,p,n);
				printf("DNA%d: \n",id);
				printdna(dnaid[id]);
				printf("\n");
				goto start;
			}
			
		}else if (i == 3){				//For deleting a nucleotide pair
			
			int id;
			int p;
			
			printf("Select DNA Molecule ID :");
			scanf("%d",&id);
			re3_0:
			if (id > count-1){		//If wrong dna id is entered
			
				printf("DNA not found.\n");
				goto re3_0;
			}
			re3_1:
			printf("Select position to delete : ");
			scanf("%d",&p);
			int no = dnalen(dnaid[id]);
			if(p < 1 || p > no+1){
	
				printf("Invalid Operation.Position is between 1 and %d. \n",no );
				goto re3_1;
			}
			if(p == 1){				//For deleting the first nucleotide
				
				dna add = NULL;
				add = (dna)malloc(sizeof(struct dnaMolecule));
				add->next =NULL;
				add = dnaid[id]->next;
				dnaid[id] = add;
				printf("DNA%d: \n",id);
				printdna(dnaid[id]);
				printf("\n");
				goto start;
			}else if(p == dnalen(dnaid[id])){		//For deleting the last nucleotide pair
				
				dna add = NULL;
				add = (dna)malloc(sizeof(struct dnaMolecule));
				add = dnaid[id];
				for(int k = 0;k< (dnalen(dnaid[id]) - 2);k++){
					add = add->next;
				}
				add->next = NULL;
				printf("DNA%d: \n",id);
				printdna(dnaid[id]);
				printf("\n");
				goto start;
	
			}else{				
				delete(dnaid[id],p);
				printf("DNA%d: \n",id);
				printdna(dnaid[id]);
				printf("\n");
				goto start;
			}
			
		}else if (i == 4){
			
			int id;
			printf("Select DNA Molecule ID :");
			scanf("%d",&id);
			if (id > count-1){		//If wrong dna id is entered
			
				printf("DNA not found.\n");
				goto start;
			}
			dnaid[count] = split(dnaid[id]);
			printdna(split(dnaid[id]));
			count++;
			printf("\n");
			goto start;
			
		
		}else if (i == 5){			//For printing a dna molecule
			
			int id;
			printf("Select DNA Molecule ID :");
			scanf("%d",&id);
			if (id > count-1){		//If wrong dna id is entered
			
				printf("DNA not found.\n");
				goto start;
			}else{
				printf("DNA%d: \n",id);
				printdna(dnaid[id]);
				printf("\n");
				goto start;
			}
		}else if (i == 6){			//For printing all the dna molecules 
			
			for(int j = 0;j<count;j++){
				printf("DNA%d: ",j);
				printdna(dnaid[j]);
				printf("\n");
				printf("\n");

			}
			printf("\n");
			goto start;
		
		}else{
			
			printf("Please enter a valid number");
			goto start;
		} 

}
