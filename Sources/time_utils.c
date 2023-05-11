/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 19:53:48 by acaillea          #+#    #+#             */
/*   Updated: 2022/02/26 19:53:51 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philosophers.h"

long long	get_time(void)
{
	t_timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	make_time(useconds_t t_x)
{
	useconds_t	t_start;
	useconds_t	t_up;

	t_start = get_time();
	t_up = t_start;
	while (t_up - t_start < t_x)
	{
		usleep(t_x);
		t_up = get_time();
	}
}
