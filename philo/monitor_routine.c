/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hettahir <hettahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:19:45 by hettahir          #+#    #+#             */
/*   Updated: 2025/07/07 12:11:03 by hettahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_every_philo_death(t_data *d)
{
	int			i;
	long long	time_since_meal;

	i = 0;
	while (i < d->n_philo)
	{
		pthread_mutex_lock(&d->meal_time_lock);
		time_since_meal = get_time() - d->philos[i].last_meal;
		pthread_mutex_unlock(&d->meal_time_lock);
		if (time_since_meal >= d->time_die)
		{
			pthread_mutex_lock(&d->death_check);
			d->dead = 1;
			pthread_mutex_unlock(&d->death_check);
			pthread_mutex_lock(&d->print);
			printf("%lld %d died\n", get_time() - d->start_time,
				d->philos[i].id);
			pthread_mutex_unlock(&d->print);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_all_philos_eat_nb_time(t_data *d)
{
	pthread_mutex_lock(&d->musteat);
	if (d->must_eat > 0)
	{
		pthread_mutex_unlock(&d->musteat);
		pthread_mutex_lock(&d->meal_check);
		if (d->full_count == d->n_philo)
		{
			pthread_mutex_unlock(&d->meal_check);
			pthread_mutex_lock(&d->death_check);
			d->dead = 1;
			pthread_mutex_unlock(&d->death_check);
			return (1);
		}
		pthread_mutex_unlock(&d->meal_check);
	}
	else
		pthread_mutex_unlock(&d->musteat);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*d;

	d = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&d->death_check);
		if (d->dead)
		{
			pthread_mutex_unlock(&d->death_check);
			break ;
		}
		pthread_mutex_unlock(&d->death_check);
		if (check_all_philos_eat_nb_time(d) == 1 || check_every_philo_death(d) == 1)
			break ;
		usleep(100);
	}
	return (NULL);
}
