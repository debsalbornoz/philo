/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:37:39 by codespace         #+#    #+#             */
/*   Updated: 2024/09/17 11:41:53 by codespace        ###   ########.fr       */
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

typedef struct	s_dining_setup t_dining_setup;
typedef struct	s_mutexes t_mutexes;
typedef struct	s_monitor t_monitor;
typedef struct	s_philo	t_philo;

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
} t_data;

typedef struct s_monitor
{
	pthread_t		monitor;
	t_philo			*philos;
	int				death_status;
	pthread_mutex_t	check_death;
	pthread_mutex_t	death_notification;

}	t_monitor;

typedef struct s_philo
{
	pthread_t			philo;
	int					index;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_dining_setup		*dinner_info;
	long int			last_meal;
	int					number_of_meals;
	t_monitor			*monitor;
	int					meals;
	pthread_mutex_t		check_first_meal;
}	t_philo;

typedef struct s_dining_setup
{
	int						philosophers;
	int						n_forks;
	int						number_of_meals;
	long int				time_to_die;
	long int				time_to_eat;
	long int				time_to_sleep;
	long int				start_dinner;
	long int				end_dinner;
	pthread_mutex_t			print_status[1];
	pthread_mutex_t			nbr_of_meals[1];
}	t_dining_setup;


//init_data.c

t_monitor		*init_monitor_data(t_monitor *monitor, t_philo *philo);
long int		get_time_ms(void);
long int		get_time(t_dining_setup *dinner_data);
t_philo			*initialize_philo_data(t_dining_setup	*dinner_data, t_philo *philo,
					pthread_mutex_t *forks, t_monitor *monitor);
int				initialize_dinner_data(t_dining_setup *dinner_data, t_philo *philo,
					pthread_mutex_t *forks, t_monitor *monitor);
void			configure_dining_parameters(t_dining_setup *dinner_data,
					char **argv, int argc);
t_data			*initialize_data(t_data *data, t_dining_setup *dinner_data, t_philo *philo, t_monitor *monitor);
//create_threads.c

int				philo_is_dead(t_philo *philo);
int				initialize_threads(t_data *data, t_philo *philo, t_dining_setup	*dinner_data, t_monitor *monitor);
void			*philo_routine(void *arg);
int 			process_philo_dining(t_philo *philo);
//mutex.c
int					safe_mutex_lock(pthread_mutex_t *mutex);
int					safe_mutex_unlock(pthread_mutex_t *mutex);
int					safe_mutex_init(pthread_mutex_t *mutex);
int					safe_mutex_destroy(pthread_mutex_t *mutex);

//philo.c
int				process_even_philosopher_eating(t_philo *philo);
int				process_odd_philosopher_eating(t_philo *philo);
void				process_philo_sleeping(t_philo *philo);
void				process_philo_thinking(t_philo	*philo);
int					check_philo_state(t_philo *philo);
int				process_philo_eating(t_philo *philo);
//utils.c
int					is_digit(char c);
int					ft_strlen(char *str);
void				ft_putstr_fd(const char *str, int fd);
long int			ft_atol(const char *str);
void				ft_itoa(long int n, char *str, size_t buffer_size, int is_negative);

//validate_args.c
int					validate_args(int argc, char **argv);
int					is_numeric_arg(const char *str);
int					is_maxmin_int(char *str);
int					is_negative_nbr(char *argv);
int					max_n_philo(char *philos);

//forks.c
void	assign_forks(t_philo *philo, int i, int n_philo, pthread_mutex_t *forks);
pthread_mutex_t	*initialize_forks(pthread_mutex_t *forks,
	t_dining_setup	*dinner_data);

//handle_mutexes.c
int	initialize_mutexes(t_mutexes *mutexes);

void	print_actions(long int time, int philo_index, char *action);
int			check_meals(t_philo *philo);
#endif
