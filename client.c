/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:07:44 by yonshin           #+#    #+#             */
/*   Updated: 2022/11/22 17:54:11 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static char	*g_message;

static int	get_pid(int argc, char *argv[])
{
	int	pid;

	if (argc < 2)
		exit(1);
	if (argv[1] == NULL)
		exit(1);
	pid = ft_atoi(argv[1]);
	if (pid < 1)
		exit(1);
	return (pid);
}

static char	*get_message(int argc, char *argv[])
{
	if (argc < 3)
		exit(1);
	if (argv[2] == NULL)
		exit(1);
	return (argv[2]);
}

void	sigaction_func(int sig, siginfo_t *info, void *old)
{
	static t_sig	send;
	int				res;

	sig = 0;
	old = 0;
	if (send.i == 0)
		send.c = *g_message;
	if (++send.i == END_OF_BYTE)
	{
		g_message++;
		send.i = 0;
	}
	if ((send.c & 0b10000000) / 0b10000000)
		res = SIGUSR2;
	else
		res = SIGUSR1;
	send.c = send.c << 1;
	kill(info->si_pid, res);
}

void	signal_exit(int sig)
{
	if (sig == SIGUSR2)
		exit(0);
}

int	main(int argc, char *argv[])
{
	const int			pid = get_pid(argc, argv);
	struct sigaction	usrsig;

	g_message = get_message(argc, argv);
	usrsig.sa_sigaction = sigaction_func;
	sigemptyset(&usrsig.sa_mask);
	usrsig.sa_flags = 0;
	usrsig.sa_flags = SA_NODEFER | SA_SIGINFO;
	if (sigaction(SIGUSR1, &usrsig, 0) == -1)
		exit(1);
	if (signal(SIGUSR2, signal_exit) == SIG_ERR)
		exit(1);
	kill(pid, SIGUSR1);
	while (1)
		;
	return (0);
}
