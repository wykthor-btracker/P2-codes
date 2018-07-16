#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct pilha pilha;
typedef struct pilha 
{
	pilha *prox;
	int val;
}pilha;

pilha *novaPilha(int val)
{
	pilha *novaPilha = malloc(sizeof(pilha));
	novaPilha->prox = NULL;
	novaPilha->val = val;
	return novaPilha;
}
int pop(pilha **Mpilha)
{
	if(*Mpilha!=NULL)
	{
		int val = (*Mpilha)->val;
		*Mpilha = (*Mpilha)->prox;
		return val;
	}
	else
	{
		return NULL;
	}
}
pilha *push(pilha *Mpilha, int val)
{
	pilha *nPilha = novaPilha(val);
	nPilha->prox = Mpilha;
	return nPilha;
}

pilha *intToBinary(int val)
{
	pilha *Num = novaPilha(val%2);
	while(val != 0)
	{
		val = val/2;
		Num = push(Num,val%2);
	}
	return Num;
}
int tamanhoDaPilha(pilha *stack)
{
	int tamanho = 0;
	while(stack!=NULL)
	{
		tamanho++;
		stack = stack->prox;
	}
	return tamanho-1;
}
int binaryToInt(pilha **stack)
{
	pilha *newStack = novaPilha(0);
	int val,i;
	while(*stack!=NULL)
	{
		val = pop(stack);
		if(val!=NULL) newStack = push(newStack,val);
	}
	val = 0;
	for(i=tamanhoDaPilha(newStack);i>=0;i--)
	{
		val+=pop(&newStack)*pow(2,i);
	}
	return val;
}

int peek(pilha *stack)
{
	return(stack->val);
}
void mostraPilha(pilha *stack)
{
	while(stack != NULL)
	{
		printf(" %d ",peek(stack));
		stack = stack->prox;
	}
}
int main()
{
	pilha *bin = intToBinary(5);
	printf("%d",binaryToInt(&bin));
	return 0;
}
