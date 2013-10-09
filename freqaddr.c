#include<stdio.h>
#include<stdlib.h>
#include "freqaddr.h"

int list_size = 0;


int badSort(LLNode *head, LLNode *nHead){
	//performs selection sort on a linked list
	
	if(head == NULL){
		return NULL;
	}

	LLNode *temp;
		temp = head;
		
	LLNode *temp2;
		temp2 = NULL;
	LLNode *maxNode;
		maxNode = NULL;
	LLNode *maxPrev;
		maxPrev = NULL;
		
	//current in new list being built
	LLNode *current;
		current = NULL;
	
	int lSize = list_size;
	
	//sets variable to hold max
	
	
	int i;
	while(temp != NULL){

		printf("1\n");
		printf("temp is %zx.\n", temp->hex);
		//resets variable to hold max
		int maxFreq = 0;
		
		temp2 = head;
		while(temp2 != NULL){
			printf("2\n");
			if(temp2->next != NULL && temp2->next->freq > maxFreq){
				maxFreq = temp2->next->freq;
				maxNode = temp2->next;
				maxPrev = temp2;
			}
			temp2 = temp2->next;
		}
		printf("3\n");
		printf("max is %zx with %d.\n", maxNode->hex, maxFreq);
		//adds max to new linked list.
		//if no list exists, create one.
		if(nHead->hex == NULL){
			printf("4\n");
			nHead = maxNode;
			nHead->next = NULL;
			current = nHead;
			printf("4.5\n");
		}
		//new list does exist.
		//add to end of new list.
		//delete max node from old list.
		printf("5\n");
		else{
			printf("6\n");
			current->next = maxNode;
			maxPrev->next = maxPrev->next->next;
			current = maxNode;
		}
		printf("7\n");
		if(temp->next == NULL){
			printf("8\n");
			current->next = temp;
			break;
		}
		temp = head;
	}
	return 0;
}


int listSort(LLNode *head){
	//performs insertion sort on a linked list
	
	if(head==NULL){
		return 1;
	}
	
	LLNode *current;
	LLNode *temp;
	LLNode *insert;
	current = head;
	temp = head;
	insert = NULL;
	
	//sets up freq to compare to
	//is this necessary??
	int max = 0;
	
	//special case if linked list is only 1 node long
	if(head->next ==NULL){
		printf("1\n");
		return 0;
	}
	
	//check if head->next->freq is greater first
	if(head->next->freq > head->freq){
		printf("2\n");
		insert = head->next;
		//printf("insert is %zx\n", insert->hex);
		head->next = head->next->next;
			/*if(head->next ==NULL){
				printf("head->next is null.");
			}else{
			printf("head->next is %zx\n", head->next->hex);
			}
			*/
		head = head->next;
		//printf("head is %zx\n", head->hex);
	}
	
	/*
	int atHead = 0;
	while(current!= NULL){
		printf("0x%zx: %d\n", temp->hex, temp->freq);
		int cfreq = current->next->freq;
		while(temp!=NULL){
			
			//should work even if there exists word with same frequency
			if(temp->freq > cfreq){
				insert = current->next;
				if(atHead=0){
					current->next = current->next->next;
					insert->next = head;
					head = insert;
					temp = head;
					//atHead++ not necessary since breaking
					break;
				}
				
				
			}
			athead++;
			temp = temp->next;
		}
		
		
		
		current = current->next;
	}
	*/
	return 0;
}

int main(int argc, char* argv[]){

	if(argv[4]!= 0){
		printf("Improperly formatted input arguments.");
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
		printf("Could not open file.\n");
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
					
					current = root;
					temp = root;
					printf("root: %zx\n", temp->hex);

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
					newNode->next = NULL;
					
					current->next = newNode;
					line++;
					list_size++;
					current = newNode;
					
					printf("new node: %zx\n", current->hex);
					
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
	badSort(temp, output);
	
	temp = root;
	printf("list size is %d.\n", list_size);
	while(temp!= NULL){
		//printf("7\n");
		printf("0x%zx: %d.\n", temp->hex, temp->freq);
		temp = temp->next;
	}
	
	fclose(fp);

	return 0;
	

}
