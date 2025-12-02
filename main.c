/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marekald <marekald@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:42:25 by marekald          #+#    #+#             */
/*   Updated: 2025/11/30 18:34:14 by marekald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/time.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	(void)ac;
	struct timeval start, end;
	gettimeofday(&start, NULL);
	int fd = open(av[1], O_RDONLY);
	char *line = get_next_line(fd);
	while (line)
	{
		printf ("%s", line);
		line = get_next_line(fd);
	}
	gettimeofday(&end, NULL);
	printf("time spent ==> %ld\n", (end.tv_sec - start.tv_sec)
	* 1000 + (end.tv_usec - start.tv_usec) / 1000);
	return (0);
}
