/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 06:33:51 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/20 17:07:49 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*meal_check(void *param)
{
	int		i;
	t_data	*data;

	data = (t_data *)param;
	i = 0;
	while (i < data->num_of_philos)
	{
		sem_wait(data->minm);
		i++;
	}
	sem_wait(data->protect1);
	sem_post(data->dead);
	return (NULL);
}

int	check_wait(t_data *data)
{
	int			i;
	pid_t		pid;
	pthread_t	tid;

	pid = fork();
	i = 0;
	if (pid == -1)
		return (-1);
	if (pid)
	{
		waitpid(-1, NULL, 0);
		sem_post(data->dead);
	}
	else
	{
		if (data->min_meals != -1)
		{
			pthread_create(&tid, NULL, meal_check, data);
			pthread_detach(tid);
		}
		sem_wait(data->dead);
	}
	if (!pid)
		exit(0);
	return (0);
}

int	init_routines(t_strct *strct)
{
	int		i;
	t_philo	*p;

	i = 0;
	p = strct->philos;
	strct->data->start_time = get_time();
	while (i < strct->data->num_of_philos)
	{
		p[i].last_meal = get_time();
		p[i].philo = fork();
		if (p[i].philo == -1)
			return (write(2, "Fork failed\n", 13), -1);
		if (!p[i].philo)
		{
			if (routine(&p[i]))
				return (-1);
		}
		i++;
	}
	if (check_wait(strct->data))
		return (-1);
	return (0);
}

static void	func(t_philo *philo)
{
	sem_wait(philo->protect2);
	philo->last_meal = get_time();
	philo->num_of_meals++;
	if (philo->num_of_meals == philo->data->min_meals)
		sem_post(philo->data->minm);
	sem_post(philo->protect2);
	ft_usleep(philo->data->eat_time);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

int	routine(t_philo *philo)
{
	char	*s1;

	s1 = ft_itoa(philo->philo_num + 10);
	if (!s1)
		return (-1);
	sem_unlink(s1);
	philo->protect2 = sem_open(s1, O_CREAT | O_EXCL, 0644, 1);
	free(s1);
	pthread_create(&philo->check, NULL, shinigami, philo);
	pthread_detach(philo->check);
	while (1)
	{
		sem_wait(philo->data->forks);
		print(philo, "has taken a fork\n");
		if (philo->data->num_of_philos == 1)
			sem_wait(philo->data->forks);
		sem_wait(philo->data->forks);
		print(philo, "has taken a fork\n");
		print(philo, "is eating\n");
		func(philo);
		print(philo, "is sleeping\n");
		ft_usleep(philo->data->sleep_time);
		print(philo, "is thinking\n");
	}
	return (0);
}
