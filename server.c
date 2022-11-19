/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:07:47 by yonshin           #+#    #+#             */
/*   Updated: 2022/11/17 02:02:39 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
	signal(SIGUSR1, signal_test);
	signal(SIGUSR2, signal_test);
	while (1) ;
}
