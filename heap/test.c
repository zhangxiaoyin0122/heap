#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
typedef int HPDataType;

typedef struct Heap {
	HPDataType* _array;
	size_t _size;
	size_t _capacity;
}Heap;


void swap(HPDataType* array, int child, int parent) {
	int tmp = array[child];
	array[child] = array[parent];
	array[parent] = tmp;
}
//向下调整,建小堆
void shiftdown1(HPDataType* array, int size, int parent) {
	int child = 2 * parent + 1;
	while (child < size) {
		if (child + 1 < size&& array[child] > array[child + 1])
			child++;
		if (array[child] < array[parent]) {
			swap(array, child, parent);
			parent = child;
			child = 2 * parent + 1;
		}
		else
			break;
	}
}
//向下调整,建大堆
void shiftdown(HPDataType* array, int size, int parent) {
	int child = 2 * parent + 1;
	while (child < size) {
		if (child + 1 < size&& array[child] < array[child + 1])
			child++;
		if (array[child] > array[parent]) {
			swap(array, child, parent);
			parent = child;
			child = 2 * parent + 1;
		}
		else
			break;
	}
}
void HeapCreat(Heap* hp, HPDataType* array, int size) {
	hp->_array = (HPDataType*)malloc(sizeof(HPDataType)*size);
	memcpy(hp->_array, array, sizeof(HPDataType)*size);
	hp->_capacity = size;
	hp->_size = size;

	for (int parent = (size - 2) / 2; parent >= 0; parent--) {
		shiftdown(hp->_array, size, parent);
	}
}
//向上调整,建小堆
void shiftup1(HPDataType* array, int child) {
	int parent = (child - 1) / 2;
	while (child > 0) {
		//前提是小根堆已经建好
		if (array[child] < array[parent]) {
			swap(array, child, parent);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
			break;
	}
}
//向上调整,建大堆
void shiftup(HPDataType* array, int child) {
	int parent = (child - 1) / 2;
	while (child > 0) {
		//前提是大根堆已经建好
		if (array[child] > array[parent]) {
			swap(array, child, parent);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
			break;
	}
}
//尾插
void HeapPush(Heap* hp,HPDataType data) {
	//检查容量
	if (hp->_size == hp->_capacity) {
		hp->_capacity *= 2;
		hp->_array = (HPDataType*)realloc(hp->_array, sizeof(HPDataType)*hp->_capacity);
	}
	//尾插
	hp->_array[hp->_size++] = data;
	shiftup(hp->_array, hp->_size - 1);
}
//删除堆顶元素
void HeapPop(Heap* hp) {
	if (hp->_size > 0) {
		//交换:堆顶和最后一个叶子
		swap(hp->_array, 0, hp->_size - 1);
		//尾删:实际删除的是堆顶元素
		hp->_size--;
		//向下调整
		shiftdown(hp->_array, hp->_size, 0);
	}
}
//获取堆顶元素
HPDataType HeapTop(Heap* hp) {
	return hp->_array[0];
}
//判空
int HeapEmpty(Heap* hp) {
	if (hp->_size == 0)
		return 1;
	return 0;
}
//堆打印
void HeapPrint(Heap* hp) {
	for (size_t i = 0; i < hp->_size; i++) {
		printf("%d ", hp->_array[i]);
	}
	printf("\n");
}

void test() {
	Heap hp;
	int array[11] = { 100,50,30,20,25,18,10,5,15,21,23 };
	HeapCreat(&hp, array, 11);
	HeapPrint(&hp);
}

void test1() {
	Heap hp;
	int array[11] = { 100,50,30,20,25,18,10,5,15,21,23 };
	int n = sizeof(array) / sizeof(array[0]);
	HeapCreat(&hp, array, n);
	HeapPrint(&hp);
	HeapPush(&hp, 7);
	HeapPrint(&hp);
	HeapPop(&hp);
	HeapPrint(&hp);
}
void test2() {
	Heap hp;
	int array[11] = { 100,50,30,20,25,18,10,5,15,21,23 };
	int n = sizeof(array) / sizeof(array[0]);
	HeapCreat(&hp, array, n);
	HeapPrint(&hp);
	while (HeapEmpty(&hp) != 1) {
		printf("%d\n",HeapTop(&hp));
		HeapPop(&hp);
	}
}

//堆排序
void HeapSort(int* array, int n) {
	for (int i = (n - 2) / 2; i >= 0; i--) {
		shiftdown(array,n,i);
	}
	while (n > 1) {
		swap(array, 0, n - 1);
		n--;
		shiftdown(array, n, 0);
	}
}
void test3() {
	int array[11] = { 100,50,30,20,25,18,10,5,15,21,23 };
	int n = sizeof(array) / sizeof(array[0]);
	HeapSort(array, n);
	for (int i = 0; i < n; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}
int main() {
	//test();
	//test1();
	//test2();
	test3();
	system("pause");
	return 0;
}

