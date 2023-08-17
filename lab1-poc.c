#include <stdio.h>

int main() {
    int n = 5;
    int curr = 0, prev = 0;
    int currMax = 0, count = 0, maxCount = 0;
    int arr[5] = {1, 1, 3, 4, 4, 5};
    for(int i = 0; i < n; i++) {
        curr = i;
        if (curr == prev) {
            count++;
        }
        prev = curr;
    
    }
}
