#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include "freqaddr.h"


//NOTE ERROR MESSAGES SHOULD BE PRINTED TO stderr USING fprintf.


//declare as global variable so no need to pass into functions
int list_size = 0;


LLNode* badSort(LLNode *head, LLNode *nHead){
	//performs selection sort on a linked list
  
  if(head == NULL){
    return 0;

  }
  
  LLNode *current;
    current = NULL;
  LLNode *insert;
    insert = NULL;
  
  LLNode *temp;
    temp = head;
  LLNode *maxNode;
    maxNode = NULL;

  int maxFreq = 0;
  int size = 0;

  while(size!= list_size){
    
    //finds max frequency
    
    temp = head;
    while(temp != NULL){
      
     // printf("temp is %zx, maxfreq is %d. tempfreq is %d, and skip is %d.\n", temp->hex, maxFreq, temp->freq, temp->skip);


      if(temp->freq > maxFreq && temp->skip != 1){
       // printf("found a max\n");
        maxNode = temp;
        maxFreq = temp->freq;
     }

      temp = temp->next;


      
    }
    maxFreq = 0;
    maxNode->skip = 1;
   // printf("maxNode is %zx. skip is %d.\n", maxNode->hex, maxNode->skip); 
    

    //add new node

    //no list exists yet
    if(nHead->freq == 0){
      insert = (LLNode*)malloc(sizeof(LLNode));
        insert->freq = maxNode->freq;
        insert->hex = maxNode->hex;
        insert->line_num = maxNode->line_num;
        insert->next = NULL;

      size++;

      nHead = insert;
       // printf("nHead is %zx: %d.\n", nHead->hex, nHead->freq);
      current = nHead;
    }

    //list already exists
    else{
      insert  = (LLNode*)malloc(sizeof(LLNode));
        insert->freq = maxNode->freq;
        insert->hex = maxNode->hex;
        insert->line_num = maxNode->line_num;
        insert->next = NULL;

      size++;

       // printf("insert is %zx: %d.\n", insert->hex, insert->freq);

      current->next = insert;
      current = insert;
    }
    

  }
  
  /*
  temp = nHead;
  while(temp != NULL){
    printf("%zx: %d.\n", temp->hex, temp->freq);
    temp = temp->next;
  }
  */


  return nHead;
}


int printList(int numPrint, LLNode *head){
  
  LLNode *temp;
  temp = head;
  int count = 0;

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

	if(argv[4]!= 0){
		fprintf(stderr, "Improperly formatted input arguments.\n");
		return 0;

	}

	size_t num;
	FILE *fp;
	fp = fopen(argv[3], "r");
	
	int numPrint = strtol(argv[2], NULL, 10);
	  
	LLNode *root;
	root = NULL;

	LLNode *current;
	current = NULL;

	LLNode *temp;
	temp = (LLNode*)malloc(sizeof(LLNode));

	LLNode *newNode;
	newNode = NULL;

	int line = 1;

	
	if(fp == 0){
		fprintf(stderr, "Error. Could not open file.\n");
		return 0;
	}

	else{
		//printf("1\n");
		
		//scans the hexadecimal in the line into a size_t
		//then add to or create a linked list
		while(fscanf(fp, "%zx", &num) != EOF){
			
			//printf("2\n");
			//the inner while loop iterates through the linked list
			//and checks for repeats
			while(temp != NULL){

				//printf("3\n");
				//if there is no root, create new linked list
				if(root == NULL){
					//printf("4\n");
					root = (LLNode*)malloc(sizeof(LLNode));

					root->hex = num;
					root->freq = 1;
					root->line_num = line;
					root->next = NULL;
          root->skip = 0;
					
					current = root;
					temp = root;
					//printf("root: %zx\n", temp->hex);

					//increase line number tracker
					line++;
					list_size++;
					break;
				}
        
			   //check to see if the hex already exists
				if(temp->hex == num){
					//printf("5\n");
					int frequency = temp->freq;
					frequency++;
					temp->freq = frequency;
					
					printf("freq: %zx: %d\n", temp->hex, temp->freq);
					break;
				}

				//if at end of linked list, create a new node
				if(temp->next == NULL){
					//printf("1\n");
					
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
					
					//printf("new node: %zx\n", current->hex);
					
					temp = root;
					
					break;
				}
				
				temp = temp->next;

			}
      

		}

	}
	//printf("6\n");
	
	
	//sort the list	
	temp = root;
	LLNode *output;
		output = (LLNode*)malloc(sizeof(LLNode));
    output =	badSort(temp, output);

  printList(numPrint, output);

  /*
	temp = output;
	printf("list size is %d.\n", list_size);
	while(temp!= NULL){
		//printf("7\n");
		printf("0x%zx: %d.\n", temp->hex, temp->freq);
		temp = temp->next;
	}
  */
	
	fclose(fp);

	return 0;
	

}
