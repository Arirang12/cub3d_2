#include "../cub.h"

t_garbage_collector	*gc_new_node(void *ptr)
{
	t_garbage_collector	*new_node;

	new_node = malloc(sizeof(t_garbage_collector));
	if (!new_node)
		return (NULL);
	new_node->already_free = 0;
	new_node->ptr = ptr;
	new_node->next = NULL;
	return (new_node);
}

t_garbage_collector	*gc_last_node(t_garbage_collector *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	gc_add_node_back(t_garbage_collector **lst, t_garbage_collector *new)
{
	t_garbage_collector	*last;

	if (!lst || !new)
		return ;
	last = gc_last_node(*lst);
	if (!last)
	{
		*lst = new;
		return ;
	}
	last->next = new;
}

void	free_all(t_garbage_collector **lst)
{
	t_garbage_collector	*tmp;

	while ((*lst))
	{
		if (!(*lst)->already_free && (*lst)->ptr)
			free((*lst)->ptr);
		tmp = (*lst);
		*lst = (*lst)->next;
		free(tmp);
	}
}

void	is_already_free(t_garbage_collector **gc, void *ptr)
{
	t_garbage_collector	*current;

	current = *gc;
	while (current)
	{
		if (current->ptr == ptr)
			current->already_free = 1;
		current = current->next;
	}
	free(ptr);
}
t_garbage_collector	**gc_instance(void)
{
	static t_garbage_collector	*gc = NULL;

	return (&gc);
}
