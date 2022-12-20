/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@student.42kocaeli.com.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:20:05 by hsozan            #+#    #+#             */
/*   Updated: 2022/10/03 15:42:53 by hsozan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

int	ft_atoi(char *s)
{
	int	i;
	int	res;
	int	n;

	i = 0;
	n = 1;
	while (s[i] <= 32)
		i++;
	if (s[i] == '+')
		i++;
	else if (s[i] == '-')
	{
		n = -1;
		i++;
	}
	while (s[i] <= '9' && s[i] >= '0')
	{
		res = (res * 10) + (s[i] - '0');
		i++;
	}
	return (res * n);
}

int	main(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	if (ac != 3)
		return (write(2, "Eksik veya fazla argüman!", 27));
	while (av[2][i])
	{
		j = 8;
		while (j--)
		{
			if ((av[2][i] >> j) % 2 == 0)
				kill(ft_atoi(av[1]), SIGUSR1);
			else
				kill(ft_atoi(av[1]), SIGUSR2);
			usleep(70);
		}
		i++;
	}
	return (0);
}
