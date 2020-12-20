#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
int debugMode=0;
//------------------------------------------------------------------------------
// stackNode declaration
typedef struct stackNode
{
    int xloc, yloc;
    struct stackNode* next;
}stack;
//------------------------------------------------------------------------------
// initializeStack function implementation
void init(stack** head)
{
    *head = NULL;
} // end of initializeStack function
//------------------------------------------------------------------------------
// isStackEmpty function implementation
int isEmpty(stack* head)
{
    if (head == NULL)
        return TRUE;
    else
        return FALSE;
} // end of isStackEmpty function
//------------------------------------------------------------------------------
// pushToStack function implementation
void push(stack * *head, int xpos, int ypos)
{
    if (debugMode == TRUE)
    {
        printf("(%d, %d) pushed into the stack.\n", xpos, ypos);
    }

    stack* newNode = (stack*)malloc(sizeof(stack));
    newNode->xloc = xpos;
    newNode->yloc = ypos;
    newNode->next = *head;
    *head = newNode;
} // end of pushToStack function
//-----------------------------------------------------------------------------
// popFromStack function implementation
void pop(stack * *head)
{
    stack* tempNode = *head;
    if (debugMode == TRUE)
    {
        printf("(%d, %d) popped off the stack.\n", tempNode->xloc, tempNode->yloc);
    }

    if (*head == NULL)
    {
        printf("\nStack is empty! Popping from stack is not possible.\n");
    }
    else
    {
        *head = (*head)->next;
        free(tempNode);
    }
} // end of popFromStack function
//------------------------------------------------------------------------------
// topOnStack function implementation
stack* top(stack * head)
{
    if (isEmpty(head) == TRUE)
        return NULL;
    else
        return head;
} // end of topOnStack function
//------------------------------------------------------------------------------
// resetStack function implementation
void resetStack(stack * *head)
{
    stack* nodePtr, * nextNode;
    nodePtr = *head;

    while (nodePtr != NULL)
    {
        nextNode = nodePtr->next;
        free(nodePtr);
        nodePtr = nextNode;
    }

    *head = NULL;
} // end of resetStack function
//------------------------------------------------------------------------------
//print reverse implementation
void printReverse(stack * *x,stack *temp1) {
     stack* current = *x; 
     
        stack *prev = NULL, *next = NULL; 
  
        while (current != NULL) { 
            next = current->next; 
  	   
            // Rever
            current->next = prev; 
  	    	
            // Move pointers one position ahead. 
            prev = current;
	   
            current = next; 
	  
        } 
        stack* temp = prev;
	*x=prev;
        while(temp!=NULL){
	printf("(%d,%d) ",temp->xloc,temp->yloc);

	temp=temp->next;

	}
	if(debugMode == TRUE){
		printf("\n");
	}
	current =*x;next=NULL; prev=NULL;
	while (current != NULL) {
            next = current->next;

            // Rever
            current->next = prev;

            // Move pointers one position ahead. 
            prev = current;

            current = next;

        }
	*x=prev;

}

