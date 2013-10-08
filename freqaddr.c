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
  
  LLNode *root;
    root = NULL;

  LLNode *current;
    current = NULL;

  LLNode *temp;
    temp = NULL;

  LLNode *newNode;
    newNode = NULL;

  int line = 1;
  
  if(fp == 0){
    printf("Could not open file.\n");
    return 0;

  }
  
  else{
    while(fscanf(fp, "%zx", num) != EOF){
      //scans the hexadecimal in the line into a size_t
      //then add to or create a linked list
      //
      //the inner while loop iterates through the linked list
      //and checks for repeats
      while(temp != NULL){

        //if there is no root, create new linked list
        if(root == NULL){
          root = (LLNode*)malloc(sizeof(LLNode));

          root->hex = num;
          root->freq = 1;
          root->line_num = line;
          root->next = NULL;
          current = root;

         //increase line number tracker
         line++;
         break;
        }
        
        //check to see if the hex already exists
        if(temp->hex == num){
          int frequency = temp->freq;
          frequency++;
          temp->freq = frequency;
          break;
        }

        //if at end of linked list, create a new node
        if(temp->next == NULL){
          
          newNode = (LLNode*)malloc(sizeof(LLNode));

          newNode->hex = num;
          newNode->freq = 1;
          newNode->line_num = line;
          newNode->next = NULL;
          current->next = newNode;
            line++;
          current = newNode;
        }

      }
      

    }

  }

  temp = root;

  while(temp!= NULL){
    printf("%zx: %d", temp->hex, temp->freq);

  }
  




}
