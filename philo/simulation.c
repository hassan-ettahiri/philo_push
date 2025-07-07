/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hettahir <hettahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:19:56 by hettahir          #+#    #+#             */
/*   Updated: 2025/07/06 19:35:51 by hettahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_philo *p)
{
	p->data->start_time = get_time();
	print_itter(p, "has taken a fork");
	waittt(p->data->time_die, p->data->time_die);
	print_itter(p, "died");
}

void	start_simulation(t_data *data)
{
	pthread_t	monitor;
	int			i;

	if (data->n_philo == 1)
	{
		one_philo(&data->philos[0]);
		return ;
	}
	pthread_mutex_lock(&data->start_simulation);
	i = -1;
	while (++i < data->n_philo)
		if(pthread_create(&data->philos[i].thread, NULL, philo_routine,
			&data->philos[i]) != 0)
			write(2, "Failed to create philo thread\n", 32);
	data->start_time = get_time();
	i = 0;
	while (i < data->n_philo)
		data->philos[i++].last_meal = data->start_time;
	pthread_mutex_unlock(&data->start_simulation);
	if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
		write(2, "Failed to create monitor thread\n", 32);
	i = 0;
	while (i < data->n_philo)
		pthread_join(data->philos[i++].thread, NULL);
	pthread_detach(monitor);
}
