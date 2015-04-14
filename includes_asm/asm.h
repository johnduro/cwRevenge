/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/14 18:22:35 by mle-roy           #+#    #+#             */
/*   Updated: 2015/04/14 20:20:41 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# define USAGE "Usage : ./asm <file> [<file> ...]"
# define USAGE_LEN 33

#include <stdlib.h>
#include "op.h"

typedef char					t_bool;
typedef struct s_token			t_token;
typedef struct s_error			t_error;

struct					s_token
{
	int					line;
	char				*token;
	char				*arg;
	t_bool				isArg;
	t_token				*next;
};

struct					s_error
{
	int					line;
	char				*error;
	t_error				*next;
};

typedef struct			s_asm
{
	int					fd;
	t_token				*tokens;
	t_error				*errors;
	t_bool				isError;
	char				name[PROG_NAME_LENGTH];
	t_bool				isName;
	char				comment[COMMENT_LENGTH];
	t_bool				isComment;
}						t_asm;

void					compileFile(char *arg);
void					treatFile(t_asm *asM);

#endif
