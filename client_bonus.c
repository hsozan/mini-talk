/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@student.42kocaeli.com.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:20:17 by hsozan            #+#    #+#             */
/*   Updated: 2022/10/03 15:43:06 by hsozan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

int	ft_strlen_or_putnbr(int nbr, char *s)
{
	char	c;
	int		i;

	i = 0;
	if (nbr == -1)
	{
		while(str[i++])
		return (i)
	}
	if (nbr >= 10)
		ft_strlen_or_putnbr(nbr / 10);
	c = (nbr % 10) + 48;
	return(write(1, &c, 1));
}

int	ft_atoi(char *s)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (s[i] <= '9' && s[i] >= '0')
	{
		res = (res * 10) + (s[i] - '0');
		i++;
	}
	return (res);
}

void	send(int pid, char c)
{
	int	i;

	i = 128;
	while (i > 0)
	{
		if (c & i)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(100);
		i /= 2;
	}
}

void	send_msg(int pid, char *s, int *g)
{
	int		i;
	char	c;

	c = '\r';
	i = 0;
	send(pid, c);
	while (s[i])
	{
        send(pid, s[i]);
		i++;
		(*g)++;
	}
}

int	main(int ac, char **av)
{
	int		i;
	int		j;
	int		g;

	i = 0;
	j = 0;
	g = 0;
	if (ac != 3)
		return (write(1, "Too many or too few arguments!\n", 32));
	send_msg(ft_atoi(av[1]), av[2], &g);
	if (g == ft_strlen_or_putnbr(-1,av[2]))
	{
		ft_strlen_or_putnbr(g);
		write(1, " characters send to pid number :", 32);
		ft_strlen_or_putnbr(ft_atoi(av[1]));
		write(1, "\n", 1);
	}
	return (0);
}
