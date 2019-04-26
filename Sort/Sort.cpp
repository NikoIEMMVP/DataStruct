
#include <stdio.h>


void PrintArray(int array[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

void Swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

// 插入排序
// 时间复杂度:
// 1) 最好		O(n)	已经有序
// 2) 平均		O(n^2)
// 3) 最坏		O(n^2)	已经有序，是逆序
// 空间复杂度
// O(1)
// 稳定
void InsertSort(int array[], int size) {
	// 外边的循环实现减治过程
	// 一次取一个数，插入到前面的有序区间内
	// 更优化的版本
	// for (int i = 1; i < size; i++) {
	for (int i = 0; i < size; i++) {
		int key = array[i];
		// 内部的循环实现的是插入的过程
		// j 从 [i-1, 0]
		// 如果 array[j] > key，往后搬
		// 如果 array[j] == key，跳出循环（保证了稳定性）
		// 如果 array[j] < key，跳出循环
		int j;
		for (j = i - 1; j >= 0 && array[j] > key; j--) {
			array[j + 1] = array[j];
		}

		// j + 1 就是要插入的位置
		array[j + 1] = key;
	}
}

// 希尔排序
// 是插入排序的优化版本
// 在插入排序之前，尽可能的让数据有序
// 分组插排
// 时间复杂度
// 1）最好	O(n)
// 2）平均	O(n^1.2) - O(n^1.3)
// 3）最差	O(n^2)
// 空间复杂度
// O(1)
// 不稳定（一旦分组，很难保证相同数分到一个组里）

// 可以设置 gap 的插入排序
void InsertSortWithGap(int array[], int size, int gap) {
	// 更优化的版本应该是
	// for (int i = gap; i < size; i++) {
	for (int i = 0; i < size; i++) {
		int key = array[i];
		int j;
		for (j = i - gap; j >= 0 && array[j] > key; j -= gap) {
			array[j + gap] = array[j];
		}

		array[j + gap] = key;
	}
}

void ShellSort(int array[], int size) {
	int gap = size;
	while (1) {
		gap = (gap / 3) + 1;	// 工程做法，没有具体理论
		InsertSortWithGap(array, size, gap);
		if (gap == 1) {
			return;
		}
	}
}

// 选择排序
// 时间复杂度：
// 最好/平均/最坏	O(n^2)
// 空间复杂度 O(1)
// 不稳定 { 9, 4, 3, 5a, 5b }，无法保证 5a 一定在 5b 前
void SelectSort(int array[], int size) {
	// for (int i = 0; i < size - 1; i++) {
	for (int i = 0; i < size; i++) {
		int max = 0;	// 假设最大的数下标为 0
		for (int j = 1; j < size - i; j++) {
			if (array[j] > array[max]) {
				max = j;
			}
		}

		Swap(array + max, array + size - 1 - i);
	}
}

// 堆排序（建大堆）
// 时间复杂度：
// 最好|平均|最坏	O(n*log(n))
// 空间复杂度 O(1)
// 不稳定	（向下调整过程中，无法保证相等数前后关系）
// 向下调整
// 时间复杂度 O(log(n))
void AdjustDown(int array[], int size, int root)
{
	int i = 2 * root + 1;
	int j = 2 * root + 2;

	if (i >= size) {
		return;
	}

	int m = i;
	if (j < size && array[j] > array[i]) {
		m = j;
	}

	if (array[m] > array[root]) {
		Swap(array + m, array + root);
		AdjustDown(array, size, m);
	}
}
// 建堆
// O(n) or O(n * log(n))
void CreateHeap(int array[], int size)
{
	for (int i = (size - 2) / 2; i >= 0; i--) {
		AdjustDown(array, size, i);
	}
}
// 堆排序
void HeapSort(int array[], int size)
{
	CreateHeap(array, size);

	for (int i = 0; i < size; i++) {
		Swap(array, array + size - i - 1);
		AdjustDown(array, size - 1 - i, 0);
	}
}

// 时间复杂度
// 最好 O(n)	已经有序
// 最坏|平均 O(n^2)
// 空间复杂度 O(1)
// 稳定
void BubbleSort(int array[], int size) {
	for (int i = 0; i < size; i++) {
		int sorted = 1;
		for (int j = 0; j < size - 1 - i; j++) {
			if (array[j] > array[j + 1]) {
				Swap(array + j, array + j + 1);
				sorted = 0;
			}
		}
		if (sorted == 1) {
			return;
		}
	}
}

// 快速排序

int Parition_1(int array[], int left, int right) {
	int begin = left;
	int end = right;
	// 基准值是 array[right]

	while (begin < end) {
		// 优先走左边
		while (begin < end && array[begin] <= array[right]) {
			begin++;
		}
		// 一定是左边卡住了

		// 再走右边
		while (begin < end && array[end] >= array[right]) {
			end--;
		}
		// 一定是右边也卡住了

		Swap(array + begin, array + end);
	}

	// 区间被分成 小，大，基准
	Swap(array + begin, array + right);

	// 返回当前基准值所在位置
	return begin;
}

// 要排序的区间是 array[left, right]
void __QuickSort(int array[], int left, int right) {
	// 终止条件 size == 0 || size == 1
	// left == right	区间内还剩一个数
	// left > right		区间内没有数
	if (left == right) {
		return;
	}

	if (left > right) {
		return;
	}

	int div; // 比基准值小的放基准值左边，大的放右边后，基准值所在的下标
	div = Parition_1(array, left, right);	// 遍历 array[left, right]，把小的放左，大的放右
	__QuickSort(array, left, div - 1);	// 分治解决左边的小区间
	__QuickSort(array, div + 1, right);	// 分治解决右边的小区间
}

void QuickSort(int array[], int size) {
	__QuickSort(array, 0, size - 1);
}

void Test() {
	int array[] = { 3, 4, 9, 8, 7, 11, 12, 4, 5, 1, 0, 2, 6 };
	int size = sizeof(array) / sizeof(int);

	PrintArray(array, size);
	BubbleSort(array, size);
	PrintArray(array, size);
}

int main() {
	Test();
}

