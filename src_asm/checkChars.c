
#include "asm.h"
#include "libft.h"

static void					checkLine(char *s, int line, t_asm *asM)
{
	int					i;
	char				*tmp;

	i = 0;
	while (s[i])
	{
		if (ft_strchr(AUTH_CHAR, s[i]) == NULL)
		{
			tmp = ft_strjoinwsep("Unauthorized char : ", "", s[i]);
			addError(tmp, line, asM);
		}
		i++;
	}
}

void						checkChars(t_asm *asM)
{
	t_token				*ptr;

	ptr = asM->tokens;
	while (ptr)
	{
		if (ptr->token)
			checkLine(ptr->token, ptr->line, asM);
		if (ptr->arg)
			checkLine(ptr->arg, ptr->line, asM);
		ptr = ptr->next;
	}
}
