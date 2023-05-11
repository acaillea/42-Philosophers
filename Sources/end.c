/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:05:48 by acaillea          #+#    #+#             */
/*   Updated: 2022/03/29 13:05:50 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philosophers.h"

void	ft_loop(t_data *d)
{
	int	i;

	i = 0;
	while (19)
	{
		if (d->d_meals <= 0 && d->nb_eat != -1)
		{
			d->start = -1;
			pthread_mutex_lock(&d->king_of_mtx);
			break ;
		}
		if ((get_time() - d->p[i]->lst_ml) > d->t_die)
		{
			ft_talk(d->p[i], DEAD);
			d->start = -1;
			pthread_mutex_lock(&d->king_of_mtx);
			break ;
		}
		if (i == d->nb_phi - 1)
			i = -1;
		i++;
	}
	d->s_free = 8;
	ft_end(d);
}

int	ft_end(t_data *d)
{
	int	i;

	pthread_mutex_unlock(&d->king_of_mtx);
	i = -1;
	while (++i < d->nb_phi)
	{
		if (pthread_join(d->p[i]->i_th, NULL))
			return (ft_exit(END, d));
	}
	i = -1;
	while (++i < d->nb_phi)
	{
		if (pthread_mutex_destroy(&d->mtx[i]))
			return (ft_exit(MD_ER, d));
	}
	if (pthread_mutex_destroy(&d->king_of_mtx))
		return (ft_exit(MD_ER, d));
	return (0);
}

int	ft_exit(char *s, t_data *d)
{
	int	i;

	i = -1;
	printf("%s", s);
	if (d->s_free > 1)
	{
		while (++i < d->nb_phi)
			free(d->p[i]);
		free(d->p);
		if (d->s_free > 3)
		{
			free(d->mtx);
			if (d->s_free < 7)
			{
				i = -1;
				while (++i < d->nb_phi)
					if (pthread_mutex_destroy(&d->mtx[i]))
						return (printf(MD_ER));
				if (pthread_mutex_destroy(&d->king_of_mtx))
					return (printf(MD_ER));
			}
		}
	}
	free(d);
	return (0);
}
