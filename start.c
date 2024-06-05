/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:41:32 by njackson          #+#    #+#             */
/*   Updated: 2024/06/05 19:12:19 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_start(t_philo *philo)
{
	int	action_dif;

	while (time_dif(philo->dat->start_time) < 0)
		usleep(100);
	if (philo->num % 2)
		usleep(1000);
	while (!philo->dat->death)
	{
		action_dif = time_dif(philo->action_time);
		if (time_dif(philo->last_meal) >= philo->dat->die_time)
		{
			print_action(philo, "died");
			philo->dat->death = 1;
		}
		else if (philo->state == 0)
			philo_eat(philo);
		else if (philo->state == 1)
			philo_sleep(philo);
		else if (philo->state == 2
			&& action_dif >= philo->dat->sleep_time)
			philo_think(philo);
		usleep(10);
	}
}

void	philo_eat(t_philo *philo)
{
	int	action_dif;

	pthread_mutex_lock(&(philo->dat->forks[philo->num - 1]));
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(
		&(philo->dat->forks[philo->num % philo->dat->num_philo]));
	print_action(philo, "has taken a fork");
	print_action(philo, "is eating");
	gettimeofday(&philo->last_meal, NULL);
	philo->state = 1;
	while (!philo->dat->death)
	{
		action_dif = time_dif(philo->last_meal);
		if (action_dif >= philo->dat->die_time
			||action_dif >= philo->dat->eat_time)
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
	print_action(philo, "is sleeping");
	gettimeofday(&philo->action_time, NULL);
	philo->state = 2;
}

void	philo_think(t_philo *philo)
{
	print_action(philo, "is thinking");
	philo->state = 0;
}
