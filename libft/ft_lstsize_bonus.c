
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*node;
	int		size;

	size = 0;
	node = lst;
	while (node != NULL)
	{
		node = node->next;
		size++;
	}
	return (size);
}
