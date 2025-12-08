rm valgrind-out.txt
sleep 1
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --log-file=valgrind-out.txt \
         ./a.out texto.txt BUFFER_SIZE=1000000
