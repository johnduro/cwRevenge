/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatFile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/14 19:38:20 by mle-roy           #+#    #+#             */
/*   Updated: 2015/04/16 16:53:10 by mle-roy          ###   ########.fr       */
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
	new->isArg = FALSE;
	new->isLabel = FALSE;
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
	printf("FILE : >%s<\nFD : %d\nNAME : %s\nCOMMENT : %s\n", asM->fileName, asM->fd, asM->name, asM->comment);
	printf(">> TOKENS : \n");
	ptrTok = asM->tokens;
	while (ptrTok)
	{
		printf("> token [%d] :\ntoken : >%s<\narg : >%s<\nisLabel : %d\n\n", ptrTok->line, ptrTok->token, ptrTok->arg, ptrTok->isLabel);
		ptrTok = ptrTok->next;
	}
	printf("<<<<<<<<<<<<<<<<<<<\n");
	ptrErr = asM->errors;
	printf(">> ERRORS : \n");
	if (asM->isError)
	{
		while (ptrErr)
		{
			printf("> error [%d] : %s\n", ptrErr->line, ptrErr->error);
			ptrErr = ptrErr->next;
		}
	}
	printf("<<<<<<<<<<<<<<<<<<<\n");
	printf("************\n");
}

char			addName(t_token *prev, t_token *ptr, t_asm *asM)
{
	//FAIRE LE ADDNAME
	return (FALSE);
}

void			getNameAndComment(t_asm *asM)
{
	t_token		*ptr;
	t_token		*prev;
	t_token		*keep;
	t_bool		isPrev;

	ptr = asM->tokens;
	prev = NULL;
	while (ptr)
	{
		isPrev = TRUE;
		keep = ptr->next;
		if (!(asM->isName) && ft_strcmp(ptr->token, ".name"))
		{
			removeToken(prev, ptr, asM);
			isPrev = FALSE;
		}
		else if (!(asM->isComment) && ft_strcmp(ptr->token, ".comment"))
		{
			removeToken(prev, ptr, asM);
			isPrev = FALSE;
		}
		if (isPrev)
			prev = ptr;
		ptr = keep;
	}
}

void			treatFile(t_asm *asM)
{
	/* printf("TF1\n");; */
	getTokens(asM);
	/* printf("TF2\n");; */
//	printDebug(asM);
	cleanTokens(asM);
	/* printf("TF3\n");; */
	getNameAndComment(asM);
	if (!(asM->isError))
	{
		parseArgs(asM);
	}
	else
		write(1, "CAN'T COMPILE DAT FILE !!111!!!1!!\n", 35);
	printDebug(asM);
	/* printf("TF4\n");; */
}
