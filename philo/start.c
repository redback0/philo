/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:41:32 by njackson          #+#    #+#             */
/*   Updated: 2024/06/06 16:43:03 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_start(t_philo *philo)
{
	while (time_dif(philo->dat->start_time, NULL) < 0)
		usleep(10);
	if (philo->num % 2)
		usleep(100);
	while (!philo->dat->death)
	{
		if (time_dif(philo->last_meal, NULL) > philo->dat->die_time * 1000)
		{
			philo->dat->death = 1;
			print_action(philo, &philo->action_time, "died");
		}
		else if (philo->state == 0)
			philo_eat(philo);
		else if (philo->state == 1)
			philo_sleep(philo);
		else if (philo->state >= 2 && time_dif(philo->action_time, NULL)
			> philo->dat->sleep_time * 1000)
			philo_think(philo);
		usleep(10);
	}
}

static int	pickup_forks(t_philo *philo)
{
	if (philo->left_fork == philo->right_fork)
		return (1);
	pthread_mutex_lock(&(philo->dat->fork_mutex[philo->left_fork]));
	pthread_mutex_lock(&(philo->dat->fork_mutex[philo->right_fork]));
	if (philo->dat->fork[philo->left_fork]
		|| philo->dat->fork[philo->right_fork])
	{
		pthread_mutex_unlock(&(philo->dat->fork_mutex[philo->left_fork]));
		pthread_mutex_unlock(&(philo->dat->fork_mutex[philo->right_fork]));
		return (1);
	}
	philo->dat->fork[philo->left_fork] = 1;
	print_action(philo, &philo->action_time, "has taken a fork");
	philo->dat->fork[philo->right_fork] = 1;
	print_action(philo, &philo->action_time, "has taken a fork");
	pthread_mutex_unlock(&(philo->dat->fork_mutex[philo->left_fork]));
	pthread_mutex_unlock(&(philo->dat->fork_mutex[philo->right_fork]));
	return (0);
}

void	philo_eat(t_philo *philo)
{
	int	action_dif;

	if (pickup_forks(philo))
		return ;
	print_action(philo, &philo->last_meal, "is eating");
	philo->state = 1;
	while (!philo->dat->death)
	{
		action_dif = time_dif(philo->last_meal, NULL);
		if (action_dif > philo->dat->die_time * 1000)
		{
			philo->dat->death = 1;
			print_action(philo, &philo->action_time, "died");
		}
		if (action_dif > philo->dat->eat_time * 1000)
			break ;
		usleep(10);
	}
	philo->eaten++;
	pthread_mutex_lock(&(philo->dat->fork_mutex[philo->left_fork]));
	pthread_mutex_lock(&(philo->dat->fork_mutex[philo->right_fork]));
	philo->dat->fork[philo->num - 1] = 0;
	philo->dat->fork[philo->num % philo->dat->num_philo] = 0;
	pthread_mutex_unlock(&(philo->dat->fork_mutex[philo->left_fork]));
	pthread_mutex_unlock(&(philo->dat->fork_mutex[philo->right_fork]));
}

void	philo_sleep(t_philo *philo)
{
	print_action(philo, &philo->action_time, "is sleeping");
	philo->state = 2;
}

void	philo_think(t_philo *philo)
{
	print_action(philo, &philo->action_time, "is thinking");
	philo->state = 0;
	usleep(100);
}
