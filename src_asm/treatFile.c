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

char			isQuote(char c)
{
	if (c == '\'' || c == '"')
		return (c);
	return (0);
}

int				findLastQuote(char *s, int start, char quote)
{
	start++;
	while (s[start])
	{
		if (s[start] == quote)
			return (start);
		start++;
	}
	return (0);
}

char			*getQuotedString(t_token *ptr, t_asm *asM)
{
	char		*ret;
	char		quote;
	int			i;
	int			start;
	int			end;

	i = 0;
	start = 0;
	end = 0;
	ret = NULL;
	while ((ptr->arg)[i])
	{
		if ((quote = isQuote((ptr->arg)[i])) != 0)
		{
			start = i;
			end = findLastQuote(ptr->arg, start, quote);
			break ;
		}
		i++;
	}
	if (end != 0)
		ret = ft_strsub(ptr->arg, start, (end - start));
	return (ret);
}

char			addName(t_token *prev, t_token *ptr, t_asm *asM)
{
	char		*name;

	if ((name = getQuotedString(ptr, asM)) == NULL)
	{
		addError("Invalid program name", ptr->line, asM);
		return (TRUE);
	}
	else
	{
		if (ft_strlen(name) > PROG_NAME_LENGTH)
		{
			addError("Program name too long", ptr->line, asM);
			free(name);
			return (TRUE);
		}
		else
		{
			ft_strcpy(asM->name, name);
			asM->isName = TRUE;
			removeToken(prev, ptr, asM);
		}
		free(name);
	}
	return (FALSE);
}

char			addComment(t_token *prev, t_token *ptr, t_asm *asM)
{
	char		*comment;

	if ((comment = getQuotedString(ptr, asM)) == NULL)
	{
		addError("Invalid comment", ptr->line, asM);
		return (TRUE);
	}
	else
	{
		if (ft_strlen(comment) > COMMENT_LENGTH)
		{
			addError("Program comment too long", ptr->line, asM);
			free(comment);
			return (TRUE);
		}
		else
		{
			ft_strcpy(asM->comment, comment);
			asM->isComment = TRUE;
			removeToken(prev, ptr, asM);
		}
		free(comment);
	}
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
			isPrev = addName(prev, ptr, asM);
		else if (!(asM->isComment) && ft_strcmp(ptr->token, ".comment"))
			isPrev = addComment(prev, ptr, asM);
		if (isPrev)
			prev = ptr;
		ptr = keep;
	}
	if (!(asM->isName))
		addError("Program name is missing", 0, asM);
	if (!(asM->isComment))
		addError("Program comment is missing", 0, asM);
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
