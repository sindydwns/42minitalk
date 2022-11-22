/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:07:47 by yonshin           #+#    #+#             */
/*   Updated: 2022/11/22 15:27:17 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_test1(int sig)
{
	ft_putstr_fd("sigusr1: ", 0);
	ft_putnbr_fd(sig, 0);
	ft_putchar_fd('\n', 0);
}

void	signal_test2(int sig, siginfo_t *info, void *old)
{
	signal_test1(sig);
	ft_putnbr_fd(info->si_pid, 0);
	ft_putchar_fd('\n', 0);
	old = 0;
	sleep(1);
	if (info->si_pid)
		kill(info->si_pid, SIGUSR1);
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
	while (1) ;
	return (0);
}
