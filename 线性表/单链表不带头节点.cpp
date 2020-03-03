#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ElemType int

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

// 不带头节点的初始化 
bool InitList(LinkList &list)
{
	list = NULL;
	return true;
}

// 不带头节点的判空方法 
bool IsEmpty(LinkList &list)
{
	return (list == NULL);
}
// 不带头结点的指定位置插入 
bool ListInsert(LinkList &list, int idx, ElemType e)
{
	if(idx < 1){
		return false;
	}	
	else if(idx == 1){ // 如果插入在第一个结点位置 
		LNode *node = (LNode *)malloc(sizeof(LNode));
		node->data = e;
		node->next = list;
		list = node;
	}
	else{
		LNode *p = list;
		int j = 1; 
		while(p != NULL && j < idx-1){ // 循环找到idx的前一个结点 
			p = p->next;
			j++;
		}
		if(p == NULL){	// idx超出范围无效 
			return false;
		} 
		LNode *node = (LNode *)malloc(sizeof(LNode));
		node->data = e;
		node->next = p->next;
		p->next = node; 
	}
	return true;
}
// 不带头结点的指定结点之后插入
bool InsertNextNode(LNode *p, ElemType e)
{
	if(p == NULL){
		return false;
	}
	LNode *node = (LNode *)malloc(sizeof(LNode));
	if(node == NULL) return false;
	node->data = e;
	if(p->next == NULL){	// 如果插入的位置在链表末尾 
		node->next = NULL;
		p->next = node;
	}
	else{
		node->next = p->next;
		p->next = node;
	}
	return true;
}
// 不带头结点在指定结点之前插入 
bool InsertPriorNode(LinkList &list, LNode *p, ElemType e)
{
	if(p == NULL){
		return false;
	}
	if(p == list){	// 如果插入第一个结点之前 
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
// 删除指定位置的结点 
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
		while(p != NULL && j < idx-1){	// 循环找到idx的前一个结点 
			p = p->next;
			j++;
		}
		if(p == NULL || p->next == NULL){ // 如果idx超出范围则无效 
			return false;
		}
		LNode *tmp = p->next;
		p->next = p->next->next;
		free(tmp);
	}
	return true;
}
// 删除指定结点
// 此方法无法删除最后一个结点
bool DeleteNode(LinkList &list, LNode *p)
{
	if(p == NULL || p->next == NULL){
		return false;
	}
	if(p == list){	// 如果删除的事第一个结点 
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
		printf("第%d个结点的值是：%d\n", i++, p->data);
	}
	return 0;
}
