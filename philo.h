/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:11:15 by njackson          #+#    #+#             */
/*   Updated: 2024/06/03 16:16:06 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <pthread.h>

# define USAGE "./philo NUM_PHILOS TIME_TO_DIE TIME_TO_EAT TIME_TO_SLEEP \
[TIMES_TO_EAT]\n"

typedef pthread_mutex_t	t_mutex;

typedef struct s_philo_dat
{
	int		num_philo;
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		each_eat;
	t_mutex	*forks;
}	t_philo_dat;

typedef struct s_philo
{
	int			num;
	t_philo_dat	*dat;
	int			eaten;
}	t_philo;

int		set_philo_dat(int ac, char **av, t_philo_dat *dat);
void	init_threads(t_philo_dat *dat);

void	thread_func(t_philo *dat);

// libft functions
int		ft_atoi_strict(const char *str, int *err);

#endif
