/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findLabels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/15 16:32:10 by mle-roy           #+#    #+#             */
/*   Updated: 2015/04/15 16:55:45 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

/* int						isLabelChar(char c) */
/* { */
/* } */

void					checkLabel(t_token *token, char *label)
{
	int					i;
	t_token				*new;

	i = 0;
	/* while ((token->token)[i] && isLabelChar((token->token)[i])) */
	while ((token->token)[i] && ft_strchr(LABEL_CHARS, (token->token)[i]))
		i++;
	if (&(token->token)[i] == label)
	{
		i++;
		token->isLabel = TRUE;
		if (ft_strlen(&(token->token)[i]) > 0)
		{
			while (ft_isspace((token->token)[i]))
				i++;
			new = initToken(ft_strdup(&(token->token)[i]), token->line);
			new->next = token->next;
			token->next = new;
		}
		*(++label) = 0;
	}
}

void					findLabels(t_asm *asM)
{
	t_token				*ptr;
	char				*label;

	ptr = asM->tokens;
	while (ptr)
	{
		if ((label = ft_strchr(ptr->token, LABEL_CHAR)) != NULL)
			checkLabel(ptr, label);
		ptr = ptr->next;
	}
}
