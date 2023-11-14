/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_dptr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:49:33 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/14 11:15:49 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*prepare_var(char *name, char *value)
{
	char	*joined;
	char	*tmp;

	joined = ft_strjoin(name, "=");
	tmp = joined;
	joined = ft_strjoin(joined, value);
	free(tmp);
	return (joined);
}

/*
	Convert the t_list to char **, whose format is needed by the execve().
*/
char	**convert_to_dptr(t_list *env)
{
	char	**new_env;
	t_var	*var;
	int		n;
	int		i;
	char	*joined;

	n = get_exported_var_n(env);
	new_env = ft_calloc(n + 1, sizeof(char *)); // protect
	new_env[n] = NULL;
	i = 0;
	while (env)
	{
		var = (t_var *)env->content;
		if (var->to_export)
		{
			joined = prepare_var(var->name, var->value);
			new_env[i] = joined;
			i++;
		}
		env = env->next;
	}
	return (new_env);
}
