/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:07:47 by yonshin           #+#    #+#             */
/*   Updated: 2022/11/16 20:42:42 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void	signal_test(int sig)
{
	static int		buff;

	if (buff == 0)
		buff = 1;
	buff = buff << 1;
	if (sig == SIGUSR2)
		buff += 1;
	if (buff < 256)
		return ;
	buff -= 256;
	write(1, &buff, 1);
	buff = 0;
}

int	main(void)
{
	printf("%d\n", getpid());
	signal(SIGUSR1, signal_test);
	signal(SIGUSR2, signal_test);
	while (1) ;
}
