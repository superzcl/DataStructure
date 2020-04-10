#include <stdio.h>
#include <stdlib.h>

#define MaxSize 100
#define ElemType int

typedef struct{
	ElemType data[MaxSize];
	int top; // 栈顶指针 指向栈顶元素 
} SeqStack;

// 栈初始化操作 
void StackInit(SeqStack &s)
{
	s.top = -1; // 初始化栈顶指针为-1为空栈 
}
// 把元素e压入栈s中 
bool StackPush(SeqStack &s, ElemType e)
{
	if(s.top == MaxSize-1){ // 栈满 
		return false;
	}
	s.top ++; // 栈顶指针+1
	s.data[s.top] = e; // 元素入栈 
	return true; 
}
// 弹出栈顶元素
bool StackPop(SeqStack &s) 
{
	if(s.top == -1){
		return false;
	}
	s.top--; // 删除栈顶元素 
	return true;
}

// 取栈顶元素
ElemType GetTop(SeqStack s) 
{
	if(s.top == -1){ // 如果栈空，则非法访问会退出 
		exit(1);
	} 
	return s.data[s.top]; // 返回栈顶元素 
} 

// 判断栈是否为空 
bool StackIsEmpty(const SeqStack &s)
{
	return (s.top == -1) ? true : false;
}
int main() 
{
	SeqStack s; // 定义一个栈 
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
