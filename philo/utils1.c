/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hettahir <hettahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:20:00 by hettahir          #+#    #+#             */
/*   Updated: 2025/07/09 15:10:03 by hettahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(t_data *data)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
	{
		pthread_mutex_lock(&data->timel);
		write(2, "Error: gettimeofday() failed\n", 29);
		pthread_mutex_unlock(&data->timel);
		return (-1);
	}
	return ((time.tv_sec * 1000LL) + (time.tv_usec / 1000));
}

void	waittt(int ms, int died, t_data *data)
{
	long long	start;

	if (died < ms)
		ms = died;
	start = get_time(data);
	while ((get_time(data) - start) < ms)
		usleep(50);
}

int	print_itter(t_philo *p, char *msg)
{
	long long	now;

	pthread_mutex_lock(&p->data->print);
	pthread_mutex_lock(&p->data->death_check);
	if (p->data->dead)
	{
		pthread_mutex_unlock(&p->data->death_check);
		pthread_mutex_unlock(&p->data->print);
		return (1);
	}
	pthread_mutex_unlock(&p->data->death_check);
	now = get_time(p->data) - p->data->start_time;
	printf("%lld %d %s\n", now, p->id, msg);
	pthread_mutex_unlock(&p->data->print);
	return (0);
}
