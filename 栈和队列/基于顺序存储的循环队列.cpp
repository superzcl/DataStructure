#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MaxSize 15
#define ElemType int

typedef struct{
	ElemType data[MaxSize];
	int front; // ��ͷָ��, ָ�����Ԫ�� 
	int rear; // ��βָ��, ָ���β��һ��Ԫ����ӵ�λ�� 
} SeqQueue; 

// ����ǰ������ 
bool QueueIsFull(SeqQueue Q);
bool QueueIsEmpty(SeqQueue Q);

void QueueInit(SeqQueue &Q)
{
	memset(Q.data, 0, sizeof(Q.data));
	Q.front = Q.rear = 0;
}

// ��Ӳ��� 
bool QueuePush(SeqQueue &Q, ElemType e)
{
	if(QueueIsFull(Q)){ // ����������� 
		return false;
	}
	Q.data[Q.rear] = e; // ��ӣ����ö�βָ����� 
	Q.rear = (Q.rear + 1) % MaxSize;
	return true; 
}
// ���Ӳ��� 
bool QueuePop(SeqQueue &Q)
{
	if(QueueIsEmpty(Q)){ // �������Ϊ�� 
		return false;
	}
	Q.data[Q.front] = -1; // ��ɾ����Ԫ����Ϊ-1 
	Q.front = (Q.front + 1) % MaxSize; // ����ָ����� 
	return true;
}

// ��ȡ����Ԫ��
ElemType QueueGetFront(SeqQueue &Q)
{
	if(QueueIsEmpty(Q)){ // �������Ϊ�ջ���� 
		exit(1);
	}
	return Q.data[Q.front]; 
} 

// �ж϶����Ƿ�Ϊ�� 
bool QueueIsEmpty(SeqQueue Q)
{
	return (Q.front == Q.rear ? true : false);
}
// �ж϶����Ƿ�����
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
