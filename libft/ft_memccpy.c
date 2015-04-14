/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 16:08:05 by mle-roy           #+#    #+#             */
/*   Updated: 2015/01/31 21:18:43 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	size_t		i;
	char		*c1;
	char		*c2;

	i = 0;
	c1 = (char *)s1;
	c2 = (char *)s2;
	while (i < n)
	{
		*c1 = *c2;
		if (c == *c2)
			return ((void *)++c1);
		c1++;
		c2++;
		i++;
	}
	return (NULL);
}