//------------------------------------------------------------------------------
typedef struct mazeStruct
{
 char **arr;  /* allows for a maze of size 30x30 plus outer walls */
 int xsize, ysize;
 int xstart, ystart;
 int xend, yend;
 int x,y;
} maze;
//------------------------------------------------------------------------------
int main (int argc, char **argv)
{
  maze m1;
  maze track;
  int xpos, ypos;
  int i,j;

  FILE *src;
  char* str = "";
  if (argc < 2)
    {
        printf("Arguments at command-line are not found!\n");
        exit(1);
    }

    for (int k = 1; k < argc; k++)
    {
        if (strcmp(argv[k], "-d") == 0)
        {
            debugMode = TRUE;
        }
        else
        {
            str = argv[k];
        }
    }
    argv[1] = str;

    if ((src = fopen(argv[1], "r")) == NULL)
    {
        printf("%s file cannot be opened!: \n", argv[1]);
        exit(1);
    }
  /* read in the size, starting and ending positions in the maze */
  fscanf (src, "%d %d", &m1.xsize, &m1.ysize);
  if(m1.xsize <=0 || m1.ysize <= 0){
      printf("Maze sizes must be greater than 0.");
      exit(-1);
  }
  m1.arr = (char **)malloc(sizeof(char *) * (m1.xsize + 2));
   track.arr = (int **)malloc(sizeof(int *) * (m1.xsize + 2));

   
   for (int i = 0; i < m1.xsize + 2; i++)
   {
       m1.arr[i] = (char *)malloc(sizeof(char) * (m1.ysize + 2));
       track.arr[i] = (int *)malloc(sizeof(int) * (m1.ysize + 2));
   }


  fscanf (src, "%d %d", &m1.xstart, &m1.ystart);
  fscanf (src, "%d %d", &m1.xend, &m1.yend);
  
  /* initialize the maze to empty */
  for (i = 0; i < m1.xsize+2; i++)
     for (j = 0; j < m1.ysize+2; j++)
       m1.arr[i][j] = '.';

 // read the coins and block
  char read;
  int xfill;
  int yfill;
  //error check invalid file
  if(fscanf (src, "%d %d %c ", &xfill, &yfill,&read) == EOF){
      printf("Invalid data file.");
      exit(-1);
  }
  if (read == 'c') {
                  m1.arr[xfill][yfill] = 'C';
    }
  else if (read == 'b') {
                   m1.arr[xfill][yfill] = '*';
    }
        
  /* print them out to verify the input */
  printf ("size: %d, %d\n", m1.xsize, m1.ysize);
  if(m1.xstart > m1.xsize || m1.ystart > m1.ysize) {
	  printf("Start/End position outside of maze range.");
	  exit(-1);
  }
  
  printf ("start: %d, %d\n", m1.xstart, m1.ystart);
  if(m1.xend > m1.xsize || m1.yend > m1.ysize) {
	  printf("Start/End position outside of maze range.");
	  exit(-1);
  }
  
  printf ("end: %d, %d\n", m1.xend, m1.yend);
  
  while( fscanf (src, "%d %d %c ", &xfill, &yfill,&read)!=EOF){
          if (xfill > m1.xsize || yfill > m1.ysize) {
              printf("Invalid coordinates: outside of maze range.\n");
          }
          if(xfill==m1.xstart && m1.ystart == yfill){
              printf("Invalid coordinates: attempting to block start/end position.\n");
          }
          if(yfill==m1.yend  && m1.xend == xfill){
              printf("Invalid coordinates: attempting to block start/end position.\n");
          }
          if(read != 'c' && read != 'b'){
              printf("Invalid type: type is not recognized.\n");
          }
          else if (read == 'c') {
                  m1.arr[xfill][yfill] = 'C';

          }
          else if (read == 'b') {
                   m1.arr[xfill][yfill] = '*';
          }
  }
  

  //unvisited
   for (i = 0; i < m1.xsize; i++) {
	 for (j = 0; j < m1.ysize; j++) {
		 track.arr[i][j] = 'U';
		 }
   }
 
  /* mark the borders of the maze with *'s */
  for (i=0; i < m1.xsize+2; i++) {
     m1.arr[i][0] = '*';
     m1.arr[i][m1.ysize+1] = '*';
    }
  for (i=0; i < m1.ysize+2; i++) {
     m1.arr[0][i] = '*';
     m1.arr[m1.xsize+1][i] = '*';
    }

  /* mark the starting and ending positions in the maze */
  m1.arr[m1.xstart][m1.ystart] = 's';
  m1.arr[m1.xend][m1.yend] = 'e';
		  
  /*This code will only read the first three lines */
  /*Complete this code by reading the rest of the input
    and placing blocked and coin positions. */
  /* Blocked positions are marked with 'b' in the input file
     They should be marked by * in the maze */

  /*Coin positions are marked by 'c' in the input file
    They should be marked by C in the maze*/
 

  /*Close the file*/
   fclose(src);

  /* print out the initial maze */
  for (i = 0; i < m1.xsize+2; i++)
    {
     for (j = 0; j < m1.ysize+2; j++)
       printf ("%c", m1.arr[i][j]);
     printf("\n");
    }

  //push start pos
  stack* s1;
  init(&s1);
  push(&s1,m1.xstart,m1.ystart);
  int coins =0;

  //start is visited
  track.arr[m1.xstart][m1.ystart]='V';
  int size=0;
//while loop
  while(!isEmpty(s1)){
         stack *topvalue = top(s1);
         size++;
         if(topvalue->xloc == m1.xend && topvalue->yloc==m1.yend) {
                 break;
         }
	 else  if(m1.arr[topvalue->xloc+1][topvalue->yloc] != '*' && track.arr[topvalue->xloc+1][topvalue->yloc] != 'V') {
                 push(&s1,topvalue->xloc+1,topvalue->yloc);
                 track.arr[topvalue->xloc+1][topvalue->yloc] = 'V';
                 if(m1.arr[topvalue->xloc+1][topvalue->yloc] == 'C') {
                         coins++;
                 }
         }
	 else  if(m1.arr[topvalue->xloc][topvalue->yloc+1] != '*' && track.arr[topvalue->xloc][topvalue->yloc+1] != 'V') {
                 push(&s1,topvalue->xloc,topvalue->yloc+1);
                 track.arr[topvalue->xloc][topvalue->yloc+1] = 'V';
                 if(m1.arr[topvalue->xloc][topvalue->yloc+1] == 'C') {
                         coins++;
                 }
         }
	 else  if(m1.arr[topvalue->xloc-1][topvalue->yloc] != '*' && track.arr[topvalue->xloc-1][topvalue->yloc] != 'V') {
                 push(&s1,topvalue->xloc-1,topvalue->yloc);
                 track.arr[topvalue->xloc-1][topvalue->yloc] = 'V';
                 if(m1.arr[topvalue->xloc-1][topvalue->yloc] == 'C') {
                         coins++;
                 }
         }
	 else  if(m1.arr[topvalue->xloc][topvalue->yloc-1] != '*' && track.arr[topvalue->xloc][topvalue->yloc-1] != 'V') {
                 push(&s1,topvalue->xloc,topvalue->yloc-1);
                 track.arr[topvalue->xloc][topvalue->yloc-1] = 'V';
                 if(m1.arr[topvalue->xloc][topvalue->yloc-1] == 'C') {
                         coins++;
                 }
         }
	 else {
         pop(&s1);
	 }
  }
  stack* temp=s1;
  if(isEmpty(s1)) {
	  printf("This maze has no solution.");
  }
  else{
      if(debugMode==TRUE){
          printf("\n");
      }
	  printf("The maze has a solution.\n");
	  printf("The amount of coins collected: %d\n",coins);
	  printf("The path from start to end:\n");
	  printReverse(&s1,temp);
	  while(!isEmpty(s1)){
	      pop(&s1);
	  }
  }
 free(track.arr);
free(m1.arr); 
}
