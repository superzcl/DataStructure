#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ElemType int

typedef struct LNode{
	ElemType data;
	struct LNode *prior;
	struct LNode *next;
}LNode, *LinkList;

// 带头节点的初始化
bool InitList(LinkList &headList)
{
	headList = (LNode*) malloc(sizeof(LNode));
	if(headList == NULL){
		return false;
	}
	// 初始化时循环双链表的头结点的前后结点都指向自己 
	headList->next = headList; 
	headList->prior = headList;	 
	return true;
}
// 按位查找 
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
		if(p == headList){ // p再次等于headList表示循环一周了 
			return NULL;
		}
	}
	return p;
}
// 按值查找
LNode* LocateElem(LinkList headList, ElemType e)
{
	LNode *p = headList->next;
	while(p != headList && p->data != e){
		p = p->next;
	}
	return p;
}
// 在指定结点p后插入元素e
bool InsertNextNode(LNode *p, ElemType e)
{
	if(p == NULL){
		return false;
	}
	LNode *node = (LNode *)malloc(sizeof(LNode));
	if(node == NULL){ // 内存分配失败 
		return false;
	}
	node->data = e;
	node->next = p->next; // 连接node的后继结点 
	p->next->prior = node; // 让node成为其后继结点的前驱 
	node->prior = p; // node前向指针指向它的前驱 
	p->next = node; // node成为p的后继结点 
//	printf("%d\n", p->next->data);
	return true;
}
// 在第idx的位置上插入e 
bool ListInsert(LinkList &headList, int idx, ElemType e)
{
	if(idx < 1){
		return false;
	} 
	LNode *p = GetElem(headList, idx-1); 
	return InsertNextNode(p, e); // 调用在指定结点后插入元素的函数 
}
// 在指定结点p之前插入元素e
bool InsertPriorNode(LinkList &headList, LNode *p, ElemType e)
{
	LNode *tmp = headList;
	tmp = p->prior;	// 得到p结点的前一个结点 
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

// 删除操作 删除第idx个位置的元素
bool ListDelete(LinkList &headList, int idx)
{
	if(idx < 0){
		return false;
	}
	LNode *p = GetElem(headList, idx-1); // 找到第idx-1个结点 
	if(p == NULL || p->next == NULL){ // 如果idx无效 
		return false;
	}
	LNode *tmp = p->next; // tmp为当前要删除的结点 
	p->next = tmp->next;
	tmp->next->prior = p;
	free(tmp); 
	return true; 
}
// 删除指定结点 O(1)方法
bool DeleteNode(LinkList &headList, LNode *p)
{
	if(p == NULL){
		return false;
	}
	LNode *priorNode = p->prior; // 被删除结点的前驱结点 
	LNode *nextNode  = p->next; // 被删除结点的后继结点 
	priorNode->next = nextNode;
	nextNode->prior = priorNode;
	free(p);
	return true;
}


// 带头节点的判空方法
bool IsEmpty(LinkList &headList)
{
	return (headList->next == headList);
}
// 求表长 
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
// 尾插法建立双链表
LinkList ListTailInsert(LinkList &headList)
{
	headList = (LinkList)malloc(sizeof(LNode)); // 建立头结点
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
// 头插法建立单链表
LinkList ListHeadInsert(LinkList &headList) 
{
	headList = (LinkList)malloc(sizeof(LNode));	// 建立头结点 
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
// 销毁单链表
bool ListDestroy(LinkList headList)
{
	if(headList == NULL){
		return false;
	}
	LNode *p = headList->next;
	if(p != headList){
		headList->next = p->next;	// 删除p结点 
		free(p);	// 释放p结点空间 
		p = headList->next; // p指向新的结点 
	}
	free(headList);	// 释放头结点 
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
	
	// 调用链表操作函数 
	ListInsert(headList, 6, 5);
	InsertPriorNode(headList, headList->next->next, 10); 

	ListDelete(headList, 8);
	DeleteNode(headList, headList->next->next);
	DeleteNode(headList, headList->next->next);
	
	printf("Here\n");
	int i = 1;
	for(LNode *p = headList->next; p != headList; p = p->next){
		printf("第%d个结点的值是：%d\n", i++, p->data);
	}
	printf("表长是%d\n", Length(headList)); 
	return 0;
}
