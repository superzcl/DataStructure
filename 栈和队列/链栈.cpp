/* 采用不带头结点的单链表实现栈 */ 

#include <stdio.h>
#include <stdlib.h>

#define ElemType int

typedef struct LinkNode{
	ElemType data;
	struct LinkNode *next;
} LinkNode, *LinkStack; 

// 初始化栈为空 
void InitStack(LinkStack &s)
{
	s = NULL; 
}
// 入栈操作 
bool StackPush(LinkStack &s, ElemType e)
{
	LinkNode* node = (LinkNode *)malloc(sizeof(LinkNode));
	if(node == NULL){ // 申请内存空间失败 
		return false;
	}
	node->data = e;
	node->next = s; 
	s = node; 
	return true;
}
// 出栈操作
bool StackPop(LinkStack &s) 
{
	if(s == NULL){	// 如果栈为空 
		return false;
	}
	LinkNode *tmp = s;
	s = s->next;
	free(tmp); // 删除此栈顶结点 
	return true;
}
ElemType GetTop(LinkStack s)
{
	if(s == NULL){ // 栈为空 
		exit(1);
	}
	return s->data;	
}

// 判断栈是否为空 
bool StackIsEmpty(LinkStack &s)
{
	return (s == NULL) ? true : false; 
}

int main()
{
	LinkStack s;
	InitStack(s);
	for(int i = 0; i < 10; i++){
		StackPush(s, i+1);
	}
	
	for(int i = 0; i < 10; i++){
		printf("%d\n", GetTop(s));
		StackPop(s);
	}
	printf("\n%d\n", StackIsEmpty(s));
	return 0;
}
