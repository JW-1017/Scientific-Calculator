#include <stdio.h>
#include "ListBaseStack.h"
#include <stdlib.h>

void StackInit(Stack* pstack)
{
	pstack->head = NULL;
	pstack->num = 0;
}

int SSize(Stack* pstack){
	return pstack->num;
}

int SIsEmpty(Stack* pstack)
{
	if (pstack->head == NULL){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

void SPush(Stack* pstack, Data data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));

	newNode->data = data;
	newNode->next = pstack->head;

	pstack->head = newNode;
	pstack->num++;
}

Data SPop(Stack* pstack)
{
	Data rdata;
	Node* rnode;

	if (SIsEmpty(pstack)){
		printf("\nERROR ! ");
		return -1;
	}
	rdata = pstack->head->data;
	rnode = pstack->head;
	pstack->head = pstack->head->next;
	free(rnode);
	pstack->num--;
	return rdata;
}

Data SPeek(Stack* pstack)
{
	if (SIsEmpty(pstack)){
		printf("Stack Memory Error!");
		exit(-1);
	}
	return pstack->head->data;
}