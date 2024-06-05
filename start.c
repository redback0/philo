/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:41:32 by njackson          #+#    #+#             */
/*   Updated: 2024/06/05 20:55:51 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_start(t_philo *philo)
{
	int	action_dif;

	while (time_dif(philo->dat->start_time, NULL) < 0)
		usleep(100);
	if (philo->num % 2)
		usleep(500);
	while (!philo->dat->death)
	{
		action_dif = time_dif(philo->action_time, NULL);
		if (time_dif(philo->last_meal, NULL) > philo->dat->die_time)
		{
			philo->dat->death = 1;
			print_action(philo, &philo->action_time, "died");
		}
		else if (philo->state == 0)
			philo_eat(philo);
		else if (philo->state == 1)
			philo_sleep(philo);
		else if (philo->state == 2 && time_dif(philo->action_time, NULL)
			> philo->dat->sleep_time)
			philo_think(philo);
		usleep(10);
	}
}

static int	pickup_fork(t_philo_dat *dat, int fork_num)
{
	pthread_mutex_lock(&(dat->forks[fork_num]));
	if (dat->death)
	{
		pthread_mutex_unlock(&(dat->forks[fork_num]));
		return (1);
	}
	return (0);
}

void	philo_eat(t_philo *philo)
{
	int	action_dif;

	if (pickup_fork(philo->dat, philo->num - 1))
		return ;
	print_action(philo, &philo->action_time, "has taken a fork");
	if (pickup_fork(philo->dat, philo->num % philo->dat->num_philo))
		return ;
	print_action(philo, &philo->action_time, "has taken a fork");
	print_action(philo, &philo->last_meal, "is eating");
	philo->state = 1;
	while (!philo->dat->death)
	{
		action_dif = time_dif(philo->last_meal, NULL);
		if (action_dif > philo->dat->die_time)
		{
			philo->dat->death = 1;
			print_action(philo, &philo->action_time, "died");
		}
		if (action_dif > philo->dat->eat_time)
			break ;
		usleep(10);
	}
	philo->eaten++;
	pthread_mutex_unlock(&(philo->dat->forks[philo->num - 1]));
	pthread_mutex_unlock(
		&(philo->dat->forks[philo->num % philo->dat->num_philo]));
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
}
