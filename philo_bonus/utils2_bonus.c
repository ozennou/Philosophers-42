/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:41:30 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/19 20:45:05 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_unlink(void)
{
	sem_unlink("frks");
	sem_unlink("p1");
	sem_unlink("dead");
	sem_unlink("minm");
}

t_philo	*init_philos(t_data *data)
{
	t_philo	*res;
	int		i;

	res = malloc(data->num_of_philos * sizeof(t_philo));
	if (!res)
		return (free(data), NULL);
	i = -1;
	while (++i < data->num_of_philos)
	{
		res[i].philo_num = i + 1;
		res[i].num_of_meals = 0;
		res[i].data = data;
		res[i].philo = 0;
	}
	ft_unlink();
	data->forks = sem_open("frks", O_CREAT | O_EXCL, 0644, data->num_of_philos);
	data->protect1 = sem_open("p1", O_CREAT | O_EXCL, 0644, 1);
	data->dead = sem_open("dead", O_CREAT | O_EXCL, 0644, 0);
	data->minm = sem_open("minm", O_CREAT | O_EXCL, 0644, 0);
	if (data->forks == SEM_FAILED || data->protect1 == SEM_FAILED
		|| data->dead == SEM_FAILED || data->minm == SEM_FAILED)
		return (free(res), free(data), NULL);
	return (res);
}
