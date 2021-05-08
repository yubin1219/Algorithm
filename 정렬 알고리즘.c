# define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
# define MAX_SIZE 100000

// 속성-> 링커 -> 시스템 -> 스택예약크기,스택커밋크기를 변경한 후 디버깅하면 stack overflow되지 않음
// 스택크기를 20000000정도로 설정하면 데이터 개수 80000개, 셔플 수 0일 때(즉, 퀵정렬의 최악의 경우에도) 정상 작동 됨
// 스택크기를 더 늘리면 MAX_SIZE를 더 늘린 상태도 가능

void bubble_sort(int list[], int n)
{
	int i, j, tmp, swaped;
	for (i = n - 1; i > 0; i--)
	{
		swaped = 0;
		for (j = 0; j < i; j++)
		{
			if (list[j] > list[j + 1])
			{
				SWAP(list[j], list[j + 1], tmp);
				swaped = 1;
			}
		}
		if (!swaped) break;
	}
}

static void merge(int list[], int left, int mid, int right)
{
	int i, j, k, l;
	static int sorted[MAX_SIZE];
	k = left;
	for (i = left, j = mid + 1; i <= mid && j <= right;)
	{
		sorted[k++] = (list[i] <= list[j]) ? list[i++] : list[j++];
		if (i > mid)
		{
			for (l = j; l <= right; l++, k++)
				sorted[k] = list[l];
			break;
		}
		if (j > right)
		{
			for (l = i; l <= mid; l++, k++)
				sorted[k] = list[l];
			break;
		}
	}
	for (l = left; l <= right; l++)
		list[l] = sorted[l];
}
void merge_sort(int list[], int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		merge_sort(list, left, mid);
		merge_sort(list, mid + 1, right);
		merge(list, left, mid, right);
	}
}

int partition(int list[], int left, int right)
{
	int tmp;
	int low = left + 1;
	int high = right;
	int pivot = list[left];
	while (low < high)
	{
		for (; low <= right && list[low] < pivot; low++);
		for (; high >= left && list[high] > pivot; high--);
		if (low < high)
			SWAP(list[low], list[high], tmp);
	}
	if (list[high] > list[left])
		return left;
	SWAP(list[left], list[high], tmp);
	return high;
}
void quick_sort(int list[], int left, int right)
{
	int q;
	if (left < right)
	{
		q = partition(list, left, right);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}

int main()
{
	clock_t s1, e1, s2, e2, s3, e3;
	double t1,t2,t3;
	int i, data_num, shuffle_num, randnum1,randnum2, temp;
	int data[MAX_SIZE];

	srand(time(NULL));

	while (1)
	{	
		printf("Number of Data (0 exit/ MAX : %d): ",MAX_SIZE);
		scanf("%d", &data_num);
		
		if (data_num <= 0)
			break;

		// 배열 초기화
		for (i = 0; i < data_num; i++) 
			data[i] = i+1;
		
		printf("Number of time to shuffle: ");
		scanf("%d", &shuffle_num);
		
		// 배열 shuffle
		for (i = 0; i < shuffle_num; i++) 
		{
			randnum1 = rand() % data_num;
			randnum2 = rand() % data_num;
			SWAP(data[randnum1], data[randnum2], temp);
		}
	
		// 버블(Bubble) 정렬
		s1 = clock();
		bubble_sort(data, data_num);
		e1 = clock();
		t1 = (double) (e1 - s1) / CLOCKS_PER_SEC;
		printf("  Bubble sort: %.3f sec\n", t1);
		
		// 배열 shuffle
		for (i = 0; i < shuffle_num; i++) 
		{
			randnum1 = rand() % data_num;
			randnum2 = rand() % data_num;
			SWAP(data[randnum1], data[randnum2], temp);
		}
		
		// 병합(Merge) 정렬
		s2 = clock();
		merge_sort(data, 0, data_num - 1);
		e2 = clock();
		t2 = (double) (e2 - s2) / CLOCKS_PER_SEC;
		printf("  Merge sort: %.3f sec\n", t2);
	
		// 배열 shuffle
		for (i = 0; i < shuffle_num; i++) 
		{
			randnum1 = rand() % data_num;
			randnum2 = rand() % data_num;
			SWAP(data[randnum1], data[randnum2], temp);
		}
		
		// 퀵(Quick) 정렬
		s3 = clock();
		quick_sort(data, 0, data_num - 1);
		e3 = clock();
		t3 = (double) (e3 - s3) / CLOCKS_PER_SEC;
		printf("  Quick sort: %.3f sec\n", t3);
	}
	return 0;
}
