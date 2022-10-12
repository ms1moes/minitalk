/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:36:45 by msimoes-          #+#    #+#             */
/*   Updated: 2022/05/05 16:36:45 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(char *str)
{
	int	number;

	number = 0;
	while (ft_isdigit(*str))
		number = (number * 10) + (*(str++) - 48);
	return (number);
}

size_t   ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void	ft_putunbr(unsigned int n)
{
	if (n >= 10)
		ft_putunbr((n / 10));
	write(1, &"0123456789"[n % 10], 1);
}

int	ft_verify_input(int ac, char **av)
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
