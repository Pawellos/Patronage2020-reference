#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ITEM(T,id,size) ((char*)(T)+(id)*(size))
#define SWAP(T,id1, id2, tmp, size) \
    do { \
        memmove((tmp), ITEM((T),(id1),(size)), (size)); \
        memmove(ITEM((T),(id1),(size)), ITEM((T),(id2),(size)), (size)); \
        memmove(ITEM((T),(id2),(size)), (tmp), (size)); \
    } while(0)

typedef int (cmp_t)(const void *a, const void *b);

void heapify(void *base, size_t nmemb, size_t size, cmp_t *cmp,
        void *tmp, size_t i)
{
    size_t j, k;

    k = i;

    while (1) {
        j = k;

        if (2*j+1 < nmemb && cmp(ITEM(base,2*j+1,size), ITEM(base,k,size)) > 0)
            k = 2*j + 1;

        if (2*j+2 < nmemb && cmp(ITEM(base,2*j+2,size), ITEM(base,k,size)) > 0)
            k = 2*j + 2;

        if (j == k)
            break;

        SWAP(base, j, k, tmp, size);
    }
}

void heapsort(void *base, size_t nmemb, size_t size, cmp_t *cmp)
{
    ssize_t i;
    void *tmp = malloc(size);

    if (nmemb > 1)
        for (i = (nmemb-2) >> 1; i >= 0; i--)
            heapify(base, nmemb, size, cmp, tmp, i);

    while (nmemb-- > 1) {
        SWAP(base, 0, nmemb, tmp, size);
        heapify(base, nmemb, size, cmp, tmp, 0);
    }

    free(tmp);
}

int cmp_int(const void *a, const void *b)
{
    if (*(int *)a < *(int *)b)
        return -1;

    else if (*(int *)a > *(int *)b)
        return 1;

    else
        return 0;
}

int cmp_str(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

int main(void)
{
    int A[] = {5, 8, 2, 11, 3, 7, 9, 12};
    char *B[] = { "Jacek", "Maria", "Szymon", "Zosia",
        "Adam", "Gosia", "Bonawentura", "Kunegunda" };

    int i;

    heapsort(A, 8, sizeof(*A), cmp_int);
    heapsort(B, 8, sizeof(*B), cmp_str);

    for (i = 0; i < 8; i++)
        printf("%d%c", A[i], (i == 7) ? '\n' : ' ');

    for (i = 0; i < 8; i++)
        printf("%s%c", B[i], (i == 7) ? '\n' : ' ');

    return 0;
}
