/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:07:44 by yonshin           #+#    #+#             */
/*   Updated: 2022/11/16 20:40:01 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void	signal_char(int pid, unsigned char c)
{
	int	bit = 8;
	while (bit--) {
		int signal = SIGUSR1 + (c & 128) / 128;
		printf("%d %x\n", signal, c);
		kill(pid, signal);
		c = c << 1;
		usleep(1000);
	}
}

int	atoi(char *str)
{
	int	i = 0;
	while (*str)
		i = i * 10 + *str++ - '0';
	return i;
}

int	main(int argc, char *argv[])
{
	if (argc < 3)
		return (0);
	int		pid = atoi(argv[1]);
	char	*str = argv[2];

	while (*str)
		signal_char(pid, *str++);
	return (0);
}
