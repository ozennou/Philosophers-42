/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:23:02 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/18 18:13:53 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_data
{
	sem_t		*protect1;
	sem_t		*dead;
	sem_t		*forks;
	sem_t		*minm;
	int			num_of_philos;
	int			die_time;
	int			eat_time;
	int			sleep_time;
	int			min_meals;
	long long	start_time;
}	t_data;

typedef struct s_philo
{
	pid_t		philo;
	pthread_t	check;
	sem_t		*protect2;
	t_data		*data;
	long long	last_meal;
	int			philo_num;
	int			num_of_meals;
}	t_philo;

typedef struct s_strct
{
	t_data	*data;
	t_philo	*philos;
}	t_strct;

int			ft_atoi(char *s, int *num);
char		*ft_itoa(int n);
void		ft_putstr_fd(char *s, int fd);
long long	get_time(void);
void		ft_error(void);
void		ft_usleep(int time);
t_data		*init_data(int ac, char **av);
t_philo		*init_philos(t_data *data);
int			routine(t_philo *philo);
int			init_routines(t_strct *strct);
void		print(t_philo *ph, char *msg);
void		*shinigami(void	*param);

#endif