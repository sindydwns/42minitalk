/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:07:47 by yonshin           #+#    #+#             */
/*   Updated: 2022/11/24 08:37:41 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	init_sig(t_sig *sig, int pid)
{
	sig->pid = pid;
	sig->c = 0;
	sig->i = 0;
}

void	sigaction_func(int sig, siginfo_t *info, void *old)
{
	static t_sig	rev;

	old = 0;
	if (rev.pid != info->si_pid)
	{
		init_sig(&rev, info->si_pid);
		kill(info->si_pid, SIGUSR1);
		return ;
	}
	rev.c = (rev.c << 1) + (sig == SIGUSR2);
	if (++rev.i == END_OF_BYTE)
	{
		write(1, &rev.c, 1);
		if (rev.c == 0)
		{
			write(1, "\n", 1);
			kill(rev.pid, SIGUSR2);
			return ;
		}
		init_sig(&rev, info->si_pid);
	}
	if (rev.i != END_OF_BYTE || rev.c != 0)
		kill(rev.pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	act;

	ft_putnbr_fd(getpid(), 0);
	ft_putchar_fd('\n', 0);
	act.sa_sigaction = sigaction_func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO | SA_NODEFER;
	if (sigaction(SIGUSR1, &act, 0) == -1)
		exit(1);
	if (sigaction(SIGUSR2, &act, 0) == -1)
		exit(1);
	while (1)
		;
	return (0);
}
