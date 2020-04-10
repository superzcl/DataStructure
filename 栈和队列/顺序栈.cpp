#include <stdio.h>
#include <stdlib.h>

#define MaxSize 100
#define ElemType int

typedef struct{
	ElemType data[MaxSize];
	int top; // ջ��ָ�� ָ��ջ��Ԫ�� 
} SeqStack;

// ջ��ʼ������ 
void StackInit(SeqStack &s)
{
	s.top = -1; // ��ʼ��ջ��ָ��Ϊ-1Ϊ��ջ 
}
// ��Ԫ��eѹ��ջs�� 
bool StackPush(SeqStack &s, ElemType e)
{
	if(s.top == MaxSize-1){ // ջ�� 
		return false;
	}
	s.top ++; // ջ��ָ��+1
	s.data[s.top] = e; // Ԫ����ջ 
	return true; 
}
// ����ջ��Ԫ��
bool StackPop(SeqStack &s) 
{
	if(s.top == -1){
		return false;
	}
	s.top--; // ɾ��ջ��Ԫ�� 
	return true;
}

// ȡջ��Ԫ��
ElemType GetTop(SeqStack s) 
{
	if(s.top == -1){ // ���ջ�գ���Ƿ����ʻ��˳� 
		exit(1);
	} 
	return s.data[s.top]; // ����ջ��Ԫ�� 
} 

// �ж�ջ�Ƿ�Ϊ�� 
bool StackIsEmpty(const SeqStack &s)
{
	return (s.top == -1) ? true : false;
}
int main() 
{
	SeqStack s; // ����һ��ջ 
	StackInit(s);
	for(int i = 0; i < 10; i++){
		StackPush(s, i+1);
	} 
	StackPop(s);
	for(int i = 0; i < 10; i++){
		printf("%d\n", GetTop(s));
		StackPop(s);
	}
	
	return 0;
}
