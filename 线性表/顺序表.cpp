#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10 	// 链表元素个数最大值 
#define ElemType int	// 链表数据类型 

typedef struct{
	ElemType *data;
	int MaxSize;
	int length;
}SeqList;

// 初始化顺序表 
void InitList(SeqList &list, int initSize)
{
	list.data = (ElemType*) malloc(sizeof(ElemType) * initSize);
	for(int i = 0; i < N; i++){
		list.data[i] = 0;	// 初始化所有数据为0 
	}
	list.MaxSize = initSize;
	list.length = 0;
}
// 增加顺序表的长度 len
void IncreaseList(SeqList &list, int len)
{
	ElemType* tmp =  list.data;
	list.data = (ElemType*) malloc(sizeof(ElemType) * (list.MaxSize + len));
	for(int i = 0; i < list.length; i++){
		list.data[i] = tmp[i];
	}
	list.MaxSize = list.MaxSize + len;
	free(tmp);
}
// 顺序表插入元素, 在第idx的位置上插入元素e 
bool ListInsert(SeqList &list, int idx, ElemType e)
{
	// 如果顺序表已满或者插入位置超出顺序表返回false 
	if(list.length >= list.MaxSize || idx >= list.MaxSize || idx < 0){
		return false;
	} 
	// 如果插入位置在所有已有元素之后 则插入到末尾 
	if(idx > list.length){ 
		idx = list.length;
	}
	for(int i = list.length; i > idx; i--){
		list.data[i] = list.data[i-1];
	} 
	list.data[idx] = e;
	list.length++;	// 顺序表长度+1 
	return true; 
}
// 顺序表删除元素, 删除idx位置的元素 
bool ListDelete(SeqList &list, int idx)
{
	if(idx < 0 || idx >= list.length){
		return false;
	}
	for(int i = idx; i < list.length -1; i++){
		list.data[i] = list.data[i+1];
	}
	list.length--;
	return true;
}
// 顺序表查找 获取第下标为i的元素 
ElemType GetElem(SeqList &list, int i) 
{
	return list.data[i];
}
// 顺序表查找 查找元素e是否存在并返回下标
int LocateElem(SeqList &list, ElemType e)
{
	int idx = -1;
	for(int i = 0; i < list.length; i++){
		if(list.data[i] == e){
			idx = i;
			break;
		}
	}
	return idx;
}
int main()
{
	SeqList list;
	InitList(list, 10);
	for(int i = 0; i < list.length; i++){
		printf("%d\n", list.data[i]);
	}
	IncreaseList(list, 20);
	for(int i = 0; i < 10; i++){
		ListInsert(list, i, i);
	}
	ListDelete(list, 3);
	ListInsert(list, 3, 3); 
	for(int i = 0; i < list.length; i++){
		printf("%d\n", list.data[i]);
	}
	return 0;
}
