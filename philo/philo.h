/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:11:15 by njackson          #+#    #+#             */
/*   Updated: 2024/06/10 13:12:07 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <pthread.h>

# define USAGE "./philo NUM_PHILOS TIME_TO_DIE TIME_TO_EAT TIME_TO_SLEEP \
[TIMES_TO_EAT]\n"

typedef unsigned int	t_uint;
typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_tv;

typedef struct s_philo	t_philo;

typedef struct s_philo_dat
{
	int			num_philo;
	int			die_time;
	int			eat_time;
	int			sleep_time;
	int			to_eat;
	int			death;
	t_mutex		death_lock;
	t_mutex		*fork_mutex;
	t_mutex		print_lock;
	t_mutex		eat_lock;
	char		*fork;
	pthread_t	*threads;
	t_tv		start_time;
	t_philo		*philos;
}	t_philo_dat;

typedef struct s_philo
{
	int			num;
	t_philo_dat	*dat;
	int			eaten;
	t_mutex		eaten_lock;
	char		state;
	int			left_fork;
	int			right_fork;
	t_tv		action_time;
	t_tv		last_meal;
}	t_philo;

int			set_philo_dat(int ac, char **av, t_philo_dat *dat);
int			set_mutexes(t_philo_dat *dat);
void		delete_dat(t_philo_dat *dat);
pthread_t	*init_threads(t_philo_dat *dat);
void		philo_manage(t_philo_dat *dat);

// philo functions
void		philo_start(t_philo *philo);
int			philo_death(t_philo *philo, int last_meal);
void		philo_eat(t_philo *philo);
void		philo_think(t_philo *philo);

// mutex functions
int			check_mutex_int(int *addr, t_mutex *lock);
void		add_mutex_int(int *addr, t_mutex *lock, int add);

// libft functions
t_uint		ft_atou_strict(const char *str, int *err);
int			time_dif(t_tv start, t_tv *time);
void		print_action(t_philo *philo, t_tv *time, char *action);

#endif
