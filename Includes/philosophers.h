/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 14:18:19 by acaillea          #+#    #+#             */
/*   Updated: 2022/02/17 14:21:54 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/****************************************************/
/*		INCLUDES 									*/
/****************************************************/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

/****************************************************/
/*		DEFINES										*/
/****************************************************/

# define FORK "\033[1;96mhas taken a fork\n\033[0;39m"
# define EAT "\033[1;32mis eating\n\033[0;39m"
# define SLEP "\x1b[33mis sleeping\n\033[0;39m"
# define THNK "\x1b[35mis thinking\n\033[0;39m"
# define DEAD "\x1b[34mdied 😭\n\033[0;39m"

/*--	Errors--------------------------*/

# define NB_ER "\033[0;31mError : too many/not enough arugments.\n\
Expected : ./philo <nb_of_philo> <time_to_die> <time_to_eat>\
 <time_to_sleep> (Optional)<nb_times_each_philo_must_eat>\n\033[0;39m"
# define DI_ER "\033[0;31mError : negative or non-numerical \
argument.\n\033[0;39m"
# define MA_ER "\033[0;31mError : data memory allocation failed.\n\033[0;39m"
# define AR_ER "\033[0;31mError : argument(s) value(s) invalid.\n\033[0;39m"
# define MU_ER "\033[0;31mError : mutex allocation or creation \
failed.\n\033[0;39m"
# define TH_ER "\033[0;31mError : thread creation failed.\n\033[0;39m"
# define MD_ER "\033[0;31mError : mutex destroy failed.\n\033[0;39m "
# define END "\033[0;31mError : pthread join failed.\n\033[0;39m"

/****************************************************/
/*		STRUCTS										*/
/****************************************************/

typedef struct s_phil	t_phil;
typedef struct s_data	t_data;
typedef struct timeval	t_timeval;

/*--------------------------------------*/

struct s_phil
{
	int					id;
	int					meals;
	long long			lst_ml;
	struct s_data		*d;
	pthread_t			i_th;
};

/*--------------------------------------*/

struct s_data
{
	int					s_free;
	int					start;
	int					nb_phi;
	long long			t_init;
	long long			t_die;
	long long			t_eat;
	long long			t_sleep;
	int					nb_eat;
	int					d_meals;
	struct s_phil		**p;
	pthread_mutex_t		king_of_mtx;
	pthread_mutex_t		*mtx;
};

/****************************************************/
/*		PROTOTYPES 									*/
/****************************************************/

/*--		Init.c-----------------------------*/
int			thread_init(t_data *d);
int			mutex_init(t_data *d);
int			phil_init(t_data *d);
int			data_init(char **av, t_data *d);

/*--		Philo.c----------------------------*/
void		*actions_init(void *pd);
void		ft_die_alone(t_phil *p);
void		ft_live(t_phil *p);
void		ft_talk(t_phil *p, char *s);

/*--		End.c------------------------------*/
void		ft_loop(t_data *d);
int			ft_end(t_data *d);
int			ft_exit(char *s, t_data *d);

/*--		Utils.c----------------------------*/
int			ft_atoi(char *s);
int			ft_isdigit(int ac, char **av);
int			ft_strcmp(const char *s1, const char *s2);
long long	ft_atoll(char *s);

/*-------	Time_Utils.c-----------------------*/
long long	get_time(void);
void		make_time(useconds_t t_x);

#endif
