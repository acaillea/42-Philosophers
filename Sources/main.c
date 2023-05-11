/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prev1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:42:26 by acaillea          #+#    #+#             */
/*   Updated: 2022/02/17 17:42:28 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philosophers.h"

int	main(int ac, char **av)
{
	t_data	*d;

	if (ac < 5 || ac > 6)
		return (printf(NB_ER));
	d = (t_data *)malloc(sizeof(t_data));
	if (!d)
		return (printf(MA_ER));
	d->s_free = -1;
	if (ft_isdigit(ac, av))
		return (ft_exit(DI_ER, d));
	if (data_init(av, d))
		return (ft_exit(AR_ER, d));
	if (phil_init(d))
		return (ft_exit(MA_ER, d));
	if (mutex_init(d))
		return (ft_exit(MU_ER, d));
	if (thread_init(d))
		return (ft_exit(TH_ER, d));
	return (ft_exit("", d));
}
