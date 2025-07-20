/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hettahir <hettahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:19:47 by hettahir          #+#    #+#             */
/*   Updated: 2025/07/21 00:47:49 by hettahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_last_meal(t_philo *p)
{
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

int	take_fork_and_eat(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	pthread_mutex_lock(p->right_fork);
	if (print_itter(p, "has taken a fork") || print_itter(p,
			"has taken a fork"))
		return (update_last_meal(p), 1);
	pthread_mutex_lock(&p->data->meal_time_lock);
	p->last_meal = get_time(p->data);
	pthread_mutex_unlock(&p->data->meal_time_lock);
	if (print_itter(p, "is eating") == 1)
		return (pthread_mutex_unlock(p->left_fork),
			pthread_mutex_unlock(p->right_fork), 1);
	waittt(p->data->time_eat, p->data->time_die, p->data);
	p->meals++;
	return (0);
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
	waittt(p->data->time_sleep, p->data->time_die, p->data);
	if (print_itter(p, "is thinking") == 1)
		return (1);
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
		waittt(60, p->data->time_die, p->data);
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
