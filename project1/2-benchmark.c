#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void Merge(int A[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    int i = 0, j = 0, k = 0;

    int *sorted = (int *)malloc(sizeof(int) * (n1 + n2));

    while (i < n1 && j < n2)
    {
        if (A[l + i] < A[m + 1 + j])
        {
            sorted[k] = A[l + i];
            i++;
        }
        else
        {
            sorted[k] = A[m + 1 + j];
            j++;
        }
        k++;
    }

    if (i == n1)
    {
        for (; j < n2; j++)
        {
            swap(&sorted[k], &A[m + j + 1]);
            k++;
        }
    }
    else
    {
        for (; i < n1; i++)
        {
            swap(&sorted[k], &A[l + i]);
            k++;
        }
    }

    for (i = l; i <= r; i++)
    {
        swap(&A[i], &sorted[i - l]);
    }

    free(sorted);
}

void MergeSort(int A[], int l, int r)
{
    if (l < r)
    {
        int m = l + ((r - l) / 2);
        MergeSort(A, l, m);
        MergeSort(A, m + 1, r);
        Merge(A, l, m, r);
    }
}

int HoarePartition(int A[], int l, int r)
{
    int p = A[l];
    int i = l + 1;
    int j = r;

    while (1)
    {
        while (i <= j && A[i] <= p)
        {
            i++;
        }

        while (A[j] > p)
        {
            j--;
        }
        swap(&A[i], &A[j]);

        if (i >= j)
        {
            break;
        }
    }

    swap(&A[i], &A[j]);
    swap(&A[l], &A[j]);

    return j;
}

void QuickSort(int A[], int l, int r)
{
    if (l < r)
    {
        int s = HoarePartition(A, l, r);
        QuickSort(A, l, s - 1);
        QuickSort(A, s + 1, r);
    }
}

int LomutoPartition(int A[], int l, int r)
{
    int p = A[l];
    int s = l;
    for (int i = l + 1; i <= r; i++)
    {
        if (A[i] < p)
        {
            s++;
            swap(&A[s], &A[i]);
        }
    }
    swap(&A[l], &A[s]);
    return s;
}

int QuickSelect(int A[], int l, int r, int k)
{
    int s = LomutoPartition(A, l, r);
    if (s == k - 1)
    {
        return A[s];
    }
    else if (s > k - 1)
    {
        QuickSelect(A, l, s - 1, k);
    }
    else
    {
        QuickSelect(A, s + 1, r, k);
    }
    return 0;
}

double algo(int n, int k)
{
    int *elements = (int *)malloc(n * sizeof(int));
    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        int randomNumber = rand() % 10000000;
        elements[i] = randomNumber;
    }

    clock_t start_time = clock();

    // MergeSort(elements, 0, n - 1);
    // QuickSort(elements, 0, n - 1);
    QuickSelect(elements, 0, n - 1, k);

    clock_t end_time = clock();

    free(elements);

    return (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;
}

int main()
{
    FILE *fpt;
    // fpt = fopen("merge.csv", "w+");
    // fpt = fopen("quick.csv", "w+");
    fpt = fopen("quickselect.csv", "w+");
    fprintf(fpt, "n,k,count,time\n");

    int n_values[] = {50, 100, 500, 1000, 5000,
                      10000, 50000, 100000, 500000, 1000000,
                      5000000, 10000000, 20000000, 50000000};
    int k_values[] = {5, 10, 50, 100, 1000};
    int sampleCount = 5;

    for (int i = 0; i < sizeof(n_values) / sizeof(n_values[0]); i++)
    {
        for (int j = 0; k_values[j] < n_values[i] && (j < sizeof(k_values) / sizeof(k_values[0])) ; j++)
        {
            int n = n_values[i];
            int k = k_values[j];
            for (int count = 0; count < sampleCount; count++)
            {
                double run_time = algo(n, k);
                printf("Runtime for n=%d, k=%d: %.3f ms, count: %d/5\n", n, k, run_time,
                       count + 1);
                fprintf(fpt, "%d,%d,%d,%.3f\n", n, k, count + 1, run_time);
            }
        }
    }

    fclose(fpt);
    return 0;
}