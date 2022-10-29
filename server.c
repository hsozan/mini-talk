/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@student.42kocaeli.com.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:21:07 by hsozan            #+#    #+#             */
/*   Updated: 2022/10/29 14:35:16 by hsozan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <signal.h>
#include <unistd.h>

int	g_i = 128;

void	ft_put_nbr(int nbr)
{
	char	c;

	if (nbr >= 10)
		ft_put_nbr(nbr / 10);
	c = (nbr % 10) + 48;
	write(1, &c, 1);
}

void	msg(int s)
{
	static char	c;

	if (s == 11)
		c += g_i;
	g_i /= 2;
	if (g_i == 0)
	{
		write(1, &c, 1);
		c = 0;
		g_i = 128;
	}
}

int	main(void)
{
	write(1, "Pid: ", 5);
	ft_put_nbr(getpid());
	write(1, "\n", 1);
	signal(10, msg);
	signal(11, msg);
	while (1)
		pause();
	return (0);
}
