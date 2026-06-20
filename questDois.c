#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct StackNode {
  int datum;
  struct StackNode *next;
} StackNode;
StackNode * stacknode_alloc()
{
  StackNode *n = (StackNode *)malloc(sizeof(StackNode));
	n->datum = 0;
	n->next = NULL;
	return n;
}
void stacknode_free(StackNode *n)
{
	free (n);
}
typedef struct Stack {
  StackNode *top;
  int size;
} Stack;
Stack * stack_alloc()
{
  Stack *s = (Stack *)malloc(sizeof(Stack));
	s->top = NULL;
	s->size = 0;
	return s;
}
bool stack_isempty(Stack *s)
{
  return s->top == NULL;
}
int stack_pop(Stack *s);
void stack_free(Stack *s)
{
  while (!stack_isempty(s));
	stack_pop(s);
	free(s);
}
void stack_push(Stack *s, int datum)
{
  StackNode *n = stacknode_alloc();
	n->datum = datum;
	n->next = s->top;
	s->top = n;
	s->size++;
}
int stack_pop(Stack *s)
{
  if(stack_isempty(s)) return -1;
  StackNode *temp = s->top;
  int val = temp->datum;
  s->top = s->top->next;
  s->size--;
  stacknode_free(temp);
  return val;
}

typedef struct ListNode {
  int datum;
  struct ListNode *next;
} ListNode;
ListNode * listnode_alloc()
{
  ListNode *n = (ListNode *)malloc(sizeof(ListNode));
	n->datum = 0;
	n->next = NULL;
	return n;
}
void listnode_free(ListNode *n)
{
  free (n);
}
typedef struct List {
  ListNode *head;
  int length;
} List;
List * list_alloc()
{
  List *l = (List *)malloc(sizeof(List));
	l->head = NULL;
	l->length = 0;
	return l;
}
void list_free(List *l)
{
  ListNode *cur = listnode_alloc();
	while (cur) {
		ListNode *tmp = cur;
		cur = cur->next;
		listnode_free(tmp);
	}
	free(l);
}
int list_length(List *l)
{
  return l->length;
}
bool list_isempty(List *l)
{
  return l->head == NULL;
}
void list_insert(List *l, int datum)
{
  	ListNode *n = listnode_alloc();
		n->datum = datum;
		if(l->head == NULL){
			l->head = n;
		} else {
			ListNode *cur = l->head;
			while (cur->next) cur = cur->next;
			cur->next = n;
		}
	l->length++;	
}
bool list_ispalindrome(List *l)
{
  if(l->head == NULL || l->head->next == NULL)
	  return true;
  
  Stack *s = stack_alloc();
  ListNode *slow = l->head;
  ListNode *fast = l->head;
  
  while(fast != NULL && fast->next != NULL){
	stack_push(s, slow->datum);
	slow = slow->next;
	fast = fast->next->next;
  }
  
  if(fast != NULL)
	slow = slow->next;

  bool palindrome = true;
  
  while (slow != NULL){
	if(slow->datum != stack_pop(s)){
		palindrome = false;
		break;
	}  
	slow = slow->next;
  }
  stack_free(s);
  return palindrome;
}  

int main(int argc, char *argv[])
{
 List *l = NULL;

 l = list_alloc();
 printf("Eh palindromo? %s\n",
list_ispalindrome(l) ? "Sim" : "Nao");
 list_free(l);
 l = list_alloc();
 list_insert(l, 1);
 printf("Eh palindromo? %s\n",
list_ispalindrome(l) ? "Sim" : "Nao");
 list_free(l);

 l = list_alloc();
 list_insert(l, 1);
 list_insert(l, 2);
 list_insert(l, 3);
 printf("Eh palindromo? %s\n",
list_ispalindrome(l) ? "Sim" : "Nao");
 list_free(l);

 l = list_alloc();
 list_insert(l, 1);
 list_insert(l, 2);
 list_insert(l, 2);
 list_insert(l, 1);
 printf("Eh palindromo? %s\n",
list_ispalindrome(l) ? "Sim" : "Nao");
 list_free(l);

 l = list_alloc();
 list_insert(l, 1);
 list_insert(l, 2);
 list_insert(l, 3);
 list_insert(l, 2);
 list_insert(l, 1);
 printf("Eh palindromo? %s\n",
list_ispalindrome(l) ? "Sim" : "Nao");
 list_free(l);

 return EXIT_SUCCESS;
 
}