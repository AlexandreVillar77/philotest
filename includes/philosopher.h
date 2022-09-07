/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:40:48 by avillar           #+#    #+#             */
/*   Updated: 2022/09/07 13:26:50 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <term.h>
typedef struct s_philo t_philo;
typedef struct s_data t_data;

//status 0 == is thinking / nothing
//status 1 == is eating
//status 2 == is sleeping
//status 3 == has one fork
//status 4 == is dead
//status 5 == launch


struct s_philo
{
	int					id;
	int					status;
	int					doing;
	long long			lm;
	int					nte;
	int					et;
	pthread_t			thread;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		l_fork;
	t_philo				*next_philo;
	t_data				*data;
};

struct s_data
{
	t_philo				*first_philo;
	pthread_mutex_t		lock;
	int					n_philo;
	int					tteat;
	int					ttdie;
	int					ttsleep;
	struct timeval		tatstart;
	int					died;
	int					stop;
	int					nte;
	int					order;
};

//parsing.c
int						parsing_glo(int argc, char **argv);

//init_struct.c
t_data					*init_structd(int argc , char **argv);
t_philo					*create_all_philo(int n, t_data *data);
void					makefork(t_philo *tmp);;

//routine.c
void					*routine(void *philo);

//free_struct.c
void					free_data(t_data *data);

//printing.c
void					is_thinking(t_philo *tmp);
void					go_sleep(t_philo *tmp);
int						go_eat(t_philo *tmp);
void					print(t_philo *tmp, char *str);
void					print_fork(t_philo *tmp);

//////////////// utils

//ft_atoi.c
char					*ft_itoa(int n);
int						ft_atoi(const char *str);

//calcul.c
int						check_for_die(int i, t_philo *philo);
int						check_for_die2(int i, t_philo *tmp);
int						ft_sleep(int i);
int						ft_strlen(char *str);
unsigned long long int	calcul_time(struct timeval atstart);
int						cee(t_philo *tmp);
int						die_wthink(int i, t_philo *tmp);
int						die_wthink2(int i, t_philo *tmp);

//ft_putchar.c
void					ft_putnbr_fd(int n, int fd);

#endif