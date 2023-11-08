/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cmd_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:53:33 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/08 13:56:09 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir_type	get_redir_type(t_tkn_type curr_tkn_type)
{
	if (curr_tkn_type == TKN_REDIR_IN)
		return (REDIR_IN);
	if (curr_tkn_type == TKN_REDIR_OUT)
		return (REDIR_OUT);
	if (curr_tkn_type == TKN_REDIR_APPEND)
		return (REDIR_APPEND);
	return (REDIR_HERE_DOC);
}

/*
	Updates the t_list *redir inside t_cmd. Can accept a token which is either
	a redirection (< << >> >) or a string, which is automatically set as a
	file name of the last node of the list.
*/
static void	update_cmd_redir(t_list *curr_tkn, t_cmd *cmd)
{
	t_tkn_data		*curr_content;
	t_redir_data	*new_content;
	t_list			*new_node;
	t_list			*last;

	last = NULL;
	curr_content = (t_tkn_data *)curr_tkn->content;
	if (is_redir(curr_content->type)) //== TKN_WORD
	{
		new_content = ft_calloc(1, sizeof(t_redir_data)); // protect
		new_content->type = get_redir_type(curr_content->type);
		new_content->file_name = NULL;
		new_node = ft_lstnew(new_content); // protect
		ft_lstadd_back(&cmd->redir, new_node);
		ft_printf("	ADD REDIR type [ %s ]\n", curr_content->str);
	}
	else
	{
		last = ft_lstlast(cmd->redir);
		((t_redir_data *)last->content)->file_name = ft_strdup(curr_content->str);
		ft_printf("	ADD REDIR: filename[ %s ]\n", ((t_redir_data *)last->content)->file_name);
	}
}

/*
	Update char **args inside t_cmd. If the recieved arg is the first, a
	cmd->args is allocated for the first time. If cmd->args already exists,
	it is updated with the new arg.
*/
static void	update_cmd_args(char *arg, t_cmd *cmd)
{
	int		i;
	int		n_args;
	char	**new_args;

	if (!cmd->args)
	{
		cmd->args = ft_calloc(2, sizeof(char *)); // protect
		cmd->args[0] = ft_strdup(arg); // protect
		cmd->args[1] = NULL; // protect
		return ;
	}
	n_args = 0;
	while (cmd->args[n_args])
		n_args++;
	new_args = ft_calloc(n_args + 2, sizeof(char *)); // protect
	i = 0;
	while (i < n_args)
	{
		new_args[i] = ft_strdup(cmd->args[i]);
		i++;
	}
	new_args[i] = ft_strdup(arg);
	new_args[i + 1] = NULL;
	free_dptr(cmd->args);
	// ft_printf("	ADD ARGS: { %s }\n", arg);
	cmd->args = new_args;
}

/*
	Take the current token assuming that syntax error are already catched in
	previous steps. @line - if (!prev_tkn) - verifies if the curr_tkn is
	the first of the token list.
*/
void	update_cmd_node(t_list *curr_tkn, t_list *prev_tkn, t_node *node)
{
	t_tkn_data	*curr_content;
	t_tkn_data	*prev_content;

	curr_content = NULL;
	prev_content = NULL;
	if (curr_tkn)
		curr_content = (t_tkn_data *)curr_tkn->content;
	if (!prev_tkn) // first iter
	{
		ft_printf("	No prev: curr_tkn [%s]\n", curr_content->str);
		if (is_redir(curr_content->type)) // in this case, curr_tkn is moved foreward
			update_cmd_redir(curr_tkn, node->content);
		else // if (curr_tkn_type == TKN_WORD)
			update_cmd_args(curr_content->str, node->content);
	}
	else
	{
		prev_content = (t_tkn_data *)prev_tkn->content;
		ft_printf("	Check curr_tkn[%s] with prev_tkn[%s]\n", curr_content->str, prev_content->str);
		if (!is_redir(curr_content->type) && !is_redir(prev_content->type))
			update_cmd_args(curr_content->str, node->content);
		else if (!is_redir(curr_content->type) && is_redir(curr_content->type))
			update_cmd_redir(curr_tkn, node->content);
		else
			update_cmd_redir(curr_tkn, node->content);
	}
}