/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node_to_linked_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:52:29 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/17 15:14:31 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*add_node_to_linked_list(t_token *head, void *content, int type)
{
	t_token	*new_node;

	if (!head)
	{
		head = create_node(content, type);
		return (head);
	}
	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	head->next = new_node;
	head->length++;
	new_node->length = head->length;
	new_node->type = type;
	new_node->content = content;
	new_node->next = NULL;
	return(new_node);
}