/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:12:12 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/09/06 12:14:02 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	is_map_line_valid(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

t_map_list *create_map_node(char *line)
{
	t_map_list *new;

	new = malloc(sizeof(t_map_list));
	if (!new)
		return (NULL);
	new->line = ft_strdup(line);
	new->next = NULL;
	return (new);
}

void free_map_list(t_map_list *list)
{
    t_map_list *tmp;
    while (list)
    {
        tmp = list;
        list = list->next;
        free(tmp->line);
        free(tmp);
    }
}

void add_map_line(t_map_list **list, t_map_list *new_node)
{
	t_map_list *curr;

	if (!list || !new_node)
		return ;
	if (!*list)
	{
		*list = new_node;
		return ;
	}
	curr = *list;
	while(curr->next)
		curr = curr->next;
	curr->next = new_node;
}

