/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@student.42kocaeli.com.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:20:17 by hsozan            #+#    #+#             */
/*   Updated: 2022/10/31 13:00:11 by hsozan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void	connection_terminate(pid_t server_pid)
{
	int	i;

	i = 8;
	while (i--)
	{
		usleep(50);
		kill(server_pid, SIGUSR2);
	}
	exit(0);
}

int	ft_strlen_or_putnbr(int nbr, char *s)
{
	char	c;
	int		i;
	int		res;

	i = 0;
	if (nbr == -1)
	{
		while (s[i++])
			;
		return (i);
	}
	if (nbr == -2 && s)
	{
		res = 0;
		while (s[i] <= '9' && s[i] >= '0')
		{
			res = (res * 10) + (s[i] - '0');
			i++;
		}
		return (res);
	}
	if (nbr >= 10)
		ft_strlen_or_putnbr(nbr / 10, s);
	c = (nbr % 10) + 48;
	return (write(1, &c, 1));
}

void	send_bit(char *s, pid_t pid)
{
	static int				i = 8;
	static unsigned char	c;
	static char				*str;
	static pid_t			server_pid;

	if (s)
	{
		str = s;
		server_pid = pid;
		c = *str;
	}
	if (!i)
	{
		i = 8;
		c = *(++str);
		if (!c)
			connection_terminate(server_pid);
	}
	if (c && c >> --i & 1)
		kill(server_pid, SIGUSR1);
	else if (c)
		kill(server_pid, SIGUSR2);
}

void	sig_handler(int sig, siginfo_t *siginfo, void *unused)
{
	static int	recv_bytes = 0;

	(void)siginfo;
	(void)unused;
	if (sig == SIGUSR1)
	{
		write(1, "\rReceived bytes : ", 16);
		ft_strlen_or_putnbr(++recv_bytes, 0);
	}
	send_bit(0, 0);
}

int	main(int argc, char **argv)
{
	struct sigaction	e;

	if (argc != 3)
	{
		write(1, "Usage : ./client [99 < Server PID < 99999] [Message]", 52);
		return (0);
	}
	e.sa_flags = SA_SIGINFO;
	e.sa_sigaction = sig_handler;
	sigaction(SIGUSR1, &e, 0);
	sigaction(SIGUSR2, &e, 0);
	send_bit(argv[2], ft_strlen_or_putnbr(-2, argv[1]));
	while (1)
		pause();
}
