/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseArgs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/16 16:00:10 by mle-roy           #+#    #+#             */
/*   Updated: 2015/04/20 18:40:26 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include "libft.h"


t_op		op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
	 "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
	 "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
	 "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
	 "load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
	 "store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
	 "long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

int					addArgToList(t_token *ptr, int start, int end)
{
	printf("ARG - \n");
	write(1, &(ptr->arg)[start], end - start);
	write(1, "\n", 1);
	return (end - start);
}

int					getArgList(t_token *ptr)
{
	int				ret;
	int				i;
	int				start;

	ret = 0;
	i = 0;
	start = 0;
	while ((ptr->arg)[i])
	{
		if ((ptr->arg)[i] == SEPARATOR_CHAR)
		{
			start += (addArgToList(ptr, start, i) + 1);
			ret++;
		}
		i++;
	}
	if (start != i)
	{
		addArgToList(ptr, start, i);
		ret++;
	}
	return (ret);
}

void				addArgs(t_token *ptr, t_op op, t_asm *asM)
{
	(void)asM;
	getArgList(ptr);
	printf("TOKEN[%d]: [%s][%s]\n", ptr->line, ptr->token, ptr->arg);
	printf("OP[%d][%s] : [nbArg : %d]\n", op.opCode, op.name, op.nbArg);

	if (getArgList(ptr) != op.nbArg)
		addError("Wrong argument number", ptr->line, asM);
}

void				parseArgs(t_asm *asM)
{
	t_token			*ptr;
	int				i;

	ptr = asM->tokens;
	while (ptr)
	{
		if (!(ptr->isLabel))
		{
			i = 0;
			while (op_tab[i].opCode)
			{
				if (!ft_strcmp(ptr->token, op_tab[i].name))
				{
					addArgs(ptr, op_tab[i], asM);
					break ;
				}
				i++;
			}
			if (i == 16)
				addError("Wrong instruction", ptr->line, asM);
		}
		ptr = ptr->next;
	}
}
