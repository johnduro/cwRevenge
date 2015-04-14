/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compileFile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/14 18:33:04 by mle-roy           #+#    #+#             */
/*   Updated: 2015/04/14 20:20:12 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "asm.h"
#include "libft.h"

t_asm			*initAsm(int fd)
{
	t_asm		*new;

	if ((new = (t_asm *)malloc(sizeof(*new))) == NULL)
		ft_exit("fail to malloc", 3);
	new->fd = fd;
	new->isError = 0;
	new->tokens = NULL;
	new->errors = NULL;
	new->name[0] = 0;
	new->isName = 0;
	new->comment[0] = 0;
	new->isComment = 0;
	return (new);
}

void			freeTokens(t_token *tokens)
{
	t_token		*ptr;

	while (tokens)
	{
		ptr = tokens->next;
		if (tokens->token)
			free(tokens->token);
		free(tokens);
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
	asM = initAsm(fd);
	treatFile(asM);
	freeAsm(asM);
}
