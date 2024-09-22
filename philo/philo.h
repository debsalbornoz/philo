/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:37:39 by codespace         #+#    #+#             */
/*   Updated: 2024/09/22 00:09:40 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MAX_INTEGER 2147483647
# define MIN_INTEGER -2147483648
# define TRUE 1
# define FALSE 0

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_dining_setup	t_dining_setup;
typedef struct s_mutexes		t_mutexes;
typedef struct s_monitor		t_monitor;
typedef struct s_philo			t_philo;

enum	e_actions
{
	EATING,
	SLEEPING,
	THINKING,
	TAKING_FORK
};

enum	e_mutex {
	LOCK,
	UNLOCK,
	INIT,
	DESTROY
};

typedef struct s_data
{
	t_monitor		*monitor;
	t_philo			*philo;
	t_dining_setup	*dinner_data;
}	t_data;

typedef struct s_monitor
{
	pthread_t				monitor;
	t_philo					*philos;
	int						death_status;
	pthread_mutex_t			monitor_philo;
	pthread_mutex_t			print_status;
}	t_monitor;

typedef struct s_philo
{
	pthread_t			philo;
	_Atomic int			index;
	_Atomic long int	last_meal;
	_Atomic int			number_of_meals;
	_Atomic int			is_satisfied;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_dining_setup		*dinner_info;
	t_monitor			*monitor;
	pthread_mutex_t		check_first_meal;
}	t_philo;

typedef struct s_dining_setup
{
	_Atomic int						philosophers;
	_Atomic int						n_forks;
	_Atomic int						number_of_meals;
	_Atomic long int				time_to_die;
	_Atomic long int				time_to_eat;
	_Atomic long int				time_to_sleep;
	_Atomic long int				start_dinner;
	_Atomic long int				end_dinner;
}	t_dining_setup;

//actions.c
void			process_philo_thinking(t_philo	*philo);
int				process_philo_eating(t_philo *philo);
int				handle_eat(t_philo *philo);
void			process_philo_sleeping(t_philo *philo);

//create_threads.c
int				initialize_threads(t_data *data, t_philo *philo,
					t_dining_setup *dinner_data, t_monitor *monitor);

//forks.c
pthread_mutex_t	*initialize_forks(pthread_mutex_t *forks,
					t_dining_setup	*dinner_data);
void			assign_forks(t_philo *philo, int i,
					int n_philo, pthread_mutex_t *forks);

//init_data.c
void			configure_dining_parameters(t_dining_setup *dinner_data,
					char **argv, int argc);
t_philo			*initialize_philo_data(t_dining_setup	*dinner_data,
					t_philo *philo, pthread_mutex_t *forks, t_monitor *monitor);
t_monitor		*init_monitor_data(t_monitor *monitor, t_philo *philo);
t_data			*initialize_data(t_data *data, t_dining_setup *dinner_data,
					t_philo *philo, t_monitor *monitor);

//monitor_routine.c
int				philo_is_dead(t_philo *philo);
void			*monitor_routine(void *arg);
int				all_philos_safisfied(t_data *data);

//mutex.c
int				safe_mutex_init(pthread_mutex_t *mutex);
int				safe_mutex_lock(pthread_mutex_t *mutex);
int				safe_mutex_unlock(pthread_mutex_t *mutex);
int				safe_mutex_destroy(pthread_mutex_t *mutex);

//philo_routine.c
void			*philo_routine(void *arg);
int				is_satisfied(t_philo *philo);
//print_actions.c
void			print_actions(long int time, char *action, t_philo *philo);
int				get_digits(long int nbr);
char			*ft_itoa(long int n);
int				ft_strlcat(char *dst, char *src, int size);
void			ft_putstr_fd(char *s, int fd);

//time.c
unsigned int	get_time_ms(void);
unsigned int	get_time(t_dining_setup *dinner_data);

//utils.c
int				is_digit(char c);
int				ft_strlen(char *str);
long int		ft_atol(const char *str);

//validate_args.c

int				validate_args(int argc, char **argv);
int				max_n_philo(char *philos);
int				is_numeric_arg(const char *str);
int				is_maxmin_int(char *str);
int				is_negative_nbr(char *str);
#endif
