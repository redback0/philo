/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:41:32 by njackson          #+#    #+#             */
/*   Updated: 2024/06/10 15:22:42 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_start(t_philo *philo)
{
	while (time_dif(philo->dat->start_time, NULL) < 0)
		usleep(50);
	if (philo->num % 2)
		usleep(philo->dat->eat_time * 500);
	while (1)
	{
		if (philo_death(philo, time_dif(philo->last_meal, NULL)))
			break ;
		else if (philo->state == 0)
			philo_eat(philo);
		else if (philo->state == 1)
		{
			print_action(philo, &philo->action_time, C_CYAN"is sleeping"C_NC);
			philo->state = 2;
		}
		else if (philo->state >= 2 && time_dif(philo->action_time, NULL)
			> philo->dat->sleep_time * 1000)
			philo_think(philo);
		usleep(philo->dat->break_time);
	}
}

static int	pickup_forks(t_philo *philo)
{
	if (philo->left_fork == philo->right_fork)
		return (1);
	pthread_mutex_lock(&philo->dat->eat_lock);
	pthread_mutex_lock(&(philo->dat->fork_mutex[philo->left_fork]));
	pthread_mutex_lock(&(philo->dat->fork_mutex[philo->right_fork]));
	if (philo->dat->fork[philo->left_fork]
		|| philo->dat->fork[philo->right_fork])
	{
		pthread_mutex_unlock(&(philo->dat->fork_mutex[philo->left_fork]));
		pthread_mutex_unlock(&(philo->dat->fork_mutex[philo->right_fork]));
		pthread_mutex_unlock(&philo->dat->eat_lock);
		return (1);
	}
	philo->dat->fork[philo->left_fork] = 1;
	print_action(philo, &philo->action_time, C_GRAY"has taken a fork"C_NC);
	philo->dat->fork[philo->right_fork] = 1;
	print_action(philo, &philo->action_time, C_GRAY"has taken a fork"C_NC);
	pthread_mutex_unlock(&(philo->dat->fork_mutex[philo->left_fork]));
	pthread_mutex_unlock(&(philo->dat->fork_mutex[philo->right_fork]));
	pthread_mutex_unlock(&philo->dat->eat_lock);
	return (0);
}

void	philo_eat(t_philo *philo)
{
	int	action_dif;

	if (pickup_forks(philo))
		return ;
	print_action(philo, &philo->last_meal, C_ORANGE"is eating"C_NC);
	philo->state = 1;
	while (1)
	{
		action_dif = time_dif(philo->last_meal, NULL);
		if (philo_death(philo, action_dif))
			break ;
		if (action_dif > philo->dat->eat_time * 1000)
			break ;
		usleep(philo->dat->break_time);
	}
	add_mutex_int(&philo->eaten, &philo->eaten_lock, 1);
	pthread_mutex_lock(&(philo->dat->fork_mutex[philo->left_fork]));
	pthread_mutex_lock(&(philo->dat->fork_mutex[philo->right_fork]));
	philo->dat->fork[philo->num - 1] = 0;
	philo->dat->fork[philo->num % philo->dat->num_philo] = 0;
	pthread_mutex_unlock(&(philo->dat->fork_mutex[philo->left_fork]));
	pthread_mutex_unlock(&(philo->dat->fork_mutex[philo->right_fork]));
}

int	philo_death(t_philo *philo, int last_meal)
{
	int	out;

	out = 0;
	pthread_mutex_lock(&philo->dat->death_lock);
	if (philo->dat->death)
		out = 1;
	else if (last_meal > philo->dat->die_time * 1000)
	{
		philo->dat->death = 1;
		print_action(philo, &philo->action_time, C_RED"died"C_NC);
		out = 1;
	}
	pthread_mutex_unlock(&philo->dat->death_lock);
	return (out);
}

void	philo_think(t_philo *philo)
{
	print_action(philo, &philo->action_time, C_GREEN"is thinking"C_NC);
	philo->state = 0;
	if (philo->dat->eat_time > philo->dat->sleep_time)
		usleep((philo->dat->eat_time - philo->dat->sleep_time) * 1000);
	usleep(100);
}
