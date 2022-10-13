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

void	end_prog(pid_t s_pid)
{
	int	i;

	i = 8;
	while (i--)
	{
		usleep(50);
		kill(s_pid, SIGUSR2);
	}
	write(1, "\nfinished successfully\n", 22);
	exit(0);
}

void	send_bit(pid_t pid, char *s)
{
	static int				i = 8;
	static char				c;
	static char				*str;
	static pid_t			s_pid;

	if (s)
	{
		str = s;
		s_pid = pid;
		c = *str;
	}
	if (!i)
	{
		i = 8;
		c = *(++str);
		if (!c)
			end_prog(s_pid);
	}
	if (c >> --i & 1)
		kill(s_pid, SIGUSR1);
	else
		kill(s_pid, SIGUSR2);
}

void	c_handler(int sig)
{
	static int	bytes = 0;

	if (sig == SIGUSR1)
	{
		write(1, "\rnumber of bytes:  ", 19);
		ft_putunbr(++bytes);
	}
	send_bit(0, NULL);
}

int	main(int ac, char **av)
{
	if (ft_verify_input(ac, av))
	{
		write(1, "Error: invalid input\n", 21);
		return (1);
	}
	signal(SIGUSR1, c_handler);
	signal(SIGUSR2, c_handler);
	if (!ft_strlen(av[2]))
		exit(0);
	send_bit(ft_atoi(av[1]), av[2]);
	while(1)
		pause();
}
