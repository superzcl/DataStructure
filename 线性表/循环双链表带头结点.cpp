#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ElemType int

typedef struct LNode{
	ElemType data;
	struct LNode *prior;
	struct LNode *next;
}LNode, *LinkList;

// ��ͷ�ڵ�ĳ�ʼ��
bool InitList(LinkList &headList)
{
	headList = (LNode*) malloc(sizeof(LNode));
	if(headList == NULL){
		return false;
	}
	// ��ʼ��ʱѭ��˫�����ͷ����ǰ���㶼ָ���Լ� 
	headList->next = headList; 
	headList->prior = headList;	 
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
	while(j < i){
		p = p->next;
		j++;
		if(p == headList){ // p�ٴε���headList��ʾѭ��һ���� 
			return NULL;
		}
	}
	return p;
}
// ��ֵ����
LNode* LocateElem(LinkList headList, ElemType e)
{
	LNode *p = headList->next;
	while(p != headList && p->data != e){
		p = p->next;
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
	p->next->prior = node; // ��node��Ϊ���̽���ǰ�� 
	node->prior = p; // nodeǰ��ָ��ָ������ǰ�� 
	p->next = node; // node��Ϊp�ĺ�̽�� 
//	printf("%d\n", p->next->data);
	return true;
}
// �ڵ�idx��λ���ϲ���e 
bool ListInsert(LinkList &headList, int idx, ElemType e)
{
	if(idx < 1){
		return false;
	} 
	LNode *p = GetElem(headList, idx-1); 
	return InsertNextNode(p, e); // ������ָ���������Ԫ�صĺ��� 
}
// ��ָ�����p֮ǰ����Ԫ��e
bool InsertPriorNode(LinkList &headList, LNode *p, ElemType e)
{
	LNode *tmp = headList;
	tmp = p->prior;	// �õ�p����ǰһ����� 
	LNode *node = (LNode *)malloc(sizeof(LNode));
	if(node == NULL){
		return false;
	}
	
	node->data = e;
	node->prior = p->prior;
	p->prior->next = node;
	node->next = p;
	p->prior = node;
	return true;
}

// ɾ������ ɾ����idx��λ�õ�Ԫ��
bool ListDelete(LinkList &headList, int idx)
{
	if(idx < 0){
		return false;
	}
	LNode *p = GetElem(headList, idx-1); // �ҵ���idx-1����� 
	if(p == NULL || p->next == NULL){ // ���idx��Ч 
		return false;
	}
	LNode *tmp = p->next; // tmpΪ��ǰҪɾ���Ľ�� 
	p->next = tmp->next;
	tmp->next->prior = p;
	free(tmp); 
	return true; 
}
// ɾ��ָ����� O(1)����
bool DeleteNode(LinkList &headList, LNode *p)
{
	if(p == NULL){
		return false;
	}
	LNode *priorNode = p->prior; // ��ɾ������ǰ����� 
	LNode *nextNode  = p->next; // ��ɾ�����ĺ�̽�� 
	priorNode->next = nextNode;
	nextNode->prior = priorNode;
	free(p);
	return true;
}


// ��ͷ�ڵ���пշ���
bool IsEmpty(LinkList &headList)
{
	return (headList->next == headList);
}
// ��� 
int Length(LinkList headList)
{
	LNode *p = headList;
	int len = 0;
	while(p->next != headList){
		p = p->next;
		len++;
	}
	return len;
}
// β�巨����˫����
LinkList ListTailInsert(LinkList &headList)
{
	headList = (LinkList)malloc(sizeof(LNode)); // ����ͷ���
	headList->next = headList;
	headList->prior = headList; 
	LNode *tail = headList;
	ElemType e;
	while(scanf("%d", &e) != EOF){
		LNode *newnode = (LNode *)malloc(sizeof(LNode));
		newnode->data = e;
		newnode->next = headList;
		headList->prior = newnode;
		tail->next = newnode;
		newnode->prior = tail;
		tail = newnode;
	}
	tail->next = headList;
	headList->prior = tail;
	return headList;
}
// ͷ�巨����������
LinkList ListHeadInsert(LinkList &headList) 
{
	headList = (LinkList)malloc(sizeof(LNode));	// ����ͷ��� 
	headList->next = headList;
	headList->prior = headList; 
	LNode *head = headList;
	ElemType e;
	while(scanf("%d", &e) != EOF){
		LNode *newnode = (LNode *)malloc(sizeof(LNode));
		newnode->data = e;
		newnode->next = head->next;
		head->next->prior = newnode;
		newnode->prior = head;
		head->next = newnode; 
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
	if(p != headList){
		headList->next = p->next;	// ɾ��p��� 
		free(p);	// �ͷ�p���ռ� 
		p = headList->next; // pָ���µĽ�� 
	}
	free(headList);	// �ͷ�ͷ��� 
	return true;
}

int main()
{
	LinkList headList;
	bool flag = false;
	flag = InitList(headList);
	printf("%d\n", flag);
//	ListTailInsert(headList);
	ListHeadInsert(headList); 
	for(int i = 0; i < 10; i++){
		ListInsert(headList, i+1, i+1);
	}
	
	// ��������������� 
	ListInsert(headList, 6, 5);
	InsertPriorNode(headList, headList->next->next, 10); 

	ListDelete(headList, 8);
	DeleteNode(headList, headList->next->next);
	DeleteNode(headList, headList->next->next);
	
	printf("Here\n");
	int i = 1;
	for(LNode *p = headList->next; p != headList; p = p->next){
		printf("��%d������ֵ�ǣ�%d\n", i++, p->data);
	}
	printf("����%d\n", Length(headList)); 
	return 0;
}
