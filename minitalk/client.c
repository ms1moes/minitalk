/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 18:08:07 by msimoes-          #+#    #+#             */
/*   Updated: 2022/05/25 20:06:14 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

static int	ft_verify_input(int ac, char **av)
{
	int	i;

	i = -1;
	if (ac != 3)
		return (1);
	while (av[1][++i])
	{
		if (ft_isdigit(av[1][i]) == 0)
			return (1);
	}
	return (0);
}

static void	reply(int sig)
{
	if (sig == SIGUSR1)
		ft_putstr("[message received]\n");
}

static void	ft_char_to_bits(unsigned char c, int pid)
{
	int		i;

	i = 8;
	while (i--)
	{
		if ((c % 2) == 1)
			kill(pid, SIGUSR2);
		if ((c % 2) == 0)
			kill(pid, SIGUSR1);
		usleep(500);
		c /= 2;
	}
}

int	main(int ac, char **av)
{
	int		pid;
	int		i;
	char	*msg;

	if (ft_verify_input(ac, av))
	{
		ft_putstr("Input error!\n");
		return (0);
	}
	pid = ft_atoi(av[1]);
	msg = av[2];
	i = -1;
	signal(SIGUSR1, reply);
	signal(SIGUSR2, reply);
	while (msg[++i])
		ft_char_to_bits(msg[i], pid);
	ft_char_to_bits('\n', pid);
	ft_char_to_bits('\0', pid);
}
