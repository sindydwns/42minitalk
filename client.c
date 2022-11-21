/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:07:44 by yonshin           #+#    #+#             */
/*   Updated: 2022/11/21 01:49:41 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

static char *get_message(int argc, char *argv[])
{
	if (argc < 3)
		exit(1);
	if (argv[2] == NULL)
		exit(1);
	return (argv[2]);
}

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
	kill(info->si_pid, SIGUSR1);
}

int	main(int argc, char *argv[])
{
	const int			pid = get_pid(argc, argv);
	const char			*message = get_message(argc, argv);
	struct sigaction	usrsig;

	usrsig.sa_sigaction = signal_test2;
	sigemptyset(&usrsig.sa_mask);
	usrsig.sa_flags = 0;
	usrsig.sa_flags = SA_NODEFER | SA_SIGINFO;
	if (sigaction(SIGUSR1, &usrsig, 0) == -1)
		exit(1);
	kill(pid, SIGUSR1);
	message++;
	while (1) ;
	return (0);
}
