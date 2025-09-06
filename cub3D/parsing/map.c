/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:12:12 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/09/06 15:16:07 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

t_map_list	*create_map_node(char *line)
{
	t_map_list	*new;

	new = malloc(sizeof(t_map_list));
	if (!new)
		return (NULL);
	new->line = ft_strdup(line);
	new->next = NULL;
	return (new);
}

void	free_map_list(t_map_list *list)
{
	t_map_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->line);
		free(tmp);
	}
}

void	add_map_line(t_map_list **list, t_map_list *new_node)
{
	t_map_list	*curr;

	if (!list || !new_node)
		return ;
	if (!*list)
	{
		*list = new_node;
		return ;
	}
	curr = *list;
	while (curr->next)
		curr = curr->next;
	curr->next = new_node;
}

int	map_height(t_map_list *head)
{
	int	i;

	i = 0;
	if (!head)
		return (i);
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

int	map_max_width(t_map_list *list)
{
	int	max_width;
	int	len;

	max_width = 0;
	while (list)
	{
		len = ft_strlen(list->line);
		if (len > max_width)
			max_width = len;
		list = list->next;
	}
	return (max_width);
}
