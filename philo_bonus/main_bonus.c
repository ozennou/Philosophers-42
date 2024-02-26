/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:29:15 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/22 18:50:07 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print(t_philo *ph, char *msg)
{
	sem_wait(ph->data->protect1);
	printf("%lld %d %s", get_time() - ph->data->start_time, ph->philo_num, msg);
	sem_post(ph->data->protect1);
}

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

void	*shinigami(void	*param)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)param;
	data = philo->data;
	while (1)
	{
		usleep(1000);
		if (get_time() - philo->last_meal > data->die_time)
		{
			sem_wait(data->protect1);
			printf("%lld %d %s", get_time() - philo->data->start_time,
				philo->philo_num, "died\n");
			break ;
		}
	}
	sem_post(data->dead);
	return (NULL);
}

void	clean_up(t_strct strct)
{
	int	i;

	i = 0;
	while (i < strct.data->num_of_philos)
	{
		kill(strct.philos[i].philo, SIGKILL);
		i++;
	}
	sem_close(strct.data->dead);
	sem_close(strct.data->forks);
	sem_close(strct.data->minm);
	sem_close(strct.data->protect1);
	free(strct.philos);
	free(strct.data);
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
	if (init_routines(&strct))
	{
		clean_up(strct);
		return (1);
	}
	clean_up(strct);
	return (0);
}
