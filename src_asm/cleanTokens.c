/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanTokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/15 15:08:17 by mle-roy           #+#    #+#             */
/*   Updated: 2015/04/16 16:46:26 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

#include <stdio.h> //debug

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
	/* printf("IN TS token : >%s<\n", token->token); */
	/* printf("END : %d\nISSPACE : %d\nVAL : %d\n", end, ft_isspace((token->token)[end]), (int)(token->token)[end]); */
	while ((end - 1) >= 0 && ft_isspace((token->token)[end - 1]))
		end--;
	/* while (end >= 0 && ((token->token)[end] == 0 || ft_isspace((token->token)[end]))) */
	/* 	end--; */
	if (end < 0)
		end = 0;
	/* printf("END2 : %d\n", end); */
	(token->token)[end] = 0;
	while (start < end && ft_isspace((token->token)[start]))
		start++;
	/* printf("START : %d\n", start); */
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

void					removeToken(t_token *prev, t_token *ptr, t_asm *asM)
{
	if (prev == NULL)
		asM->tokens = ptr->next;
	else
		prev->next = ptr->next;
	freeToken(ptr);
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
		/* printf("remove token ? : >%s<\n", ptr->token); */
		if (!ft_strlen(ptr->token))
		{
			removeToken(prev, ptr, asM);
			/* printf("YES\n"); */
			/* if (prev == NULL) */
			/* 	asM->tokens = ptr->next; */
			/* else */
			/* 	prev->next = ptr->next; */
			/* freeToken(ptr); */
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
	/* printf("IN FA\n"); */
	while (ptr)
	{
		/* printf("LOOP FA\n"); */
		/* printf("token[%d] : >%s<\n", ptr->line, ptr->token); */
		if (ptr->isLabel == FALSE)
		{
			/* printf("NO LABEL\n"); */
			getArgs(asM, ptr);
		}
		ptr = ptr->next;
	}
}

/* void					checkLine(char *s, int line, t_asm *asM) */
/* { */
/* 	int					i; */
/* 	char				*tmp; */

/* 	i = 0; */
/* 	while (s[i]) */
/* 	{ */
/* 		if (ft_strchr(AUTH_CHAR, s[i]) == NULL) */
/* 		{ */
/* 			tmp = ft_strjoinwsep("Unauthorized char : ", "", s[i]); */
/* 			addError(tmp, line, asM); */
/* 		} */
/* 		i++; */
/* 	} */
/* } */

/* void					checkChars(t_asm *asM) */
/* { */
/* 	t_token				*ptr; */

/* 	ptr = asM->tokens; */
/* 	while (ptr) */
/* 	{ */
/* 		if (ptr->token) */
/* 			checkLine(ptr->token, ptr->line, asM); */
/* 		if (ptr->arg) */
/* 			checkLine(ptr->arg, ptr->line, asM); */
/* 		ptr = ptr->next; */
/* 	} */
/* } */

void					cleanTokens(t_asm *asM)
{
	/* printf("CT1\n"); */
	removeComment(asM);
	/* printf("CT2\n"); */
	removeSpace(asM);
	/* printf("CT3\n"); */
	findLabels(asM);
	/* printf("CT4\n"); */
	removeEmptyTokens(asM);
	/* printf("CT5\n"); */
	findArgs(asM);
	/* printf("CT6\n"); */
	/* checkChars(asM); */
}
