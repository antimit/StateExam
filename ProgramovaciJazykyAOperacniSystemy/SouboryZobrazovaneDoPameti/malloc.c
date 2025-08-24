#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

void* my_malloc(size_t size) {
    // round up to multiple of page size
    size_t pagesize = getpagesize();
    size_t alloc_size = ((size + pagesize - 1) / pagesize) * pagesize;

    void* ptr = mmap(NULL, alloc_size,
                     PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS,
                     -1, 0);

    if (ptr == MAP_FAILED) {
        return NULL;
    }
    return ptr;
}

void my_free(void* ptr, size_t size) {
    size_t pagesize = getpagesize();
    size_t alloc_size = ((size + pagesize - 1) / pagesize) * pagesize;
    munmap(ptr, alloc_size);
}

int main() {
    int *arr = (int*) my_malloc(10 * sizeof(int));
    if (!arr) {
        perror("mmap failed");
        return 1;
    }

    for (int i = 0; i < 10; i++) arr[i] = i * 2;
    for (int i = 0; i < 10; i++) printf("%d ", arr[i]);
    printf("\n");

    my_free(arr, 10 * sizeof(int));
    return 0;
}
