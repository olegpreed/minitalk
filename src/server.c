/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 19:13:35 by preed             #+#    #+#             */
/*   Updated: 2022/04/01 21:00:08 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	action(int signum, siginfo_t *sig, void *context)
{
	static int	n = 128;
	static char	a = 0;

	(void)sig;
	(void)context;
	if (n == 0)
	{
		write(1, "\n", 1);
		n = 64;
		a = 0;
	}
	if (signum == SIGUSR2)
	{
		write(1, "1", 1);
		a = a | n;
	}
	else if (signum == SIGUSR1)
	{
		write(1, "0", 1);
		a = a | 0;
	}
	n /= 2;
}

int	main(void)
{
	int					id;
	char				*pid;
	struct sigaction	sigac;

	id = getpid();
	pid = ft_itoa(id);
	write(1, pid, ft_strlen(pid));
	write(1, "\n", 1);
	sigac.sa_flags = SA_SIGINFO;
	sigac.sa_sigaction = action;
	sigaction(SIGUSR1, &sigac, NULL);
	sigaction(SIGUSR2, &sigac, NULL);
	while (1)
		;
	return (0);
}
