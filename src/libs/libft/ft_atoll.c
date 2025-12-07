/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonte <hkonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:58:21 by hkonte            #+#    #+#             */
/*   Updated: 2024/11/29 13:15:20 by hkonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	ft_is_sign(char c)
{
	return (c == '+' || c == '-');
}

static long long	ft_is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (c == '\r' || c == '\v' || c == '\f');
}

long long	ft_atoll(const char *nptr)
{
	long long	result;
	long long			i;
	long long			p;
	long long			val;

	result = 0;
	i = 0;
	p = 1;
	while (nptr[i] != '\0' && ft_is_space(nptr[i]))
		i++;
	if (ft_is_sign(nptr[i]))
	{
		if (nptr[i] == '-')
			p *= -1;
		i++;
	}
	while (nptr[i] != '\0')
	{
		val = (long long)(nptr[i] - '0');
		if (val < 0 || val > 9)
			return (p * result);
		result = result * 10 + val;
		i++;
	}
	return ((long long)p * result);
}
