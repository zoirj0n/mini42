
#include "minishell.h"

void	deallocate_memory(void *memory)
{
	if (*(void **)memory != NULL)
		free(*(void **)memory);
	*(void **)memory = NULL;
}

void	release_token_memory(void *mem)
{
	t_token	*token;

	token = mem;
	deallocate_memory(&token->substr);
	if (token->sub_tokens != NULL)
		ft_lstclear(&token->sub_tokens, release_token_memory);
	deallocate_memory(&token);
}

void	release_string_array(char **split)
{
	size_t	i;

	if (split == NULL)
		return ;
	i = 0;
	while (split[i] != NULL)
	{
		deallocate_memory(&split[i]);
		i++;
	}
	deallocate_memory(&split);
}
