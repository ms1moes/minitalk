/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:36:51 by msimoes-          #+#    #+#             */
/*   Updated: 2022/05/26 15:27:57 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static char	*start_str(char c)
{
	char	*str;

	str = malloc(2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

static char	*add_char(char *str, char c)
{
	char	*new;
	int		i;

	if (!str)
		return (start_str(c));
	new = malloc((ft_strlen(str) + 2));
	if (!new)
	{
		free(str);
		return (NULL);
	}
	i = -1;
	while (str[++i])
		new[i] = str[i];
	free(str);
	new[i++] = c;
	new[i] = '\0';
	c = 0;
	return (new);
}

char	*print_free(char *str)
{
	write(1, str, ft_strlen(str));
	free(str);
	return (NULL);
}

void	s_handler(int sig, siginfo_t *siginfo, void *unused)
{
	static char				c = 0;
	static int				i = 0;
	static char				*str = NULL;
	static pid_t			c_pid = 0;

	(void)unused;
	if (c_pid)
		c <<= 1;
	if (!c_pid)
		c_pid = siginfo->si_pid;
	c |= (sig == SIGUSR1);
	if (++i == 8)
	{
		i = 0;
		if (c == 0)
		{
			str = print_free(str);
			c_pid = 0;
			return ;
		}
		str = add_char(str, c);
		kill(c_pid, SIGUSR1);
	}
	else
		kill(c_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;
	sigset_t			mask;

	write(1, "Server PID: ", 12);
	ft_putunbr(getpid());
	write(1, "\n", 1);
	sigfillset(&mask);
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sa.sa_mask = mask;
	sa.sa_sigaction = s_handler;
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	while (1)
		pause();
}
