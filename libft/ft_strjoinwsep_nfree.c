/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinwsep_nfree.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/11 15:28:57 by mle-roy           #+#    #+#             */
/*   Updated: 2015/01/31 21:41:43 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strjoinwsep_nfree(char *s1, char const *s2, char const c)
{
	char	*new;

	new = ft_strjoinwsep((const char *)s1, s2, c);
	free(s1);
	return (new);
}
