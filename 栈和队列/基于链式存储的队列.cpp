// ���ڴ�ͷ��㵥���� 
#include <stdio.h>
#include <stdlib.h>

#define ElemType int

typedef struct LinkNode{ // ����ÿ��Ԫ�ؽ�� 
	ElemType data;
	struct LinkNode *next;
} LinkNode;

typedef struct{ // ������� 
	LinkNode *front; // ����ָ�� 
	LinkNode *rear; // ��βָ�� 
} LinkQueue;

// ǰ�ú������� 
bool QueueIsEmpty(LinkQueue Q);

// ���д�ͷ����ʼ�� 
void InitQueue(LinkQueue &Q)
{
	// ��ʼ front��rear��ָ��ͷ��㣬����Ϊ�� 
	LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode)); // ����һ����㵱��ͷ��� 
	Q.front = newNode;
	Q.rear = newNode; 
	Q.front->next = NULL; // ͷ�����޽���ʾ����Ϊ�� 
}

bool QueuePush(LinkQueue &Q, ElemType e) 
{
	LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode));
	if(newNode == NULL){ // ����ռ�ʧ�� 
		return false;
	}
	newNode->data = e;
	newNode->next = NULL; // �����Ԫ�غ���Ϊ�� 
	Q.rear->next = newNode; // ���뵽��β 
	Q.rear = newNode; // �޸Ķ�βָ��ָ���µĶ�βԪ�� 
	return true; 
}
bool QueuePop(LinkQueue &Q) 
{
	if(QueueIsEmpty(Q)){
		return false;
	}
	if(Q.front->next == Q.rear){ // �����ɾ��������ֻʣһ��Ԫ�أ����βָ��Ҫָ��ͷ��� 
		Q.rear = Q.front;
	}
	LinkNode *tmp = Q.front->next; // �ȴ�����Ԫ�� 
	Q.front->next = Q.front->next->next; // // �Ӷ�����ɾ������Ԫ�� 
	free(tmp); // �ͷſռ� 
	return true;
}
// ��ȡ����Ԫ�� 
ElemType GetFront(LinkQueue Q)
{
	if(QueueIsEmpty(Q)){
		printf("����Ϊ�գ��Ƿ�����"); 
		exit(1); // ��ֹ���� 
	} 
	return Q.front->next->data; 
}
// �ж϶����Ƿ�Ϊ�� 
bool QueueIsEmpty(LinkQueue Q) 
{
	return (Q.front == Q.rear) ? true : false;
//	return (Q.front->next == NULL) ? true : false; // ����Ҳ���� 
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

bool QueueDestroy(LinkQueue &Q) // ���ٶ��� 
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
