/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/14 18:28:07 by mle-roy           #+#    #+#             */
/*   Updated: 2015/04/14 20:18:31 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "asm.h"

/* open */
/* read */
/* write */
/* lseek */
/* close */
/* malloc */
/* realloc */
/* free */
/* exit */
/* perror / strerror (et, du coup, errno) */



int			main(int argc, char **argv)
{
	int		i;

	i = 1;
	if (argc < 2)
	{
		write(1, USAGE, USAGE_LEN);
		return (0);
	}
	while (i < argc)
	{
		compileFile(argv[i]);
		i++;
	}
	return (0);
}
