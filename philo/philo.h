/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hettahir <hettahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:19:53 by hettahir          #+#    #+#             */
/*   Updated: 2025/07/11 01:20:45 by hettahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	int					meals;
	long long			last_meal;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	int					done_eating;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	int					n_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					must_eat;
	int					full_count;
	int					dead;
	int					philo_died;
	int					done_eating;
	long long			start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		death_check;
	pthread_mutex_t		meal_time_lock;
	pthread_mutex_t		start_simulation;
	pthread_mutex_t		musteat;
	pthread_mutex_t		timel;
	t_philo				*philos;
}						t_data;

size_t					ft_strlen(const char *s);
int						ft_isdigit(int c);
long					ft_atoi(const char *s);
int						check_num(int ac, char **av);

void					clean_mutexes(t_data *data);

int						set_inputs(t_data *data, int c, int i);
int						check_param(int ac, char **av, t_data *input);
int						check_num(int ac, char **av);
int						start_simulation(t_data *data);

long long				get_time(t_data *data);
void					waittt(int ms, int died, t_data *data);
int						print_itter(t_philo *p, char *msg);
int						check_death(t_philo *p);
void					*philo_routine(void *arg);

void					*monitor_routine(void *arg);

#endif