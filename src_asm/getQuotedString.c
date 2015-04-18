
#include "asm.h"
#include "libft.h"

static char			isQuote(char c)
{
	if (c == '\'' || c == '"')
		return (c);
	return (0);
}

static int			findLastQuote(char *s, int start, char quote)
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

static int			isTrailingChar(char *s, int idx)
{
	int			i;

	i = idx;
	while (&(s[idx]) && s[idx])
		idx++;
	return (idx - i);
}

char				*getQuotedString(t_token *ptr, t_asm *asM)
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
		ret = ft_strsub(ptr->arg, (start + 1), (end - (start + 1)));
	if (isTrailingChar(ptr->arg, (end + 1)))
		addError("Wrong format", ptr->line, asM);
	return (ret);
}
