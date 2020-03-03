#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ElemType int

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

// ����ͷ�ڵ�ĳ�ʼ�� 
bool InitList(LinkList &list)
{
	list = NULL;
	return true;
}

// ����ͷ�ڵ���пշ��� 
bool IsEmpty(LinkList &list)
{
	return (list == NULL);
}
// ����ͷ����ָ��λ�ò��� 
bool ListInsert(LinkList &list, int idx, ElemType e)
{
	if(idx < 1){
		return false;
	}	
	else if(idx == 1){ // ��������ڵ�һ�����λ�� 
		LNode *node = (LNode *)malloc(sizeof(LNode));
		node->data = e;
		node->next = list;
		list = node;
	}
	else{
		LNode *p = list;
		int j = 1; 
		while(p != NULL && j < idx-1){ // ѭ���ҵ�idx��ǰһ����� 
			p = p->next;
			j++;
		}
		if(p == NULL){	// idx������Χ��Ч 
			return false;
		} 
		LNode *node = (LNode *)malloc(sizeof(LNode));
		node->data = e;
		node->next = p->next;
		p->next = node; 
	}
	return true;
}
// ����ͷ����ָ�����֮�����
bool InsertNextNode(LNode *p, ElemType e)
{
	if(p == NULL){
		return false;
	}
	LNode *node = (LNode *)malloc(sizeof(LNode));
	if(node == NULL) return false;
	node->data = e;
	if(p->next == NULL){	// ��������λ��������ĩβ 
		node->next = NULL;
		p->next = node;
	}
	else{
		node->next = p->next;
		p->next = node;
	}
	return true;
}
// ����ͷ�����ָ�����֮ǰ���� 
bool InsertPriorNode(LinkList &list, LNode *p, ElemType e)
{
	if(p == NULL){
		return false;
	}
	if(p == list){	// ��������һ�����֮ǰ 
		LNode *node = (LNode *)malloc(sizeof(LNode));
		if(node == NULL) return false;
		node->data = e;
		node->next = list;
		list = node;
	}
	else{
		LNode *node = (LNode *)malloc(sizeof(LNode));
		if(node == NULL) return false;
		node->data = p->data;
		p->data = e;
		node->next = p->next;
		p->next = node;
	} 
	return true;
}
// ɾ��ָ��λ�õĽ�� 
bool ListDelete(LinkList &list, int idx)
{
	if(idx < 1){
		return false;
	} 
	LNode *p = list;
	if(idx == 1){
		list = list->next;
	}
	else{
		int j = 1;
		while(p != NULL && j < idx-1){	// ѭ���ҵ�idx��ǰһ����� 
			p = p->next;
			j++;
		}
		if(p == NULL || p->next == NULL){ // ���idx������Χ����Ч 
			return false;
		}
		LNode *tmp = p->next;
		p->next = p->next->next;
		free(tmp);
	}
	return true;
}
// ɾ��ָ�����
// �˷����޷�ɾ�����һ�����
bool DeleteNode(LinkList &list, LNode *p)
{
	if(p == NULL || p->next == NULL){
		return false;
	}
	if(p == list){	// ���ɾ�����µ�һ����� 
		list = list->next;
		free(p);
	}
	else{
		LNode *tmp = p->next;
		p->data = p->next->data;
		p->next = p->next->next;
		free(tmp);
	}
	return true;
}

int main()
{
	LinkList list;
	InitList(list);
	for(int i = 0; i < 2; i++){
		ListInsert(list, i+1, i+1);
	}
	ListInsert(list, 1, 10);
	InsertNextNode(list->next->next, 11);
	InsertPriorNode(list, list->next, 12);
	ListDelete(list, 6);
	DeleteNode(list, list->next);
	int i = 1;
	for(LNode *p = list; p != NULL; p = p->next){
		printf("��%d������ֵ�ǣ�%d\n", i++, p->data);
	}
	return 0;
}
