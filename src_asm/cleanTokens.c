/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanTokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/15 15:08:17 by mle-roy           #+#    #+#             */
/*   Updated: 2015/04/15 18:28:34 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

void					removeComment(t_asm *asM)
{
	t_token				*ptr;
	int					i;

	ptr = asM->tokens;
	while (ptr)
	{
		i = 0;
		while ((ptr->token)[i])
		{
			if ((ptr->token)[i] == COMMENT_CHAR)
				(ptr->token)[i] = 0;
			i++;
		}
		ptr = ptr->next;
	}
}

void					trimSpace(t_token *token)
{
	int					len;
	int					end;
	int					start;

	len = ft_strlen(token->token);
	end = len;
	start = 0;
	while (end >= 0 && ft_isspace((token->token)[end]))
		end--;
	(token->token)[end] = 0;
	while (start < end && ft_isspace((token->token)[start]))
		start++;
	if (start != 0 && (len - start) > 0)
		ft_memmove(token->token, &((token->token)[start]), (len - start) + 1);
}

void					removeSpace(t_asm *asM)
{
	t_token				*ptr;

	ptr = asM->tokens;
	while (ptr)
	{
		trimSpace(ptr);
		ptr = ptr->next;
	}
}

void					removeEmptyTokens(t_asm *asM)
{
	t_token				*ptr;
	t_token				*prev;
	t_token				*keep;
	t_bool				isPrev;

	ptr = asM->tokens;
	prev = NULL;
	while (ptr)
	{
		isPrev = TRUE;
		keep = ptr->next;
		if (!ft_strlen(ptr->token))
		{
			if (prev == NULL)
				asM->tokens = ptr->next;
			else
				prev->next = ptr->next;
			freeToken(ptr);
			isPrev = FALSE;
		}
		if (isPrev)
			prev = ptr;
		ptr = keep;
	}
}

void					getArgs(t_asm *asM, t_token *tok)
{
	int					i;

	i = 0;
	while ((tok->token)[i] && !ft_isspace((tok->token)[i]))
		i++;
	if ((tok->token)[i] == 0)
		addError("No argument(s) on instruction needing", tok->line, asM);
	else
	{
		(tok->token)[i++] = 0;
		while ((tok->token)[i] && ft_isspace((tok->token)[i]))
			i++;
		if ((tok->token)[i] == 0)
			addError("No argument(s) on instruction needing", tok->line, asM);
		else
			tok->arg = &((tok->token)[i]);
	}
}

void					findArgs(t_asm *asM)
{
	t_token				*ptr;

	ptr = asM->tokens;
	while (ptr)
	{
		if (ptr->isLabel == FALSE)
			getArgs(asM, ptr);
		ptr = ptr->next;
	}
}

void					cleanTokens(t_asm *asM)
{
	removeComment(asM);
	removeSpace(asM);
	findLabels(asM);
	removeEmptyTokens(asM);
	findArgs(asM);
}
