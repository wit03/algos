#include <stdio.h>

int main() {
    int n = 0;
    int count;
    scanf("%n", &n);
    for(int i = 1; i < n-1; i++) {
        for(int j = i; i < i+1; j++) {
            count++;
        }
    }
    printf("%d", count);
    return 0;
}