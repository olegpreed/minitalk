/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 18:35:30 by preed             #+#    #+#             */
/*   Updated: 2022/04/01 20:38:23 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	char_to_bits(char sign, int pid)
{
	int	n;

	n = 64;
	kill(pid, SIGUSR1);
	while (n > 0)
	{
		if ((sign & n) > 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		n /= 2;
	}
}

void	send_nudes(int pid, char *msg)
{
	while (*msg)
	{
		char_to_bits(*msg, pid);
		msg++;
	}
}

int check(char *argv, int *pid_p)
{
	LLI	num;

	num = ft_atoi(argv);
	if (num > 2147483647 || num <= 0)
		return (0);
	*pid_p = num;
	return (*pid_p);
}

int	main(int argc, char **argv)
{
	int	pid;

	pid = 0;
	if (argc == 3 && check(argv[1], &pid))
		send_nudes(pid, argv[2]);
	return (0);
}