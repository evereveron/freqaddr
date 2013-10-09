#include<stdio.h>
#include<stdlib.h>
#include "freqaddr.h"


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
	
	temp = root;
	
	while(temp!= NULL){
		printf("7\n");
		printf("%zx: %d\n", temp->hex, temp->freq);
		temp = temp->next;
	}
	
	fclose(fp);

	return 0;
	

}
