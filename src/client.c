/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 18:35:30 by preed             #+#    #+#             */
/*   Updated: 2022/05/05 18:33:28 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_reciever;

void	char_to_bits(char sign, int pid)
{
	int	n;

	n = 128;
	while (n > 0)
	{
		g_reciever = 0;
		if ((sign & n) > 0)
		{
			if (kill(pid, SIGUSR2) == -1)
				write(1, "KillError!\n", 11);
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				write(1, "KillError!\n", 11);
		}
		n /= 2;
		while (!g_reciever)
			;
	}
}

void	send_nudes(int pid, char *msg)
{
	while (*msg)
	{
		char_to_bits(*msg, pid);
		msg++;
	}
	char_to_bits(*msg, pid);
}

int	check(char *argv, int *pid_p)
{
	t_lli	num;

	num = ft_atoi(argv);
	if (num > 2147483647 || num <= 0)
		return (0);
	*pid_p = num;
	return (1);
}

void	listen(int signum, siginfo_t *sig, void *context)
{
	(void)sig;
	(void)context;
	if (signum == SIGUSR2)
		write(1, "Great success!\n", 15);
	g_reciever = 1;
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sigac;

	g_reciever = 1;
	pid = 0;
	sigac.sa_flags = SA_SIGINFO;
	sigac.sa_sigaction = listen;
	if ((sigaction(SIGUSR1, &sigac, NULL) == -1)
		|| (sigaction(SIGUSR2, &sigac, NULL) == -1))
	{
		write(1, "Sigerror!\n", 10);
		return (0);
	}
	if (argc == 3 && check(argv[1], &pid))
		send_nudes(pid, argv[2]);
	return (0);
}
