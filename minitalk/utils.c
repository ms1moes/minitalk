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

void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		ft_putchar(str[i]);
}

int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}

void	ft_putunbr(unsigned int n)
{
	if (n >= 10)
		ft_putunbr((n / 10));
	ft_putchar((n % 10) + '0');
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
