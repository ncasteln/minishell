/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_pipechain.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:49:46 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/07 14:02:16 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	In order:
		• char **env is prepared to be sent to execve()
		• stdin and stdout are redirected to pipe ends
		• stdin and stdout are redirected to redir (< << >> >)
		• if builtin, it's run separately with proper functions (no execve());
		• if normal cmd, execve() is called
*/
void	child_pipechain(t_data *data, t_node *node, int *fd_pipe, int *prev_pipe)
{
	char	**env;
	t_cmd	*cmd;

	cmd = (t_cmd *)node->content;
	env = convert_to_dptr(data->env);
	if (!env)
		exit(1);
	if (redirect_to_pipes(fd_pipe, prev_pipe, cmd)) // changed verify
		free_child_and_exit(data, env, 1);
	if (redirect_to_explicit(node))
		free_child_and_exit(data, env, 1);
	if (is_builtin(cmd))
		exit(call_builtin_function(cmd, data));
	// fprintf(stderr, "fdin [%d]", cmd->fd_in);
	// fprintf(stderr, "fdout [%d]", cmd->fd_out);
	if (cmd->args)
	{
		resolve_args(&cmd->args[0], env);
		if (execve(cmd->args[0], cmd->args, env))
		{
			error(cmd->args[0], NULL, CE_CMDNOTFOUND);
			free_child_and_exit(data, env, 127);
		}
	}
	else
		free_child_and_exit(data, env, 0);
}
