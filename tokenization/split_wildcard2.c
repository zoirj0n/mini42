
#include "minishell.h"

bool	count_quoted_words(const char *str, size_t *num_words, size_t *i)
{
	char	quote;

	if (str[*i] == '\'' || str[*i] == '\"')
	{
		quote = str[*i];
		*i += 1;
		while (str[*i] != quote && str[*i] != '\0')
			*i += 1;
		*num_words += 1;
		*i += 1;
		return (true);
	}
	return (false);
}

bool	split_quoted_wildcard(const char *wc, size_t *i, size_t *word_count,
	t_wildcard **wc_split)
{
	char		quote;
	char		*wc_seg;
	size_t		start;

	if (wc[*i] == '\'' || wc[*i] == '\"')
	{
		quote = wc[*i];
		start = *i;
		*i += 1;
		while (wc[*i] != quote && wc[*i] != '\0')
			*i += 1;
		wc_seg = remove_quote_characters(build_word_string(wc, start, *i));
		if (wc_seg != NULL && wc_seg[0] != '\0')
		{
			wc_split[*word_count] = build_wildcard_segment(wc_seg, false);
			*word_count += 1;
		}
		else
			deallocate_memory(&wc_seg);
		*i += 1;
		return (true);
	}
	return (false);
}
