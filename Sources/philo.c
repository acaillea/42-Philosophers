/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:11:05 by acaillea          #+#    #+#             */
/*   Updated: 2022/03/24 16:11:08 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philosophers.h"

void	*actions_init(void *pd)
{
	t_phil	*p;

	p = (struct s_phil *)pd;
	while (p->d->start == -1)
		;
	p->lst_ml = get_time();
	ft_die_alone(p);
	return (NULL);
}

void	ft_die_alone(t_phil *p)
{
	if (p->d->nb_phi == 1)
	{
		pthread_mutex_lock(&p->d->mtx[0]);
		ft_talk(p, FORK);
		pthread_mutex_unlock(&p->d->mtx[0]);
	}
	else
	{
		if (p->d->nb_phi % 2 == 0)
		{
			if (p->id % 2 == 0)
				make_time(p->d->t_eat / 2);
			ft_live(p);
		}
		else
		{
			if (p->id % 2 != 0)
				make_time(p->d->t_eat / 2);
			ft_live(p);
		}
	}
}

void	ft_live(t_phil *p)
{
	int	tmp;

	tmp = 0;
	while (p->d->start == 1)
	{
		if (p->id == p->d->nb_phi)
			tmp = p->d->nb_phi;
		pthread_mutex_lock(&p->d->mtx[p->id - 1]);
		ft_talk(p, FORK);
		pthread_mutex_lock(&p->d->mtx[p->id - tmp]);
		ft_talk(p, FORK);
		p->lst_ml = get_time();
		ft_talk(p, EAT);
		p->meals++;
		make_time(p->d->t_eat);
		ft_talk(p, SLEP);
		pthread_mutex_unlock(&p->d->mtx[p->id - 1]);
		pthread_mutex_unlock(&p->d->mtx[p->id - tmp]);
		make_time(p->d->t_sleep);
		ft_talk(p, THNK);
	}
}

void	ft_talk(t_phil *p, char *s)
{
	long long	t_spend;

	if ((p->meals >= p->d->nb_eat && p->d->nb_eat != -1)
		|| p->d->start == -1 || (p->d->d_meals <= 0 && p->d->nb_eat != -1))
		return ;
	pthread_mutex_lock(&p->d->king_of_mtx);
	t_spend = get_time() - p->d->t_init;
	if (ft_strcmp(s, EAT) == 0)
		p->d->d_meals--;
	if (p->d->start == 1)
		printf("[%06llu] %03d %s\n", t_spend, p->id, s);
	pthread_mutex_unlock(&p->d->king_of_mtx);
}
