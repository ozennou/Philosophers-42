/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:29:15 by mozennou          #+#    #+#             */
/*   Updated: 2024/02/25 16:21:30 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *ph, char *msg)
{
	pthread_mutex_lock(&ph->data->protect1);
	printf("%lld %d %s", get_time() - ph->data->start_time, ph->philo_num, msg);
	pthread_mutex_unlock(&ph->data->protect1);
}

int	enough_meals(t_data *data, t_philo *philos)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	pthread_mutex_lock(&data->protect3);
	while (i < data->num_of_philos)
	{
		if (philos[i++].num_of_meals >= data->min_meals)
			count++;
	}
	pthread_mutex_unlock(&data->protect3);
	if (count == data->num_of_philos)
		return (1);
	return (0);
}

void	*shinigami(t_strct strct)
{
	t_philo	*philos;
	t_data	*data;
	int		i;

	data = strct.data;
	philos = strct.philos;
	i = 0;
	while (1)
	{
		if (data->min_meals != -1 && enough_meals(data, philos))
			return (pthread_mutex_lock(&data->protect1), NULL);
		pthread_mutex_lock(&data->protect2);
		if (get_time() - philos[i].last_meal > data->die_time)
		{
			pthread_mutex_unlock(&data->protect2);
			pthread_mutex_lock(&data->protect1);
			printf("%lld %d %s\n", get_time() - philos[i].data->start_time,
				philos[i].philo_num, "died");
			break ;
		}
		pthread_mutex_unlock(&data->protect2);
		if (++i == data->num_of_philos)
			i = 0;
	}
	return (NULL);
}

void	clean_up(t_strct strct)
{
	int	i;

	i = 0;
	while (i < strct.data->num_of_philos)
		pthread_mutex_destroy(&strct.philos[i++].r_fork);
	pthread_mutex_destroy(&strct.data->protect2);
	pthread_mutex_destroy(&strct.data->protect3);
	pthread_mutex_destroy(&strct.data->protect1);
}

int	main(int ac, char **av)
{
	t_strct	strct;

	if (ac != 5 && ac != 6)
		return (ft_error(), 1);
	strct.data = init_data(ac, av);
	if (!strct.data)
		return (1);
	if (!strct.data->min_meals)
		return (0);
	strct.philos = init_philos(strct.data);
	if (!strct.philos)
		return (1);
	strct.data->start_time = get_time();
	init_routines(strct);
	shinigami(strct);
	clean_up(strct);
	free(strct.philos);
	free(strct.data);
	return (0);
}
