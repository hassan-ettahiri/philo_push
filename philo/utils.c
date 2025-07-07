/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hettahir <hettahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:19:58 by hettahir          #+#    #+#             */
/*   Updated: 2025/06/28 23:06:04 by hettahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (!(c >= '0' && c <= '9'))
		return (0);
	return (1);
}

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

long	ft_atoi(const char *s)
{
	int		num;
	int		tmp;
	size_t	i;

	i = 0;
	num = 0;
	tmp = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '-')
		return (0);
	else if (s[i] == '+')
		i++;
	while (ft_isdigit(s[i]))
	{
		tmp = (num * 10) + (s[i++] - 48);
		if (tmp < num)
			return (0);
		num = tmp;
	}
	return (num);
}

int	check_num(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		if (!((av[i][0] >= '0' && av[i][0] <= '9') || av[i][0] == '+'
				|| av[i][0] == '-'))
			return (write(2, "Error: input must be a number...", 33), 1);
		j++;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (write(2, "Error: input must be a number...", 33), 1);
			j++;
		}
		i++;
	}
	return (0);
}
