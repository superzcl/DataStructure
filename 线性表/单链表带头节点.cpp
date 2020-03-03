#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ElemType int

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

// ��ͷ�ڵ�ĳ�ʼ��
bool InitList(LinkList &headList)
{
	headList = (LNode*) malloc(sizeof(LNode));
	if(headList == NULL){
		return false;
	}
	headList->next = NULL;
	return true;
}
// ��λ���� 
LNode* GetElem(LinkList headList, int i)
{
	if(i < 0){
		return NULL;
	}
	LNode *p = headList;
	int j = 0;
	while(p != NULL && j < i){
		p = p->next;
		j++;
	}
	return p;
}
// ��ֵ����
LNode* LocateElem(LinkList headList, ElemType e)
{
	LNode *p = headList->next;
	while(p != NULL && p->data != e){
		p = p ->next;
	}
	return p;
}
// ��ָ�����p�����Ԫ��e
bool InsertNextNode(LNode *p, ElemType e)
{
	if(p == NULL){
		return false;
	}
	LNode *node = (LNode *)malloc(sizeof(LNode));
	if(node == NULL){ // �ڴ����ʧ�� 
		return false;
	}
	node->data = e;
	node->next = p->next; // ����node�ĺ�̽�� 
	p->next = node; // ����node��ǰ����� 
//	printf("%d\n", p->next->data);
	return true;
}
// �ڵ�idx��λ���ϲ���e 
bool ListInsert(LinkList &headList, int idx, ElemType e)
{
	if(idx < 1){
		return false;
	} 
	LNode *p = headList;	// headListָ��ͷ��� ͷ��㲻������ 
	int j = 0;	// ��ǰpָ��ڼ������ 
	while(p != NULL && j < idx - 1){ // ѭ���ҵ���idx-1���ڵ� 
		p = p->next;
		j++;
	}  
	return InsertNextNode(p, e); // ������ָ���������Ԫ�صĺ��� 
}
// ��ָ�����p֮ǰ����Ԫ��e  O(n)���� 
bool InsertPriorNode(LinkList &headList, LNode *p, ElemType e)
{
	LNode *tmp = headList;
	while(tmp != NULL){	// ѭ���ҵ�p����ǰһ����� 
		if(tmp->next == p){
			break;
		}
		tmp = tmp->next;
	}
	if(tmp == NULL){
		return false;
	} 
	LNode *node = (LNode *)malloc(sizeof(LNode));
	if(node == NULL){
		return false;
	}
	node->data = e;
	node->next = p;
	tmp->next = node;
	return true;
}
// ��ָ�����p֮ǰ����Ԫ��e  O(1)���� 
bool InsertPriorNode(LNode *p, ElemType e)
{
	if(p == NULL){
		return false;
	}
	LNode *node = (LNode *)malloc(sizeof(LNode));
	if(node == NULL){
		return false;
	} 
	// �ƶ����� ʵ�ֲ����� 
	node->data = p->data;	// ������Ľ���滻����ǰ��p��� 
	p->data = e; 	// Ȼ���p�������ݸ���������p�ͳ�����ǰp��ǰ����� 
	node->next = p->next; // ���� 
	p->next = node;
	return true;
}
// ɾ������ ɾ����idx��λ�õ�Ԫ��
bool ListDelete(LinkList &headList, int idx)
{
	if(idx < 0){
		return false;
	}
	LNode *p = headList;
	for(int i = 0; i < idx-1 && p != NULL; i++){ // ѭ���ҵ���i-1����� 
		p = p->next;
	}
	if(p == NULL || p->next == NULL){ // ���idx��Ч 
		return false;
	}
	LNode *tmp = p->next; // tmpΪ��ǰҪɾ���Ľ�� 
	p->next = tmp->next;
	free(tmp); 
	return true; 
}
// ɾ��ָ����� O(n)����
bool DeleteNode(LinkList &headList, LNode *p)
{
	if(p == NULL){
		return false;
	}
	LNode *tmp = headList;
	while(tmp->next != p){	// ѭ���ҵ���ɾ������ǰ����� 
		tmp = tmp->next;
	}
	tmp->next = p->next;
	free(p);
	return true;
}
// ɾ��ָ����� O(1)����
// ȱ�����޷�ɾ�����һ����� 
bool DeleteNode(LNode *p)
{
	if(p == NULL || p->next == NULL){ // ���p�����ڻ�p�����һ����� 
		return false;
	}
	LNode *q = p->next;	// q�Ǳ�ɾ�����p�ĺ�̽�� 
	p->data = q->data;	// ��p���q��� 
	p->next = q->next;	// p����q�ĺ�̽���������ȼ���ɾ����p��� 
	free(q);
	return true;
}


