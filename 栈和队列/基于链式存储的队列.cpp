// 基于带头结点单链表 
#include <stdio.h>
#include <stdlib.h>

#define ElemType int

typedef struct LinkNode{ // 定义每个元素结点 
	ElemType data;
	struct LinkNode *next;
} LinkNode;

typedef struct{ // 定义队列 
	LinkNode *front; // 队首指针 
	LinkNode *rear; // 队尾指针 
} LinkQueue;

// 前置函数声明 
bool QueueIsEmpty(LinkQueue Q);

// 队列带头结点初始化 
void InitQueue(LinkQueue &Q)
{
	// 初始 front和rear都指向头结点，队列为空 
	LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode)); // 申请一个结点当作头结点 
	Q.front = newNode;
	Q.rear = newNode; 
	Q.front->next = NULL; // 头结点后无结点表示队列为空 
}

bool QueuePush(LinkQueue &Q, ElemType e) 
{
	LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode));
	if(newNode == NULL){ // 申请空间失败 
		return false;
	}
	newNode->data = e;
	newNode->next = NULL; // 新入队元素后面为空 
	Q.rear->next = newNode; // 插入到队尾 
	Q.rear = newNode; // 修改队尾指针指向新的队尾元素 
	return true; 
}
bool QueuePop(LinkQueue &Q) 
{
	if(QueueIsEmpty(Q)){
		return false;
	}
	if(Q.front->next == Q.rear){ // 如果被删除队列中只剩一个元素，则队尾指针要指向头结点 
		Q.rear = Q.front;
	}
	LinkNode *tmp = Q.front->next; // 等待出队元素 
	Q.front->next = Q.front->next->next; // // 从队列中删除出队元素 
	free(tmp); // 释放空间 
	return true;
}
// 获取队首元素 
ElemType GetFront(LinkQueue Q)
{
	if(QueueIsEmpty(Q)){
		printf("队列为空，非法访问"); 
		exit(1); // 终止程序 
	} 
	return Q.front->next->data; 
}
// 判断队列是否为空 
bool QueueIsEmpty(LinkQueue Q) 
{
	return (Q.front == Q.rear) ? true : false;
//	return (Q.front->next == NULL) ? true : false; // 这样也可以 
}
int QueueSize(LinkQueue Q)
{
	int length = 0;
	LinkNode *q = Q.front;
	while(q->next != NULL){
		q = q->next;
		length++;
	}
	return length;
}

bool QueueDestroy(LinkQueue &Q) // 销毁队列 
{
	while(Q.front != NULL){
		LinkNode *tmp = Q.front;
		Q.front = Q.front->next;
		free(tmp);
	}
	Q.front = Q.rear = NULL;
	return true;
}

int main() 
{
	LinkQueue Q;
	InitQueue(Q);
	for(int i = 1; i <= 10; i++){
		QueuePush(Q, i);
	} 
	printf("length = %d\n", QueueSize(Q));
	for(int i = 0; i < 10; i++){
		printf("%d\n", GetFront(Q));
		QueuePop(Q);
	}
	printf("length = %d\n", QueueSize(Q));
	GetFront(Q);
	
	return 0;
}
