#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ElemType int

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

// 带头节点的初始化
bool InitList(LinkList &headList)
{
	headList = (LNode*) malloc(sizeof(LNode));
	if(headList == NULL){
		return false;
	}
	headList->next = NULL;
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
	while(p != NULL && j < i){
		p = p->next;
		j++;
	}
	return p;
}
// 按值查找
LNode* LocateElem(LinkList headList, ElemType e)
{
	LNode *p = headList->next;
	while(p != NULL && p->data != e){
		p = p ->next;
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
	p->next = node; // 连接node的前驱结点 
//	printf("%d\n", p->next->data);
	return true;
}
// 在第idx的位置上插入e 
bool ListInsert(LinkList &headList, int idx, ElemType e)
{
	if(idx < 1){
		return false;
	} 
	LNode *p = headList;	// headList指向头结点 头结点不存数据 
	int j = 0;	// 当前p指向第几个结点 
	while(p != NULL && j < idx - 1){ // 循环找到第idx-1个节点 
		p = p->next;
		j++;
	}  
	return InsertNextNode(p, e); // 调用在指定结点后插入元素的函数 
}
// 在指定结点p之前插入元素e  O(n)方法 
bool InsertPriorNode(LinkList &headList, LNode *p, ElemType e)
{
	LNode *tmp = headList;
	while(tmp != NULL){	// 循环找到p结点的前一个结点 
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
// 在指定结点p之前插入元素e  O(1)方法 
bool InsertPriorNode(LNode *p, ElemType e)
{
	if(p == NULL){
		return false;
	}
	LNode *node = (LNode *)malloc(sizeof(LNode));
	if(node == NULL){
		return false;
	} 
	// 移动数据 实现插入结点 
	node->data = p->data;	// 新申请的结点替换掉当前的p结点 
	p->data = e; 	// 然后把p结点的数据更换，这样p就成了先前p的前驱结点 
	node->next = p->next; // 连接 
	p->next = node;
	return true;
}
// 删除操作 删除第idx个位置的元素
bool ListDelete(LinkList &headList, int idx)
{
	if(idx < 0){
		return false;
	}
	LNode *p = headList;
	for(int i = 0; i < idx-1 && p != NULL; i++){ // 循环找到第i-1个结点 
		p = p->next;
	}
	if(p == NULL || p->next == NULL){ // 如果idx无效 
		return false;
	}
	LNode *tmp = p->next; // tmp为当前要删除的结点 
	p->next = tmp->next;
	free(tmp); 
	return true; 
}
// 删除指定结点 O(n)方法
bool DeleteNode(LinkList &headList, LNode *p)
{
	if(p == NULL){
		return false;
	}
	LNode *tmp = headList;
	while(tmp->next != p){	// 循环找到被删除结点的前驱结点 
		tmp = tmp->next;
	}
	tmp->next = p->next;
	free(p);
	return true;
}
// 删除指定结点 O(1)方法
// 缺陷是无法删除最后一个结点 
bool DeleteNode(LNode *p)
{
	if(p == NULL || p->next == NULL){ // 如果p不存在或p是最后一个结点 
		return false;
	}
	LNode *q = p->next;	// q是被删除结点p的后继结点 
	p->data = q->data;	// 把p变成q结点 
	p->next = q->next;	// p在与q的后继结点相连，等价于删除了p结点 
	free(q);
	return true;
}


// 带头节点的判空方法
bool IsEmpty(LinkList &headList)
{
	return (headList->next == NULL);
}
// 求表长 
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
// 尾插法建立单链表
LinkList ListTailInsert(LinkList &headList)
{
	headList = (LinkList)malloc(sizeof(LNode)); // 建立头结点
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
// 头插法建立单链表
LinkList ListHeadInsert(LinkList &headList) 
{
	headList = (LinkList)malloc(sizeof(LNode));	// 建立头结点 
	headList->next = NULL;
	LNode *head = headList;
	ElemType e;
	while(scanf("%d", &e) != EOF){
		LNode *newnode = (LNode *)malloc(sizeof(LNode));
		newnode->data = e;
		newnode->next = head->next;	// newnode变成头结点后的第一个结点 
		head->next = newnode; 	// 更新第一个结点 
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
	if(p != NULL){
		headList->next = p->next;	// 删除p结点 
		free(p);	// 释放p结点空间 
		p = headList->next; // p指向新的结点 
	}
	free(headList);	// 释放头结点 
	return true;
}
// 单链表反转
LinkList ListReverse(LinkList &headList)
{
	LinkList newList = (LinkList)malloc(sizeof(LNode)); // 新建一个链表的头结点 
	newList->next = NULL;
	LNode *p = headList->next;
	while(p != NULL){
		LNode *newnode = (LNode *)malloc(sizeof(LNode)); // 新建一个结点准备复制 
		newnode->data = p->data; // 复制数据 
		newnode->next = p->next;  // 复制下一个指针 
		newnode->next = newList->next; // 将新节点插入到新链表的第一个结点前 
		newList->next = newnode;	// 更新头结点指向的第一个结点 
		p = p->next; // p后移 准备下次上述操作 
	}
	ListDestroy(headList);	// 销毁之前的链表 防止内存溢出 
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
	// 调用链表操作函数 
	ListInsert(headList, 6, 5);
	InsertPriorNode(headList, headList->next->next, 10); 
	InsertPriorNode(headList->next->next, 11);
	ListDelete(headList, 8);
	DeleteNode(headList, headList->next->next);
	DeleteNode(headList->next->next);
	ListReverse(headList);
	int i = 1;
	for(LNode *p = headList->next; p != NULL; p = p->next){
		printf("第%d个结点的值是：%d\n", i++, p->data);
	}
	printf("表长是%d\n", Length(headList)); 
	return 0;
}
