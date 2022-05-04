/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 18:35:30 by preed             #+#    #+#             */
/*   Updated: 2022/05/04 15:18:14 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile	sig_atomic_t	reciever;

void	char_to_bits(char sign, int pid)
{
	int	n;

	n = 128;
	while (n > 0)
	{
		reciever = 0;
		if ((sign & n) > 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		n /= 2;
		usleep(100000);
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
	return (*pid_p);
}

void	listen(int signum, siginfo_t *sig, void *context)
{
	static int	i;

	(void)sig;
	(void)context;
	if (signum == SIGUSR1)
		i++;
	else
		printf("All %d chars have been transferred! No one got hurt!", i / 8);
	reciever = 1;
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sigac;

	reciever = 1;
	pid = 0;
	sigac.sa_flags = SA_SIGINFO;
	sigac.sa_sigaction = listen;
	if (sigaction(SIGUSR1, &sigac, NULL) < 0)
		return (0);
	if (sigaction(SIGUSR2, &sigac, NULL) < 0)
		return (0);
	if (argc == 3 && check(argv[1], &pid))
		send_nudes(pid, argv[2]);
	return (0);
}
