/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:37:39 by codespace         #+#    #+#             */
/*   Updated: 2024/09/11 20:30:17 by dlamark-         ###   ########.fr       */
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

typedef struct s_dining_setup t_dining_setup;
typedef struct s_mutexes t_mutexes;
typedef struct s_monitor t_monitor;

enum	actions {
	EATING,
	SLEEPING,
	THINKING,
	TAKING_FORK

};

enum	mutex {
	LOCK,
	UNLOCK,
	INIT,
	DESTROY
};

typedef struct s_monitor
{
	int				philo_is_dead;
	pthread_mutex_t	monitor_dead;
	pthread_mutex_t	notice_dead;
	pthread_mutex_t	flag;
	
}	t_monitor;

typedef struct s_philo
{
	pthread_t			philo;
	int					index;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_dining_setup		*dinner_info;
	t_mutexes			*mutexes;
	long int			last_meal;
	int					number_of_meals;
	t_monitor			*monitor;
	
}	t_philo;

typedef struct s_dining_setup
{
	long int				philosophers;
	long int				n_forks;
	long int				time_to_die;
	long int				time_to_eat;
	long int				time_to_sleep;
	int						number_of_meals;
	long int				start_dinner;
	long int				end_dinner;
}	t_dining_setup;

typedef struct s_mutexes
{
	pthread_mutex_t		print[1];
}	t_mutexes;

//init_data.c
int 				initialize_dinner_data(t_dining_setup *dinner_data, t_philo *philo, pthread_mutex_t *forks, t_mutexes *mutexes, t_monitor *monitor);
int					initialize_data(t_dining_setup *dinner_data, t_philo *philos, pthread_mutex_t	*forks);
void				configure_dining_parameters(t_dining_setup *dinner_data,
						char **argv, int argc);
pthread_mutex_t		*initialize_forks(pthread_mutex_t *forks, t_dining_setup	*dinner_data);
void				assign_forks(t_philo *philo, int i, int n_philo, pthread_mutex_t *forks);
pthread_mutex_t		*create_prints_mutex(pthread_mutex_t *prints);
void				assign_prints(pthread_mutex_t *prints, t_philo *philo, t_dining_setup *dinner_data);
int					initialize_mutexes(t_mutexes *mutexes);
t_philo 			*initialize_philo_data(t_dining_setup	*dinner_data, t_philo *philo,
						pthread_mutex_t *forks, t_mutexes *mutexes, t_monitor *monitor);

//free_and_error.c
void				set_allocation_error(void);
void ft_itoa(long int n, char *str, size_t buffer_size);
//print.c
void				print_dinner_data(t_dining_setup *dinner_data);
void				print_philo_data(t_philo *philo, t_dining_setup	*dinner_data);
void				safe_print(t_philo *philo, int action);
void				safe_print_eat(t_philo *philo, int action);
void				print_actions(long int time, int philo_index, char *action);
//create_threads.c
int					initialize_threads(t_philo *philo, t_dining_setup	*dinner_data);
long int			get_time(void);
int					philo_is_dead(t_philo *philo);

//mutex.c
int					safe_mutex_lock(pthread_mutex_t *mutex);
int					safe_mutex_unlock(pthread_mutex_t *mutex);
int					safe_mutex_init(pthread_mutex_t *mutex);
int					safe_mutex_destroy(pthread_mutex_t *mutex);

//philo.c
void				process_even_philosopher_eating(t_philo *philo);
void				process_odd_philosopher_eating(t_philo *philo);
void				process_philo_sleeping(t_philo *philo);
void				process_philo_thinking(t_philo	*philo);
int					check_philo_state(t_philo *philo);

//utils.c
int					is_digit(char c);
int					ft_strlen(char *str);
void				ft_putstr_fd(const char *str, int fd);
long int			ft_atol(const char *str);

//validate_args.c
int					validate_args(int argc, char **argv);
int					is_numeric_arg(const char *str);
int					is_maxmin_int(char *str);
int					is_negative_nbr(char *argv);
int					max_n_philo(char *philos);

#endif
