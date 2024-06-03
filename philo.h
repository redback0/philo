/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:11:15 by njackson          #+#    #+#             */
/*   Updated: 2024/05/31 19:18:57 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <pthread.h>

typedef struct s_philo
{
	int		num_philo;
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		each_eat;
}	t_philo;

int	set_philo_dat(int ac, char **av, t_philo *dat);
void	init_threads(t_philo *dat);


void	thread_func(t_philo *dat);

// libft functions
int		ft_atoi_strict(const char *str, int *err);

#endif
