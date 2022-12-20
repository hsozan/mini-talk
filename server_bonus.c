/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@student.42kocaeli.com.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:20:53 by hsozan            #+#    #+#             */
/*   Updated: 2022/10/26 10:30:06 by hsozan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

void	ft_putnbr(int nbr)
{
	char	c;

	if (nbr >= 10)
		ft_putnbr(nbr / 10);
	c = (nbr % 10) + 48;
	write(1, &c, 1);
}

void	sig_handler(int sig, siginfo_t *siginfo, void *unused)
{
	static unsigned char	c = 0;
	static int				cnt = 0;
	static pid_t			client_pid = 0;

	(void)unused;
	if (!client_pid)
		client_pid = siginfo->si_pid;
	c |= (sig == SIGUSR1);
	if (++cnt == 8)
	{
		cnt = 0;
		if (c == 0)
		{
			client_pid = 0;
			return ;
		}
		write(1, &c, 1);
		c = 0;
		kill(client_pid, SIGUSR1);
	}
	else
	{
		c <<= 1;
		kill(client_pid, SIGUSR2);
	}
}
//✅🔥⌚☣☮🌏📱Ⅻ🚀€🍔🍦👑⚽🎵🎧

int	main(void)
{
	struct sigaction	e;

	write(1, "Server PID = [", 14);
	ft_putnbr(getpid());
	write(1, "]\n", 2);
	e.sa_flags = SA_SIGINFO;
	e.sa_sigaction = sig_handler;
	write(1, "Waiting for client...\n", 22);
	sigaction(SIGUSR1, &e, 0);
	sigaction(SIGUSR2, &e, 0);
	while (1)
		pause();
	return (0);
}
