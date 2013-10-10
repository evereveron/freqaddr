#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include "freqaddr.h"


/*NOTE ERROR MESSAGES SHOULD BE PRINTED TO stderr USING fprintf.*/
/*FREE STUFF*/

/*
Declared as global variable, so no need to pass into functions.
*/
int list_size = 0;


/*
Performs selection sort on a linked list.
*/
LLNode* badSort(LLNode *head, LLNode *nHead){

  
	LLNode *current;
	LLNode *insert;
	LLNode *temp;
	LLNode *maxNode;

	int maxFreq = 0;
	int size = 0;


    	current = NULL;
    	insert = NULL;
  	temp = head;

    	maxNode = NULL;


	if(head == NULL){
    	
		return 0;
	}
 
	/*
	Finds max frequency.
	*/
	while(size!= list_size){
    
    		temp = head;
    		while(temp != NULL){

      			if(temp->freq > maxFreq && temp->skip != 1){
       
        			maxNode = temp;
        			maxFreq = temp->freq;
     			}

      			temp = temp->next;
      
    		}
    		
		maxFreq = 0;
    		maxNode->skip = 1;
    

    		/*
		Add new node.
		No list exists yet.
		*/
    		if(nHead->freq == 0){

      			insert = (LLNode*)malloc(sizeof(LLNode));
        		insert->freq = maxNode->freq;
        		insert->hex = maxNode->hex;
        		insert->line_num = maxNode->line_num;
        		insert->next = NULL;

      			size++;

      			nHead = insert;
      			current = nHead;
    		}

    		/*
		Add new node.
		List already exists.
		*/
    		else{
      			insert  = (LLNode*)malloc(sizeof(LLNode));
        		insert->freq = maxNode->freq;
        		insert->hex = maxNode->hex;
        		insert->line_num = maxNode->line_num;
        		insert->next = NULL;

      			size++;

      			current->next = insert;
      			current = insert;
    		}
    

	}

	return nHead;
}

/* 
Prints the linked list in "address: frequency" format. 
Parameters it takes are numPrint (number of addresses to print) and *head, the root of the linked list.
*/
int printList(int numPrint, LLNode *head){
  
	LLNode *temp;  
	int count = 0;
	
	/*
	Error check if desired outputs exceeds number of distinct elements.
	*/
	if(numPrint>list_size){
		fprintf(stderr, "Not enough addresses.\n");
		return 0;
	}

	temp = head;

  	while(temp!=NULL){
    
    		if(numPrint == 0){ 
      		printf("0x%lx :%d\n", temp->hex, temp->freq);
    		}

    		else{
      			if(count < numPrint){
        		printf("0x%lx :%d\n", temp->hex, temp->freq);
      			}
      			else
        			break;
    		}

    		count++;
    		temp = temp->next;
	}


	return 0;
}

void recurseFree(LLNode *root){
	if(root != NULL){
		recurseFree(root->next);
	}
	free(root);

}

/*
The main method.
It takes in 4 arguments- the program name (freqaddr), -n, the number of addresses to output, and a file name.
The main method reads the addresses from the file and stores them in a linked list.
The main method calls badSort and printList.
*/
int main(int argc, char* argv[]){
	
	
	unsigned long num;
	FILE *fp;

	int numPrint = strtol(argv[2], NULL, 10);
	int line = 1;

	LLNode *root;
	LLNode *current;
	LLNode *temp;
	LLNode *newNode;
	LLNode *output;

	
	/*
	Error check for when there are too many arguments.
	*/
	if(argv[4]!= 0){

		fprintf(stderr, "Improperly formatted input arguments.\n");
		return 0;

	}

	fp = fopen(argv[3], "r");

	root = NULL;
	current = NULL;
	newNode = NULL;
	
	temp = (LLNode*)malloc(sizeof(LLNode));
	

	/*
	Error check for when the file does not exist.
	*/
	if(fp == 0){
		fprintf(stderr, "Error. Could not open file.\n");
		return 0;
	}

	else{
		
		/*
     		Scans the hexadecimal in the line into an unsigned long,
	     	and then adds to or creates a linked list.
		*/
		while(fscanf(fp, "%lx", &num) != EOF){
			

			/*
			The inner while loop iterates through the linked list
			and checks for repeats.
			*/
			while(temp != NULL){

				/*
				If there is no root, create new linked list.
				*/
				if(root == NULL){

					root = (LLNode*)malloc(sizeof(LLNode));

					root->hex = num;
					root->freq = 1;
					root->line_num = line;
					root->next = NULL;
          				root->skip = 0;
					
					current = root;
					temp = root;

					/*
					Increase line number tracker.
					*/
					line++;
					list_size++;
					break;
				}
        
			   	/*
				Check to see if the hex already exists.
				*/
				else if(temp->hex == num){
					
					int frequency = temp->freq;
					frequency++;
					temp->freq = frequency;
					temp = root;
					break;
				}

				/*
				If at end of linked list, create a new node.
				*/
				else if(temp->next == NULL && temp->hex != num){
					
					newNode = (LLNode*)malloc(sizeof(LLNode));

					newNode->hex = num;
					newNode->freq = 1;
					newNode->line_num = line;
          				newNode->skip = 0;
					newNode->next = NULL;
					
					current->next = newNode;
					line++;
					list_size++;
					current = newNode;
					
					
					temp = root;
					
					break;
				}
				
				else 
					temp = temp->next;

			}
      

		}

	}
	
	
	/*
	Sort the list with badSort.
	*/
	temp = root;
	
	output = (LLNode*)malloc(sizeof(LLNode));
    	output = badSort(temp, output);
	
	/*
	Prints the list.
	*/
  	printList(numPrint, output);
	

	/*
	Frees memory.
	*/
	recurseFree(root);
	recurseFree(output);

	
	fclose(fp);

	return 0;
	

}
