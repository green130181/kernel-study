#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>


int main() {
    const int size = 1024;
    char *buffer = reinterpret_cast<char *>(malloc(size));
    memset(buffer, 0, size);
    __builtin___clear_cache(buffer, buffer + size);
}
