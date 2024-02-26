/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 06:33:51 by mozennou          #+#    #+#             */
/*   Updated: 2024/02/26 08:54:21 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init_data(int ac, char **av)
{
	t_data	*res;

	res = malloc(sizeof(t_data));
	if (!res)
		return (NULL);
	if (ft_atoi(av[1], &res->num_of_philos) || !res->num_of_philos)
		return (ft_error(), free(res), NULL);
	if (ft_atoi(av[2], &res->die_time) || !res->die_time)
		return (ft_error(), free(res), NULL);
	if (ft_atoi(av[3], &res->eat_time) || !res->eat_time)
		return (ft_error(), free(res), NULL);
	if (ft_atoi(av[4], &res->sleep_time) || !res->sleep_time)
		return (ft_error(), free(res), NULL);
	if (ac == 6)
	{
		if (ft_atoi(av[5], &res->min_meals))
			return (ft_error(), free(res), NULL);
	}
	else
		res->min_meals = -1;
	return (res);
}

t_philo	*init_philos(t_data *data)
{
	t_philo	*res;
	int		i;

	res = malloc(data->num_of_philos * sizeof(t_philo));
	if (!res)
		return (free(data), NULL);
	i = 0;
	while (i < data->num_of_philos)
	{
		res[i].philo_num = i + 1;
		res[i].num_of_meals = 0;
		if (pthread_mutex_init(&res[i].r_fork, NULL))
			return (free(data), NULL);
		if (i != 0)
			res[i].l_fork = &res[i - 1].r_fork;
		res[i].data = data;
		i++;
	}
	if (data->num_of_philos != 1)
		res[0].l_fork = &res[i - 1].r_fork;
	if (pthread_mutex_init(&data->protect1, NULL)
		|| pthread_mutex_init(&data->protect2, NULL)
		|| pthread_mutex_init(&data->protect3, NULL))
		return (free(data), NULL);
	return (res);
}

int	init_routines(t_strct strct)
{
	int		i;
	t_philo	*p;

	i = 0;
	p = strct.philos;
	while (i < strct.data->num_of_philos)
	{
		p[i].last_meal = get_time();
		pthread_create(&p[i].philo, NULL, &routine, &p[i]);
		i++;
	}
	while (--i != -1)
		pthread_detach(p[i].philo);
	return (0);
}

static void	func(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->protect2);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->protect2);
	pthread_mutex_lock(&philo->data->protect3);
	philo->num_of_meals++;
	pthread_mutex_unlock(&philo->data->protect3);
}

void	*routine(void	*param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->philo_num % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->r_fork);
		print(philo, "has taken a fork\n");
		if (philo->data->num_of_philos == 1)
			pthread_mutex_lock(&philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
		print(philo, "has taken a fork\n");
		print(philo, "is eating\n");
		func(philo);
		ft_usleep(philo->data->eat_time);
		pthread_mutex_unlock(&philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		print(philo, "is sleeping\n");
		ft_usleep(philo->data->sleep_time);
		print(philo, "is thinking\n");
	}
	return (NULL);
}
