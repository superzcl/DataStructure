#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MaxSize 15
#define ElemType int

typedef struct{
	ElemType data[MaxSize];
	int front; // 队头指针, 指向队首元素 
	int rear; // 队尾指针, 指向队尾下一个元素入队的位置 
} SeqQueue; 

// 函数前置声明 
bool QueueIsFull(SeqQueue Q);
bool QueueIsEmpty(SeqQueue Q);

void QueueInit(SeqQueue &Q)
{
	memset(Q.data, 0, sizeof(Q.data));
	Q.front = Q.rear = 0;
}

// 入队操作 
bool QueuePush(SeqQueue &Q, ElemType e)
{
	if(QueueIsFull(Q)){ // 如果队列已满 
		return false;
	}
	Q.data[Q.rear] = e; // 入队，并让队尾指针后移 
	Q.rear = (Q.rear + 1) % MaxSize;
	return true; 
}
// 出队操作 
bool QueuePop(SeqQueue &Q)
{
	if(QueueIsEmpty(Q)){ // 如果队列为空 
		return false;
	}
	Q.data[Q.front] = -1; // 被删除的元素置为-1 
	Q.front = (Q.front + 1) % MaxSize; // 队首指针后移 
	return true;
}

// 获取队首元素
ElemType QueueGetFront(SeqQueue &Q)
{
	if(QueueIsEmpty(Q)){ // 如果队列为空会出错 
		exit(1);
	}
	return Q.data[Q.front]; 
} 

// 判断队列是否为空 
bool QueueIsEmpty(SeqQueue Q)
{
	return (Q.front == Q.rear ? true : false);
}
// 判断队列是否已满
bool QueueIsFull(SeqQueue Q)
{
//	return (((Q.rear +1) % MaxSize == Q.front) ? true : false);
	if((Q.rear + 1) % MaxSize == Q.front){
		return true;
	}
	return false;
}
int main()
{
	SeqQueue Q;
	QueueInit(Q); 
	for(int i = 0; i < 15; i++){
		QueuePush(Q, i+1);
	}
	QueuePop(Q);
	QueuePush(Q, 15);
	QueuePop(Q);
	QueuePush(Q, 16);
	for(int i = 0; i < MaxSize; i++){
		printf("%d ", Q.data[i]);
	}
	
	return 0;
} 
