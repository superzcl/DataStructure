#include <stdio.h>
#include <stdlib.h>

#define ElemType int

typedef struct DNode{
	ElemType data;
	struct DNode *prior; // ָ��ǰ����� 
	struct DNode *next;  // ָ���̽�� 
}DNode, *DLinkList; 
// ˫������ĳ�ʼ�� 
bool InitDLinkList(DLinkList &L)
{
	L = (DNode *)malloc(sizeof(DNode)); // ����ͷ��� 
	if(L == NULL) return false;	// �ڴ�����ʧ�� 
	L->prior = NULL;
	L->next = NULL;
	return true; 
}
// ˫���� ����ָ��idxλ�õĽ�� 
DNode* GetNode(DLinkList &L, int idx) 
{
	if(L == NULL){
		return NULL;
	}
	DNode *p = L;
	int j = 0;
	while(p->next != NULL && j < idx){ // �ҵ���idx����� 
		p = p->next;
		j++;
	}
	return p;
}
// ˫������ָ��p���֮�����s��� 
bool InsertNextNode(DNode *p, DNode *s)
{
	
	if(p == NULL || s == NULL){ // �Ƿ����� 
		return false;
	}
	
	s->next = p->next;
	if(p->next != NULL){ // ���p�к�̽�� 
		p->next->prior = s;
	}
	s->prior = p;
	p->next = s;
	return true;
}
// ��ָ��λ�ò�����p
bool ListInsert(DLinkList &L, int idx, DNode *p)
{
	if(idx < 1){
		return false;
	}

	DNode *s = GetNode(L, idx-1);	// ��ȡ��idx-1����� 
	if(s == NULL){
		return false;
	}
//	printf("Here\n");
	return InsertNextNode(s, p); // �ڵ�idx-1֮�����p��� 
}
// ˫���� ɾ��ָ��P���ĺ�̽��
bool DeleteNextNode(DNode *p)
{
	if(p == NULL || p->next == NULL){
		return false;
	}
	DNode *s = p->next; // ��ɾ����� 
	if(s->next != NULL){
		s->next->prior = p;
	}
	p->next = s->next;
	free(s);
	return true;
}
// ����˫����
bool DestroyList(DLinkList &L) 
{
	while(L->next != NULL){
		DeleteNextNode(L);
	} 
	free(L);
	return true;
}

bool IsEmpty(DLinkList L)
{
	return (L->next == NULL ? true : false);
}
// ͷ�巨����˫����
DLinkList ListHeadInsert(DLinkList &L) 
{
	if(L != NULL){
		DestroyList(L);
	}
	L = (DNode *)malloc(sizeof(DNode));
	L->next = L->prior = NULL;
	
	ElemType e;
	while(scanf("%d", &e) != EOF){
		DNode *newnode = (DNode *)malloc(sizeof(DNode));
		newnode->data = e;
		newnode->next = L->next;
		if(L->next != NULL){ // ���ͷ����к�̽�� 
			L->next->prior = newnode;
		}
		newnode->prior = L;
		L->next = newnode;
	}
	return L;
}
// β�巨����˫����
DLinkList ListTailInsert(DLinkList &L) 
{
//	if(L != NULL){
//		DestroyList(L);
//	}
//	L = (DNode *)malloc(sizeof(DNode));
//	L->prior = L->next = NULL;
	ElemType e;
	DNode *tail = L;
	while(tail->next != NULL){
		tail = tail->next;
	}
	while(scanf("%d", &e) != EOF){
		DNode *newnode = (DNode *)malloc(sizeof(DNode));
		newnode->data = e;
		newnode->next = NULL;
		newnode->prior = tail;
		tail->next = newnode;
		tail = newnode;
	}
	return L;
}

int main()
{
	DLinkList L;
	InitDLinkList(L);	
	for(int i = 0; i < 10; i++){
		DNode *node = (DNode *)malloc(sizeof(DNode));
		node->data = i+1;
		ListInsert(L, i+1, node);
	}
	DNode *node = (DNode *)malloc(sizeof(DNode));
	node->data = 10;
	InsertNextNode(L, node); 
	DeleteNextNode(L); 

//	ListHeadInsert(L);
	ListTailInsert(L);
	DNode *p = L->next;
	int i = 1;
	while(p != NULL){
		printf("��%d������ֵ�ǣ�%d\n", i++, p->data);
		p = p->next;
	} 
	return 0;
}
