#include "get_next_line.h"
#include <sys/time.h>

 int    main(int ac, char **av) {
        (void)ac;
        struct timeval start, end;
        gettimeofday(&start, NULL);
    int fd = open(av[1], O_RDONLY);
    char *line = get_next_line(fd);
    while (line) {
        printf ("%s", line);
        line = get_next_line(fd);
    }
gettimeofday(&end, NULL);
    printf("time spent ==> %ld\n", (end.tv_sec - start.tv_sec) * 1000 +
    (end.tv_usec - start.tv_usec) / 1000);
        return (0);
}
