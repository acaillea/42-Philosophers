/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:39:58 by acaillea          #+#    #+#             */
/*   Updated: 2022/02/24 17:40:00 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philosophers.h"

int	thread_init(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->nb_phi)
	{
		if (pthread_create(&d->p[i]->i_th, NULL, &actions_init, d->p[i]))
			return (-19);
		i++;
	}
	pthread_mutex_lock(&d->king_of_mtx);
	d->start = 1;
	pthread_mutex_unlock(&d->king_of_mtx);
	d->t_init = get_time();
	ft_loop(d);
	return (0);
}

int	mutex_init(t_data *d)
{
	int	i;

	i = -1;
	d->mtx = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * d->nb_phi);
	if (!d->mtx)
		return (-19);
	d->s_free = 4;
	i = -1;
	while (++i < d->nb_phi)
	{
		if (pthread_mutex_init(&d->mtx[i], NULL))
			return (-19);
	}
	if (pthread_mutex_init(&d->king_of_mtx, NULL))
		return (-19);
	return (0);
}

int	phil_init(t_data *d)
{
	int	i;

	i = -1;
	d->p = (t_phil **)malloc(sizeof(t_phil *) * d->nb_phi);
	if (!d->p)
		return (-19);
	while (++i < d->nb_phi)
	{	
		d->p[i] = (t_phil *)malloc(sizeof(t_phil));
		if (!d->p[i])
			return (-19);
		d->p[i]->id = i + 1;
		d->p[i]->meals = 0;
		d->p[i]->d = d;
		d->p[i]->lst_ml = get_time();
	}
	d->s_free = 2;
	return (0);
}

int	data_init(char **av, t_data *d)
{
	d->nb_phi = ft_atoi(av[1]);
	if (d->nb_phi > 200 || d->nb_phi <= 0)
		return (-19);
	d->t_die = ft_atoll(av[2]);
	if (d->t_die <= 0)
		return (-19);
	d->t_eat = ft_atoll(av[3]);
	if (d->t_eat <= 0)
		return (-19);
	d->t_sleep = ft_atoll(av[4]);
	if (d->t_sleep <= 0)
		return (-19);
	if (av[5])
	{
		d->nb_eat = ft_atoi(av[5]);
		if (d->nb_eat <= 0)
			return (-19);
		d->d_meals = d->nb_phi * d->nb_eat;
	}
	else
		d->nb_eat = -1;
	d->start = -1;
	d->t_init = get_time();
	return (0);
}
