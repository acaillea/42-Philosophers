/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:42:09 by acaillea          #+#    #+#             */
/*   Updated: 2022/02/17 17:42:10 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philosophers.h"

int	ft_atoi(char *s)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	if (s && s[i] && s[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (s && s[i])
	{
		res = (res * 10) + (s[i] - 48);
		i++;
		if (res * sign < -2147483648)
			return (-19);
		if (res * sign > 2147483647)
			return (-19);
	}
	return (res * sign);
}

long long	ft_atoll(char *s)
{
	long long	res;
	int			i;

	res = 0;
	i = 0;
	while (s && s[i])
	{
		res = (res * 10) + (s[i] - 48);
		i++;
	}
	return (res);
}

int	ft_isdigit(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < 48 || av[i][j] > 57)
				return (-19);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	char	*s1_str;
	char	*s2_str;
	size_t	i;

	s1_str = (char *)s1;
	s2_str = (char *)s2;
	i = 0;
	while (s1_str[i] && s2_str[i] && s1_str[i] == s2_str[i])
		i++;
	return ((unsigned char)s1_str[i] - (unsigned char)s2_str[i]);
}
