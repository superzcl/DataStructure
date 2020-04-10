/* ���ò���ͷ���ĵ�����ʵ��ջ */ 

#include <stdio.h>
#include <stdlib.h>

#define ElemType int

typedef struct LinkNode{
	ElemType data;
	struct LinkNode *next;
} LinkNode, *LinkStack; 

// ��ʼ��ջΪ�� 
void InitStack(LinkStack &s)
{
	s = NULL; 
}
// ��ջ���� 
bool StackPush(LinkStack &s, ElemType e)
{
	LinkNode* node = (LinkNode *)malloc(sizeof(LinkNode));
	if(node == NULL){ // �����ڴ�ռ�ʧ�� 
		return false;
	}
	node->data = e;
	node->next = s; 
	s = node; 
	return true;
}
// ��ջ����
bool StackPop(LinkStack &s) 
{
	if(s == NULL){	// ���ջΪ�� 
		return false;
	}
	LinkNode *tmp = s;
	s = s->next;
	free(tmp); // ɾ����ջ����� 
	return true;
}
ElemType GetTop(LinkStack s)
{
	if(s == NULL){ // ջΪ�� 
		exit(1);
	}
	return s->data;	
}

// �ж�ջ�Ƿ�Ϊ�� 
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
