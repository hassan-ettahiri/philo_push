/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hettahir <hettahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:19:56 by hettahir          #+#    #+#             */
/*   Updated: 2025/07/21 00:52:36 by hettahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philo_1(void *arg)
{
	t_philo *philo = (t_philo*)arg;
	philo->data->start_time = get_time(philo->data);
	pthread_mutex_lock(philo->left_fork);
	print_itter(philo, "has taken a fork");
	waittt(philo->data->time_die, philo->data->time_die, philo->data);
	print_itter(philo, "died");
	return NULL;
}

void	one_philo(t_data *data)
{
	if(pthread_create(&data->philos[0].thread, NULL, philo_1, &data->philos[0]) != 0)
	{
		write(2, "Failed to create philo thread\n", 30);
		return ;
	}
	pthread_join(data->philos[0].thread, NULL);
}

void	clean_mutexes(t_data *data)
{
	pthread_mutex_destroy(data->forks);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->meal_check);
	pthread_mutex_destroy(&data->death_check);
	pthread_mutex_destroy(&data->meal_time_lock);
	pthread_mutex_destroy(&data->start_simulation);
	pthread_mutex_destroy(&data->musteat);
	pthread_mutex_destroy(&data->timel);
}

int	start_simulation(t_data *data)
{
	pthread_t	monitor;
	int			i;

	if (data->n_philo == 1)
		return (one_philo(data), 0);
	pthread_mutex_lock(&data->start_simulation);
	i = -1;
	while (++i < data->n_philo)
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]) != 0)
			return (write(2, "Failed to create philo thread\n", 30), 1);
	1 && (data->start_time = get_time(data), i = 0);
	while (i < data->n_philo)
		data->philos[i++].last_meal = data->start_time;
	pthread_mutex_unlock(&data->start_simulation);
	if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
		return (write(2, "Failed to create monitor thread\n", 32), 1);
	i = 0;
	while (i < data->n_philo)
		pthread_join(data->philos[i++].thread, NULL);
	pthread_join(monitor, NULL);
	clean_mutexes(data);
	return (0);
}
