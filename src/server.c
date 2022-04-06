/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 19:13:35 by preed             #+#    #+#             */
/*   Updated: 2022/04/06 16:01:54 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
		ft_strlcat(p, &a, i++);
		n = 128;
		if (a == '\n' || i == 10001)
		{
			write(1, p, ft_strlen(p));
			// printf("\ni = %d\n", i);
			// printf("p length = %d\n", ft_strlen(p));
			free(p);
			i = 2;
			p = NULL;
		}
		a = 0;
	}
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
