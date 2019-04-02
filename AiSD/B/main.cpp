#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define MAX_HEAP 700000

unsigned long long *heap;
int *next_val;


void move_down(int i, int size)
{
	int left = 2 * (i + 1) - 1;
	int right = 2 * (i + 1);

	if (left < size && right < size && heap[left] > heap[i] && heap[right] > heap[i] && heap[left] > heap[right])
	{
		swap(heap[left], heap[i]);
		swap(next_val[left], next_val[i]);
		move_down(left, size);
		return;
	}
	if (left < size && right < size && heap[left] > heap[i] && heap[right] > heap[i] && heap[left] < heap[right])
	{
		swap(heap[right], heap[i]);
		swap(next_val[right], next_val[i]);
		move_down(right, size);
		return;
	}
	if (left < size && heap[left] > heap[i])
	{
		swap(heap[left], heap[i]);
		swap(next_val[left], next_val[i]);
		move_down(left, size);
		return;
	}
	if (right < size && heap[right] > heap[i])
	{
		swap(heap[right], heap[i]);
		swap(next_val[right], next_val[i]);
		move_down(right, size);
		return;
	}
	return;
}


int main()
{
	int k;
	unsigned long long M;
	scanf("%llu %d", &M, &k);

	unsigned int size = fmin(M, MAX_HEAP);

	heap = new unsigned long long[size];
	next_val = new int[size];

	unsigned int j = 0;
	for (; j < size; j++)
	{
		heap[j] = (M - j) * M;
		next_val[j] = M - j;
	}

	unsigned long long last_max = M * M + 1;

	for (int i = 0; i < k; i++)
	{
		if (heap[0] < last_max)
		{
			if(i==k-1)
			printf("%llu\n", heap[0]);
			last_max = heap[0];
		}
		else //powtorzenie
			i--;

		heap[0] -= next_val[0];
		unsigned long long next = next_val[0];

		if (heap[0] < next * next && j < M)
		{
			heap[0] = (M - j) * M;
			next_val[0] = M - j;
			j++;
		}

		move_down(0, size);
	}

	return 0;
}