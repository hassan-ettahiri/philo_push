/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hettahir <hettahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:19:37 by hettahir          #+#    #+#             */
/*   Updated: 2025/07/09 10:22:07 by hettahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_inputs(t_data *data, int c, int i)
{
	if (i == 1)
		data->n_philo = c;
	if (i == 2)
		data->time_die = c;
	if (i == 3)
		data->time_eat = c;
	if (i == 4)
		data->time_sleep = c;
	if (i == 5)
		data->must_eat = c;
	else
		data->must_eat = -1;
	data->dead = 0;
	data->full_count = 0;
	return (1);
}

int	set_mutex(t_data *data)
{
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->meal_check, NULL);
	pthread_mutex_init(&data->meal_time_lock, NULL);
	pthread_mutex_init(&data->death_check, NULL);
	pthread_mutex_init(&data->start_simulation, NULL);
	pthread_mutex_init(&data->musteat, NULL);
	pthread_mutex_init(&data->timel, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->forks)
	{
		printf("Error: Memory allocation failed\n");
		return (0);
	}
	return (1);
}

int	set_thread(t_data *data)
{
	int	d;

	data->philos = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philos)
	{
		printf("Error: Memory allocation failed\n");
		return (0);
	}
	d = 0;
	while (d < data->n_philo)
		pthread_mutex_init(&data->forks[d++], NULL);
	d = 0;
	while (d < data->n_philo)
	{
		data->philos[d].id = d + 1;
		data->philos[d].meals = 0;
		data->philos[d].last_meal = 0;
		data->philos[d].left_fork = &data->forks[d];
		data->philos[d].right_fork = &data->forks[(d + 1) % data->n_philo];
		data->philos[d++].data = data;
	}
	return (1);
}

int	check_param(int ac, char **av, t_data *data)
{
	int	i;
	int	c;

	i = 1;
	while (i < ac)
	{
		c = ft_atoi((const char *)av[i]);
		if (c == 0)
			return (write(2, "Error: input must be between 1 and 2147483647...",
					49), 1);
		if (c == -1)
			return (write(2, "Error: input must be positive...", 33), 1);
		if (set_inputs(data, c, i) == 0)
			return (1);
		i++;
	}
	if (set_mutex(data) == 0 || set_thread(data) == 0)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!(ac == 5 || ac == 6))
		return (write(2, "Error: invalid number of parameter...", 38), 1);
	if (check_num(ac, av) == 1 || check_param(ac, av, &data) == 1)
		return (1);
	if (get_time(&data) < 0)
		return (free(data.forks), free(data.philos), 1);
	if (start_simulation(&data) == 1)
		return (free(data.forks), free(data.philos), 1);
	free(data.forks);
	free(data.philos);
	return (0);
}
