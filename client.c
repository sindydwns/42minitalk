/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:07:44 by yonshin           #+#    #+#             */
/*   Updated: 2022/11/17 02:00:47 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*g_str;
void	signal_char(int pid)
{
	static int	bit;
	int			signal;

	signal = SIGUSR1 + ((*g_str & (0b100000000 >> ++bit)) > 0);
	if (bit != 8)
	{
		kill(pid, signal);
		return ;
	}
	if (*g_str == 0)
	{
		kill(pid, signal);
		exit(0);
	}
	g_str += 1;
	bit = 0;
	kill(pid, signal);
}

int	main(int argc, char *argv[])
{
	int		pid;

	if (argc < 3)
		return (0);
	pid = ft_atoi(argv[1]);
	if (pid < 1)
		return (1);
	g_str = argv[2];
	signal(SIGUSR1, signal_char);
	kill(pid, SIGUSR1);
	while (1) ;
	return (0);
}
