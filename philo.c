/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:29:24 by njackson          #+#    #+#             */
/*   Updated: 2024/06/03 17:08:06 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_philo_dat	dat;

	if (ac < 5 || ac > 7)
		return (printf(USAGE), 0);
	set_philo_dat(ac, av, &dat);
	init_threads(&dat);
}

int	set_philo_dat(int ac, char **av, t_philo_dat *dat)
{
	int err;

	err = 0;
	dat->num_philo = ft_atoi_strict(av[1], &err);
	dat->die_time = ft_atoi_strict(av[2], &err);
	dat->eat_time = ft_atoi_strict(av[3], &err);
	dat->sleep_time = ft_atoi_strict(av[4], &err);
	if (ac == 6)
		dat->each_eat = ft_atoi_strict(av[5], &err);
	else
		dat->each_eat = -1;
	return (err);
}

void	init_threads(t_philo_dat *dat)
{
	t_philo		*philo;
	pthread_t	thread;
	int			i;

	i = 0;
	while (i < dat->num_philo)
	{
		philo = (t_philo *)malloc(sizeof(*philo));
		philo->dat = dat;
		philo->num = i;
		philo->eaten = 0;
		pthread_create(&thread, NULL, (void *)(void *)thread_func, philo);
		pthread_detach(thread);
		i++;
	}
	usleep(1000);
}

void	thread_func(t_philo *philo)
{
	printf("PHILO %d: Hello world!\n", philo->num);
	free(philo);
}
