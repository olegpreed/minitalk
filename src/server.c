/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 19:13:35 by preed             #+#    #+#             */
/*   Updated: 2022/05/05 18:33:37 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_reciever[2];

void	this_is_the_end(siginfo_t *sig)
{
	if (kill(sig->si_pid, SIGUSR2) == -1)
		write(1, "KillError!\n", 11);
	write(1, "\n", 1);
}

void	print_saved(char **p, char a, siginfo_t *sig, int *i)
{
	write(1, *p, ft_strlen(*p));
	free(*p);
	*i = 2;
	*p = NULL;
	if (a == '\0')
		this_is_the_end(sig);
}

void	action(int signum, siginfo_t *sig, void *context)
{
	static int	n = 128;
	static char	a;
	static char	*p = NULL;
	static int	i = 2;

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
		ft_strlcat(p, &a, i++);
		n = 128;
		if (i == 10001 || a == '\0')
			print_saved(&p, a, sig, &i);
		a = 0;
	}
	g_reciever[0] = 1;
	g_reciever[1] = sig->si_pid;
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
		write(1, "Sigerror!\n", 10);
		return (0);
	}
	while (1)
	{
		while (!g_reciever[0])
			;
		g_reciever[0] = 0;
		if (kill(g_reciever[1], SIGUSR1) == -1)
			write(1, "KillError!\n", 11);
	}
	return (0);
}
