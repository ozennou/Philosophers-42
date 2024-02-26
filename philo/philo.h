/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:23:02 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/18 18:11:35 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_data
{
	pthread_mutex_t	protect1;
	pthread_mutex_t	protect2;
	pthread_mutex_t	protect3;
	int				num_of_philos;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				min_meals;
	long long		start_time;
}	t_data;

typedef struct s_philo
{
	pthread_t		philo;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	*l_fork;
	t_data			*data;
	long long		last_meal;
	int				philo_num;
	int				num_of_meals;
}	t_philo;

typedef struct s_strct
{
	t_data	*data;
	t_philo	*philos;
}	t_strct;

int			ft_atoi(char *s, int *num);
void		ft_putstr_fd(char *s, int fd);
long long	get_time(void);
void		ft_error(void);
void		ft_usleep(int time);
t_data		*init_data(int ac, char **av);
t_philo		*init_philos(t_data *data);
void		*routine(void	*param);
int			init_routines(t_strct strct);
void		print(t_philo *ph, char *msg);

#endif