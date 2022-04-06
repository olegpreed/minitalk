/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 18:35:30 by preed             #+#    #+#             */
/*   Updated: 2022/04/05 18:56:39 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	char_to_bits(char sign, int pid)
{
	int	n;

	n = 128;
	usleep(25);
	while (n > 0)
	{
		if ((sign & n) > 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		n /= 2;
		usleep(40);
	}
}

void	send_new_line(int pid)
{
	int		n;
	char	new_line;

	n = 128;
	new_line = '\n';
	usleep(1);
	while (n > 0)
	{
		if ((new_line & n) > 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		n /= 2;
		usleep(30);
	}
}

void	send_nudes(int pid, char *msg)
{
	while (*msg)
	{
		char_to_bits(*msg, pid);
		msg++;
	}
	send_new_line(pid);
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

int	main(int argc, char **argv)
{
	int	pid;

	pid = 0;
	if (argc == 3 && check(argv[1], &pid))
		send_nudes(pid, argv[2]);
	return (0);
}
