#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include "freqaddr.h"


/*NOTE ERROR MESSAGES SHOULD BE PRINTED TO stderr USING fprintf.*/


/*declare as global variable so no need to pass into functions*/
int list_size = 0;



LLNode* badSort(LLNode *head, LLNode *nHead){
	/*performs selection sort on a linked list*/
  
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
  
 

  while(size!= list_size){
    
    /* finds max frequency*/
    
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
    

    /*add new node

    no list exists yet
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

    /*list already exists*/
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


int printList(int numPrint, LLNode *head){
  
  LLNode *temp;
  
  int count = 0;


	temp = head;
  while(temp!=NULL){
    
    if(numPrint == 0){ 
      printf("0x%zx: %d\n", temp->hex, temp->freq);
    }
    else{
      if(count < numPrint){
        printf("0x%zx: %d\n", temp->hex, temp->freq);
      }
      else
        break;
    }
    count++;
    temp = temp->next;
  }


  return 0;
}

int main(int argc, char* argv[]){
	
	
	size_t num;
	FILE *fp;

	int numPrint = strtol(argv[2], NULL, 10);

	LLNode *root;


	LLNode *current;

	LLNode *temp;

	int line = 1;

	LLNode *newNode;

	LLNode *output;

	if(argv[4]!= 0){
		fprintf(stderr, "Improperly formatted input arguments.\n");
		return 0;

	}

	fp = fopen(argv[3], "r");
	
	  
	
	root = NULL;

	
	current = NULL;

	
	temp = (LLNode*)malloc(sizeof(LLNode));

	
	newNode = NULL;

	

	
	if(fp == 0){
		fprintf(stderr, "Error. Could not open file.\n");
		return 0;
	}

	else{
		
		/*
     * scans the hexadecimal in the line into a size_t
     * then add to or create a linked list
    */

		while(fscanf(fp, "%zx", &num) != EOF){
			

			/*the inner while loop iterates through the linked list
			 and checks for repeats
			*/
			while(temp != NULL){

				/*if there is no root, create new linked list*/
				if(root == NULL){

					root = (LLNode*)malloc(sizeof(LLNode));

					root->hex = num;
					root->freq = 1;
					root->line_num = line;
					root->next = NULL;
          				root->skip = 0;
					
					current = root;
					temp = root;

					/*increase line number tracker*/
					line++;
					list_size++;
					break;
				}
        
			   	/*check to see if the hex already exists*/
				if(temp->hex == num){
					
					int frequency = temp->freq;
					frequency++;
					temp->freq = frequency;
					
					printf("freq: %zx: %d\n", temp->hex, temp->freq);
					break;
				}

				/*if at end of linked list, create a new node*/
				if(temp->next == NULL){
					
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
				
				temp = temp->next;

			}
      

		}

	}
	
	
	/*sort the list*/
	temp = root;
	
		output = (LLNode*)malloc(sizeof(LLNode));
    output =	badSort(temp, output);

  printList(numPrint, output);

	
	fclose(fp);

	return 0;
	

}
