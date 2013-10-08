#ifndef FREQADDR_H_
#define FREQADDR_H_


typedef struct Node{
	char *wrd;
	long int address;
	struct Node *next;
	int freq;
}Node;
 
typedef struct hNode{
  char *wrd;
  long int address;
  struct Node left;
  struct Node right;
  struct Node parent;
  int freq;

}hNode;


typedef struct LLNode{
  size_t hex;
  int freq;
  int line_num;
  struct LLNode *next;
}LLNode;




#endif
