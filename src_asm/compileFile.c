/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compileFile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/14 18:33:04 by mle-roy           #+#    #+#             */
/*   Updated: 2015/04/15 17:55:51 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "asm.h"
#include "libft.h"

#include <stdio.h>

t_asm			*initAsm(int fd, char *arg, char *ptr)
{
	t_asm		*new;

	if ((new = (t_asm *)malloc(sizeof(*new))) == NULL)
		ft_exit("fail to malloc", 3);
	new->fd = fd;
	/* printf("???? > %d\n", (int)(ptr - arg)); */
	new->fileName = ft_strsub(arg, 0, (size_t)(ptr - arg));
	/* write(1, "ICICIIC\n", 8); */
	/* write(1, new->fileName, ft_strlen(new->fileName)); */
	/* write(1, "2CICIIC\n", 8); */
	new->isError = FALSE;
	new->tokens = NULL;
	new->errors = NULL;
	new->name[0] = 0;
	new->isName = FALSE;
	new->comment[0] = 0;
	new->isComment = FALSE;
	return (new);
}

void			freeToken(t_token *ptr)
{
	if (ptr->token)
		free(ptr->token);
	free(ptr);
}

void			freeTokens(t_token *tokens)
{
	t_token		*ptr;

	while (tokens)
	{
		ptr = tokens->next;
		freeToken(tokens);
		tokens = ptr;
	}
}

void			freeErrors(t_error *errors)
{
	t_error		*ptr;

	while (errors)
	{
		ptr = errors->next;
		if (errors->error)
			free(errors->error);
		free(errors);
		errors = ptr;
	}
}

void			freeAsm(t_asm *asM)
{
	if (asM->fd > 0)
		close(asM->fd);
	if (asM->tokens)
		freeTokens(asM->tokens);
	if (asM->errors)
		freeErrors(asM->errors);
	free(asM);
}

void			compileFile(char *arg)
{
	char		*ptr;
	int			fd;
	t_asm		*asM;

	if (((ptr = ft_strrchr(arg, '.')) == NULL) || ft_strcmp(ptr, ".s"))
	{
		write(1, "C PAS 1 .s !\n", 13);
		return ;
	}
	if ((fd = open(arg, O_RDONLY)) <= 0)
	{
		write(1, "asm : can't open file ", 22);
		ft_putendl(arg);
		return ;
	}
	/* printf("ici\n"); */
	asM = initAsm(fd, arg, ptr);
	/* printf("la\n"); */
	treatFile(asM);
	/* printf("yo\n"); */
	freeAsm(asM);
	/* printf("yolol\n"); */
}
