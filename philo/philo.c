/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:29:24 by njackson          #+#    #+#             */
/*   Updated: 2024/06/06 19:59:05 by njackson         ###   ########.fr       */
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
	i = 0;
	while (i < dat.num_philo)
		dat.fork[i++] = 0;
	dat.threads = init_threads(&dat);
	i = 0;
	if (dat.to_eat > 0)
	{
		while (!dat.death && i < dat.num_philo)
		{
			if (dat.philos[i].eaten >= dat.to_eat)
				i++;
			usleep(1000);
		}
		dat.death = 1;
	}
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
	dat->die_time = ft_atou_strict(av[2], &err);
	dat->eat_time = ft_atou_strict(av[3], &err);
	dat->sleep_time = ft_atou_strict(av[4], &err);
	dat->death = 0;
	if (ac == 6)
		dat->to_eat = ft_atou_strict(av[5], &err);
	else
		dat->to_eat = -1;
	if (err)
		return (err);
	dat->philos = (t_philo *)malloc(dat->num_philo * sizeof(*(dat->philos)));
	dat->fork_mutex = (t_mutex *)malloc(dat->num_philo
			* sizeof(*(dat->fork_mutex)));
	dat->fork = (char *)malloc(dat->num_philo * sizeof(char));
	i = 0;
	while (i < dat->num_philo)
		if (pthread_mutex_init(dat->fork_mutex + i++, NULL))
			return (printf("Mutex init failed\n"), 1);
	gettimeofday(&dat->start_time, NULL);
	return (dat->start_time.tv_sec += 1, err);
}

void	delete_dat(t_philo_dat *dat)
{
	int	i;

	i = 0;
	while (i < dat->num_philo)
		pthread_mutex_destroy(dat->fork_mutex + i++);
	free(dat->fork_mutex);
	free(dat->fork);
	free(dat->philos);
	free(dat->threads);
}

pthread_t	*init_threads(t_philo_dat *dat)
{
	pthread_t	*threads;
	int			i;

	threads = (pthread_t *)malloc((dat->num_philo) * sizeof(*threads));
	i = 0;
	while (i < dat->num_philo)
	{
		dat->philos[i].dat = dat;
		dat->philos[i].num = i + 1;
		dat->philos[i].eaten = 0;
		dat->philos[i].state = 0;
		dat->philos[i].left_fork = i;
		dat->philos[i].right_fork = (i + 1) % dat->num_philo;
		dat->philos[i].last_meal = dat->start_time;
		pthread_create(&threads[i], NULL,
			(void *)(void *)philo_start, dat->philos + i);
		i++;
	}
	return (threads);
}
