/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:29:24 by njackson          #+#    #+#             */
/*   Updated: 2024/06/05 15:21:05 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_philo_dat	dat;
	int			i;

	if (ac < 5 || ac > 7)
		return (printf(USAGE), 0);
	set_philo_dat(ac, av, &dat);
	dat.threads = init_threads(&dat);
	i = 0;
	while (i < dat.num_philo)
		pthread_join(dat.threads[i++], NULL);
	delete_dat(&dat);
}

int	set_philo_dat(int ac, char **av, t_philo_dat *dat)
{
	int	err;
	int	i;

	err = 0;
	dat->num_philo = ft_atou_strict(av[1], &err);
	dat->die_time = ft_atou_strict(av[2], &err) * 1000;
	dat->eat_time = ft_atou_strict(av[3], &err) * 1000;
	dat->sleep_time = ft_atou_strict(av[4], &err) * 1000;
	dat->death = 0;
	if (ac == 6)
		dat->to_eat = ft_atou_strict(av[5], &err);
	else
		dat->to_eat = -1;
	if (err)
		return (err);
	dat->forks = (t_mutex *)malloc(dat->num_philo * sizeof(*(dat->forks)));
	i = 0;
	while (i < dat->num_philo)
		if (pthread_mutex_init(dat->forks + i++, NULL))
			return (printf("Mutex init failed\n"), 1);
	gettimeofday(&dat->start_time, NULL);
	dat->start_time.tv_sec += 1;
	return (err);
}

void	delete_dat(t_philo_dat *dat)
{
	int	i;

	i = 0;
	while (i < dat->num_philo)
		pthread_mutex_destroy(dat->forks + i++);
	free(dat->forks);
}

pthread_t	*init_threads(t_philo_dat *dat)
{
	t_philo		*philo;
	pthread_t	*threads;
	int			i;

	threads = (pthread_t *)malloc((dat->num_philo) * sizeof(*threads));
	i = 0;
	while (i < dat->num_philo)
	{
		philo = (t_philo *)malloc(sizeof(*philo));
		philo->dat = dat;
		philo->num = ++i;
		philo->eaten = 0;
		philo->state = 0;
		philo->last_meal = dat->start_time;
		pthread_create(&threads[i - 1], NULL,
			(void *)(void *)philo_start, philo);
	}
	return(threads);
}
