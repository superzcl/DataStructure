#include <stdio.h>
#include <stdlib.h>

#define ElemType int

typedef struct DNode{
	ElemType data;
	struct DNode *prior; // 指向前驱结点 
	struct DNode *next;  // 指向后继结点 
}DNode, *DLinkList; 
// 双向链表的初始化 
bool InitDLinkList(DLinkList &L)
{
	L = (DNode *)malloc(sizeof(DNode)); // 建立头结点 
	if(L == NULL) return false;	// 内存申请失败 
	L->prior = NULL;
	L->next = NULL;
	return true; 
}
// 双链表 查找指定idx位置的结点 
DNode* GetNode(DLinkList &L, int idx) 
{
	if(L == NULL){
		return NULL;
	}
	DNode *p = L;
	int j = 0;
	while(p->next != NULL && j < idx){ // 找到第idx个结点 
		p = p->next;
		j++;
	}
	return p;
}
// 双链表在指定p结点之后插入s结点 
bool InsertNextNode(DNode *p, DNode *s)
{
	
	if(p == NULL || s == NULL){ // 非法参数 
		return false;
	}
	
	s->next = p->next;
	if(p->next != NULL){ // 如果p有后继结点 
		p->next->prior = s;
	}
	s->prior = p;
	p->next = s;
	return true;
}
// 在指定位置插入结点p
bool ListInsert(DLinkList &L, int idx, DNode *p)
{
	if(idx < 1){
		return false;
	}

	DNode *s = GetNode(L, idx-1);	// 获取第idx-1个结点 
	if(s == NULL){
		return false;
	}
//	printf("Here\n");
	return InsertNextNode(s, p); // 在第idx-1之后插入p结点 
}
// 双链表 删除指定P结点的后继结点
bool DeleteNextNode(DNode *p)
{
	if(p == NULL || p->next == NULL){
		return false;
	}
	DNode *s = p->next; // 待删除结点 
	if(s->next != NULL){
		s->next->prior = p;
	}
	p->next = s->next;
	free(s);
	return true;
}
// 销毁双链表
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
// 头插法建立双链表
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
		if(L->next != NULL){ // 如果头结点有后继结点 
			L->next->prior = newnode;
		}
		newnode->prior = L;
		L->next = newnode;
	}
	return L;
}
// 尾插法建立双链表
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
		printf("第%d个结点的值是：%d\n", i++, p->data);
		p = p->next;
	} 
	return 0;
}
