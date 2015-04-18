
#include "asm.h"
#include "libft.h"

static char			addName(t_token *prev, t_token *ptr, t_asm *asM)
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

static char			addComment(t_token *prev, t_token *ptr, t_asm *asM)
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

void				getNameAndComment(t_asm *asM)
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
		if (!(asM->isName) && !ft_strcmp(ptr->token, ".name"))
			isPrev = addName(prev, ptr, asM);
		else if (!(asM->isComment) && !ft_strcmp(ptr->token, ".comment"))
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
