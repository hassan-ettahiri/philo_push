/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hettahir <hettahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:19:47 by hettahir          #+#    #+#             */
/*   Updated: 2025/07/07 10:40:56 by hettahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork_and_eat(t_philo *p)
{
	if (p->left_fork < p->right_fork)
	{
		pthread_mutex_lock(p->left_fork);
		pthread_mutex_lock(p->right_fork);
	}
	else
	{
		pthread_mutex_lock(p->right_fork);
		pthread_mutex_lock(p->left_fork);
	}
	if (print_itter(p, "has taken a fork") == 1)
		return (pthread_mutex_unlock(p->left_fork),
			pthread_mutex_unlock(p->right_fork), 1);
	if (print_itter(p, "has taken a fork") == 1)
		return (pthread_mutex_unlock(p->left_fork),
			pthread_mutex_unlock(p->right_fork), 1);
	pthread_mutex_lock(&p->data->meal_time_lock);
	p->last_meal = get_time();
	pthread_mutex_unlock(&p->data->meal_time_lock);
	if (print_itter(p, "is eating") == 1)
		return (pthread_mutex_unlock(p->left_fork),
			pthread_mutex_unlock(p->right_fork), 1);
	waittt(p->data->time_eat, p->data->time_die);
	p->meals++;
	return (0);
}

void	update_last_meal(t_philo *p)
{
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

int	check_all_philos_eat(t_philo *p)
{
	pthread_mutex_lock(&p->data->musteat);
	if (p->data->must_eat > 0 && p->meals == p->data->must_eat
		&& !p->done_eating)
	{
		pthread_mutex_unlock(&p->data->musteat);
		p->done_eating = 1;
		pthread_mutex_lock(&p->data->meal_check);
		p->data->full_count++;
		pthread_mutex_unlock(&p->data->meal_check);
		return (1);
	}
	pthread_mutex_unlock(&p->data->musteat);
	return (0);
}

int	sleep_and_think(t_philo *p)
{
	if (print_itter(p, "is sleeping") == 1)
		return (1);
	waittt(p->data->time_sleep, p->data->time_die);
	if (print_itter(p, "is thinking") == 1)
		return (1);
	if(p->data->n_philo % 2 != 0)
		usleep(50);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	pthread_mutex_lock(&p->data->start_simulation);
	pthread_mutex_unlock(&p->data->start_simulation);
	if (!p || !p->data)
		return (write(2, "invalid thread data\n", 20), NULL);
	if (p->id % 2 == 0)
		waittt(60, p->data->time_die);
	while (1)
	{
		if (take_fork_and_eat(p) == 1)
			break ;
		update_last_meal(p);
		if (check_all_philos_eat(p) == 1)
			break ;
		if (sleep_and_think(p) == 1)
			break ;
	}
	return (NULL);
}
