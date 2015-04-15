/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorAsm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/15 18:15:34 by mle-roy           #+#    #+#             */
/*   Updated: 2015/04/15 18:21:22 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

t_error				*initError(const char *error, int line)
{
	t_error			*new;

	if ((new = (t_error *)malloc(sizeof(*new))) == NULL)
		ft_exit("fail to malloc error !", 3);
	new->line = line;
	new->error = ft_strdup(error);
	new->next = NULL;
	return (new);
}

void				addError(const char *error, int line, t_asm *asM)
{
	t_error			*new;
	t_error			*ptr;

	new = initError(error, line);
	if (asM->errors == NULL)
		asM->errors = new;
	else
	{
		ptr = asM->errors;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	asM->isError = TRUE;
}
