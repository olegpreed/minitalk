/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 19:13:35 by preed             #+#    #+#             */
/*   Updated: 2022/05/04 16:33:30 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile	sig_atomic_t	reciever[2];

void	action(int signum, siginfo_t *sig, void *context)
{
	static int	n = 128;
	static char	a;
	static char	*p = NULL;
	static int	i = 2;

	(void)sig;
	(void)context;
	if (!p)
		p = ft_calloc(10000, sizeof(char));
	if (!p)
		return ;
	if (signum == SIGUSR2)
		a = a | n;
	n = n / 2;
	if (n == 0)
	{
		strlcat(p, &a, i++);
		n = 128;
		if (i == 10001 || a == '\0')
		{
			write(1, p, ft_strlen(p));
			free(p);
			i = 2;
			p = NULL;
			if (a == '\0')
			{
				if (kill(sig->si_pid, SIGUSR2) == -1)
				{
					write(1, "Error!", 6);
					return ;
				}
				write(1, "\n", 1);
				return ;
			}
		}
		a = 0;
	}
	reciever[0] = 1;
	reciever[1] = sig->si_pid;
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
	if ((sigaction(SIGUSR1, &sigac, NULL) == -1)
		|| (sigaction(SIGUSR2, &sigac, NULL) == -1))
	{
		write(1, "Sigerror!", 9);
		return (0);
	}
	while (1)
	{
		while (!reciever[0])
		{
		}
		reciever[0] = 0;
		kill(reciever[1], SIGUSR1);
	}
	return (0);
}
