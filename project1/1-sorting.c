#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

int isDuplicate(int number, int array[], int size) {
  for (int i = 0; i < size; i++) {
    if (array[i] == number) {
      return 1;
    }
  }
  return 0;
}

void Merge(int A[], int l, int m, int r) {
  int n1 = m - l + 1;
  int n2 = r - m;
  int i = 0, j = 0, k = 0;

  int *sorted = (int*)malloc(sizeof(int) *(n1+n2));

  while (i < n1 && j < n2) {
    if (A[l + i] < A[m + 1 + j]) {
      sorted[k] = A[l + i];
      i++;
    } else {
      sorted[k] = A[m + 1 + j];
      j++;
    }
    k++;
  }

  if (i == n1) {
    for (; j < n2; j++) {
      swap(&sorted[k], &A[m + j + 1]);
      k++;
    }
  } else {
    for (; i < n1; i++) {
      swap(&sorted[k], &A[l + i]);
      k++;
    }
  }

  for (i = l; i <= r; i++) {
    swap(&A[i], &sorted[i-l]);
  }

  free(sorted);
}

void MergeSort(int A[], int l, int r) {
  if (l < r) {
    int m=l+((r-l)/2);
    MergeSort(A, l, m);
    MergeSort(A, m + 1, r);
    Merge(A, l, m, r);
  }
}

int HoarePartition(int A[], int l, int r) {
  int p = A[l];
  int i = l + 1;
  int j = r;

  while (1) {
    while (i <= j && A[i] <= p) {
      i++;
    }

    while (A[j] > p) {
      j--;
    }
    swap(&A[i], &A[j]);

    if (i >= j) {
      break;
    }
  }

  swap(&A[i], &A[j]);
  swap(&A[l], &A[j]);

  return j;
}

void QuickSort(int A[], int l, int r) {
  if (l < r) {
    int s = HoarePartition(A, l, r);
    QuickSort(A, l, s - 1);
    QuickSort(A, s + 1, r);
  }
}

int LomutoPartition(int A[], int l, int r) {
  int p = A[l];
  int s = l;
  for (int i = l + 1; i <= r; i++) {
    if (A[i] < p) {
      s++;
      swap(&A[s], &A[i]);
    }
  }
  swap(&A[l], &A[s]);
  return s;
}

int QuickSelect(int A[], int l, int r, int k) {
  int s = LomutoPartition(A, l, r);
  if (s == k - 1) {
    return A[s];
  } else if (s > k - 1) {
    QuickSelect(A, l, s - 1, k);
  } else {
    QuickSelect(A, s + 1, r, k);
  }
  return 0;
}

int main() {
  int n = 0;
  int k = 0;
  printf("Enter number of elements (n): ");
  scanf("%d", &n);
  printf("Enter k: ");
  scanf("%d", &k);

  int *elements = (int *)malloc(n * sizeof(int));
  int *MergeElements = (int *)malloc(n * sizeof(int));
  int *QuickElements = (int *)malloc(n * sizeof(int));
  int *QuickSelectElements = (int *)malloc(n * sizeof(int));

  int i = 0;
  srand(time(NULL));
  while (i < n) {
    int randomNumber = rand() % 10000000;
    if (!isDuplicate(randomNumber, elements, i)) {
      elements[i] = randomNumber;
      MergeElements[i] = randomNumber;
      QuickElements[i] = randomNumber;
      QuickSelectElements[i] = randomNumber;
      i++;
    }
  }

  printf("Elements of the array before sorting\n");
  for (i = 0; i < n; i++) {
    printf("%d ", elements[i]);
  }
  printf("\n");

  MergeSort(MergeElements, 0, n - 1);
  QuickSort(QuickElements, 0, n - 1);
  QuickSelect(QuickSelectElements, 0, n - 1, k);

  printf("\n%d smallest elements (Merge)\n", k);
  for (i = 0; i < k; i++) {
    printf("%d ", MergeElements[i]);
  }
  printf("\n\n%d smallest elements (Quick)\n", k);
  for (i = 0; i < k; i++) {
    printf("%d ", QuickElements[i]);
  }
  printf("\n\n%d-th smallest elements (QuickSelect)\n", k);

  printf("%d ", QuickSelectElements[k - 1]);

  printf("\n");
}