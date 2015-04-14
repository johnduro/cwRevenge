/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatFile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/14 19:38:20 by mle-roy           #+#    #+#             */
/*   Updated: 2015/04/14 20:23:29 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "asm.h"
#include "get_next_line.h"
#include "libft.h"

t_token			*initToken(char *line, int nbLine)
{
	t_token		*new;

	if ((new = (t_token *)malloc(sizeof(*new))) == NULL)
		ft_exit("fail to malloc token", 3);
	new->line = nbLine;
	new->token = line;
	new->arg = NULL;
	new->isArg = 0;
	new->next = NULL;
	return (new);
}

void			addToken(t_asm *asM, char *line, int nbLine)
{
	t_token		*new;
	t_token		*ptr;

	new = initToken(line, nbLine);
	if (asM->tokens == NULL)
		asM->tokens = new;
	else
	{
		ptr = asM->tokens;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

void			getTokens(t_asm *asM)
{
	char		*line;
	int			nbLine;

	nbLine = 1;
	while (get_next_line(asM->fd, &line)) //errors!
	{
		addToken(asM, line, nbLine);
		nbLine++;
	}
}

void			printDebug(t_asm *asM) //debug
{
	t_token		*ptrTok;
	t_error		*ptrErr;

	printf("**** DEBUG ****\n");
	printf("FD : %d\nNAME : %s\nCOMMENT : %s\n", asM->fd, asM->name, asM->comment);
	printf(">> TOKENS : \n");
	ptrTok = asM->tokens;
	while (ptrTok)
	{
		printf("> token [%d] :\ntoken : %s\narg : %s", ptrTok->line, ptrTok->token, ptrTok->arg);
		ptrTok = ptrTok->next;
	}
	printf("<<<<<<<<<<<<<<<<<<<\n");
	ptrErr = asM->errors;
	printf(">> ERRORS : \n");
	while (ptrErr)
	{
		printf("> error [%d] : %s\n", ptrErr->line, ptrErr->error);
		ptrErr = ptrErr->next;
	}
	printf("<<<<<<<<<<<<<<<<<<<\n");
	printf("************\n");
}

void			treatFile(t_asm *asM)
{
	getTokens(asM);
	printDebug(asM);
}