// ��ͷ�ڵ���пշ���
bool IsEmpty(LinkList &headList)
{
	return (headList->next == NULL);
}
// ��� 
int Length(LinkList headList)
{
	LNode *p = headList;
	int len = 0;
	while(p->next != NULL){
		p = p->next;
		len++;
	}
	return len;
}
// β�巨����������
LinkList ListTailInsert(LinkList &headList)
{
	headList = (LinkList)malloc(sizeof(LNode)); // ����ͷ���
	headList->next = NULL;
	LNode *tail = headList;
	ElemType e;
	while(scanf("%d", &e) != EOF){
		LNode *newnode = (LNode *)malloc(sizeof(LNode));
		newnode->data = e;
		newnode->next = NULL;
		tail->next = newnode;
		tail = newnode;
	}
	tail->next = NULL;
	return headList;
}
// ͷ�巨����������
LinkList ListHeadInsert(LinkList &headList) 
{
	headList = (LinkList)malloc(sizeof(LNode));	// ����ͷ��� 
	headList->next = NULL;
	LNode *head = headList;
	ElemType e;
	while(scanf("%d", &e) != EOF){
		LNode *newnode = (LNode *)malloc(sizeof(LNode));
		newnode->data = e;
		newnode->next = head->next;	// newnode���ͷ����ĵ�һ����� 
		head->next = newnode; 	// ���µ�һ����� 
	}
	headList = head;
	return headList;
}
// ���ٵ�����
bool ListDestroy(LinkList headList)
{
	if(headList == NULL){
		return false;
	}
	LNode *p = headList->next;
	if(p != NULL){
		headList->next = p->next;	// ɾ��p��� 
		free(p);	// �ͷ�p���ռ� 
		p = headList->next; // pָ���µĽ�� 
	}
	free(headList);	// �ͷ�ͷ��� 
	return true;
}
// ������ת
LinkList ListReverse(LinkList &headList)
{
	LinkList newList = (LinkList)malloc(sizeof(LNode)); // �½�һ�������ͷ��� 
	newList->next = NULL;
	LNode *p = headList->next;
	while(p != NULL){
		LNode *newnode = (LNode *)malloc(sizeof(LNode)); // �½�һ�����׼������ 
		newnode->data = p->data; // �������� 
		newnode->next = p->next;  // ������һ��ָ�� 
		newnode->next = newList->next; // ���½ڵ���뵽������ĵ�һ�����ǰ 
		newList->next = newnode;	// ����ͷ���ָ��ĵ�һ����� 
		p = p->next; // p���� ׼���´��������� 
	}
	ListDestroy(headList);	// ����֮ǰ������ ��ֹ�ڴ���� 
	headList = newList;
	return headList;
}
int main()
{
	LinkList headList;
	bool flag = false;
	flag = InitList(headList);
	printf("%d\n", flag);
//	ListTailInsert(headList);
//	ListHeadInsert(headList); 
	for(int i = 0; i < 10; i++){
		ListInsert(headList, i+1, i+1);
	}
	// ��������������� 
	ListInsert(headList, 6, 5);
	InsertPriorNode(headList, headList->next->next, 10); 
	InsertPriorNode(headList->next->next, 11);
	ListDelete(headList, 8);
	DeleteNode(headList, headList->next->next);
	DeleteNode(headList->next->next);
	ListReverse(headList);
	int i = 1;
	for(LNode *p = headList->next; p != NULL; p = p->next){
		printf("��%d������ֵ�ǣ�%d\n", i++, p->data);
	}
	printf("����%d\n", Length(headList)); 
	return 0;
}
