/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:41:32 by njackson          #+#    #+#             */
/*   Updated: 2024/06/06 15:14:38 by njackson         ###   ########.fr       */
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
		else if (philo->state == 2 && time_dif(philo->action_time, NULL)
			> philo->dat->sleep_time * 1000)
			philo_think(philo);
		usleep(10);
	}
}

static int	pickup_fork(t_philo *philo, int fork_num)
{
	static t_mutex	grab_fork;

	if (philo->dat->num_philo == 1)
		return (1);
	pthread_mutex_lock(&grab_fork);
	if (philo->dat->fork_state[fork_num])
	{
		pthread_mutex_unlock(&grab_fork);
		return (1);
	}
	pthread_mutex_lock(&(philo->dat->forks[fork_num]));
	if (time_dif(philo->last_meal, NULL) > philo->dat->die_time * 1000)
	{
		philo->dat->death = 1;
		print_action(philo, &philo->action_time, "died");
	}
	if (philo->dat->death)
	{
		pthread_mutex_unlock(&(philo->dat->forks[fork_num]));
		pthread_mutex_unlock(&grab_fork);
		return (1);
	}
	philo->dat->fork_state[fork_num] = 1;
	print_action(philo, &philo->action_time, "has taken a fork");
	pthread_mutex_unlock(&grab_fork);
	return (0);
}

void	philo_eat(t_philo *philo)
{
	int	action_dif;

	if (philo->dat->fork_state[philo->num %philo->dat->num_philo]
		|| pickup_fork(philo, philo->num - 1))
		return ;
	if (pickup_fork(philo, philo->num % philo->dat->num_philo))
	{
		philo->dat->fork_state[philo->num - 1] = 0;
		pthread_mutex_unlock(&(philo->dat->forks[philo->num - 1]));
		return ;
	}
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
	philo->dat->fork_state[philo->num - 1] = 0;
	pthread_mutex_unlock(&(philo->dat->forks[philo->num - 1]));
	philo->dat->fork_state[philo->num % philo->dat->num_philo] = 0;
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
