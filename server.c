/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:07:47 by yonshin           #+#    #+#             */
/*   Updated: 2022/11/22 17:17:44 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	init_sig(t_sig *sig, int pid)
{
	sig->pid = pid;
	sig->c = 0;
	sig->i = 0;
}

void	signal_test2(int sig, siginfo_t *info, void *old)
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
	struct sigaction usrsig;

	ft_putnbr_fd(getpid(), 0);
	ft_putchar_fd('\n', 0);
	usrsig.sa_sigaction = signal_test2;
	sigemptyset(&usrsig.sa_mask);
	usrsig.sa_flags = 0;
	usrsig.sa_flags = SA_SIGINFO | SA_NODEFER;
	if (sigaction(SIGUSR1, &usrsig, 0) == -1)
		exit(1);
	if (sigaction(SIGUSR2, &usrsig, 0) == -1)
		exit(1);
	while (1) ;
	return (0);
}
