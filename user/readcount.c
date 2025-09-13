#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[])
{
    int initial_count, final_count, fd;
    char buf[100];

    // 1. Get initial read count
    initial_count = getreadcount();
    printf("Initial read count: %d\n", initial_count);

    // 2. Read 100 bytes from a file. We'll use the README file.
    fd = open("README", O_RDONLY);
    if(fd < 0){
        printf("readcount: failed to open README\n");
        exit(1);
    }

    int bytes_read = read(fd, buf, sizeof(buf));
    if(bytes_read < 0){
        printf("readcount: read failed\n");
        exit(1);
    }
    close(fd);

    // 3. Get final read count and verify
    final_count = getreadcount();
    printf("Final read count: %d\n", final_count);

    printf("Bytes read during test: %d\n", bytes_read);
    printf("Difference in getreadcount(): %d\n", final_count - initial_count);

    if (final_count - initial_count == bytes_read) {
        printf("Test PASSED!\n");
    } else {
        printf("Test FAILED!\n");
    }

    exit(0);
}