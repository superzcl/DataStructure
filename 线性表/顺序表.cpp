#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10 	// ����Ԫ�ظ������ֵ 
#define ElemType int	// ������������ 

typedef struct{
	ElemType *data;
	int MaxSize;
	int length;
}SeqList;

// ��ʼ��˳��� 
void InitList(SeqList &list, int initSize)
{
	list.data = (ElemType*) malloc(sizeof(ElemType) * initSize);
	for(int i = 0; i < N; i++){
		list.data[i] = 0;	// ��ʼ����������Ϊ0 
	}
	list.MaxSize = initSize;
	list.length = 0;
}
// ����˳���ĳ��� len
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
// ˳������Ԫ��, �ڵ�idx��λ���ϲ���Ԫ��e 
bool ListInsert(SeqList &list, int idx, ElemType e)
{
	// ���˳����������߲���λ�ó���˳�����false 
	if(list.length >= list.MaxSize || idx >= list.MaxSize || idx < 0){
		return false;
	} 
	// �������λ������������Ԫ��֮�� ����뵽ĩβ 
	if(idx > list.length){ 
		idx = list.length;
	}
	for(int i = list.length; i > idx; i--){
		list.data[i] = list.data[i-1];
	} 
	list.data[idx] = e;
	list.length++;	// ˳�����+1 
	return true; 
}
// ˳���ɾ��Ԫ��, ɾ��idxλ�õ�Ԫ�� 
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
// ˳������ ��ȡ���±�Ϊi��Ԫ�� 
ElemType GetElem(SeqList &list, int i) 
{
	return list.data[i];
}
// ˳������ ����Ԫ��e�Ƿ���ڲ������±�
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
