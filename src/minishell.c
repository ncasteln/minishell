/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:38:38 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/10 17:22:22 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_empty_input(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t') // check also \t ??? and other ???
		i++;
	if (ft_strlen(s) == i)
		return (1);
	return (0);
}

static void	init_data(t_data *data, char **env)
{
	data->env = init_env(env); // need to check in case of empty environment ???
	data->input = NULL;
	data->tokens = NULL;
	data->tree = NULL;
	data->err = NULL;
	data->e_code = 0;
}

static void	process_input(t_data *data)
{
	lexer(data->input, &data->tokens);
	if (data->tokens) // can be false ?
	{
		data->err = parse(data->tokens);
		if (data->err)
		{
			data->e_code = 258;
			ft_printf("\033[91mminishell: syntax error near unexpected token `%s'\033[0m\n", data->err);
		}
	}
	if (!data->err)
	{
		data->tree = build_syntax_tree(data->tokens, 0);
		print_syntax_tree(data->tree);
	}
	if (data->tree)
		expansion(data->tree, data->env, data->e_code);
	here_doc(data->tree);
	add_history(data->input); // not always to do
	free_data(data);
	exit(1);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc > 1 || argv[1])
		return (1); // custom err
	init_data(&data, env);
	if (!data.env)
		return (1); // custom err
	while (1)
	{
		data.input = readline("minishell $ "); // ft_strdup("<in cat -e | wc -l -o  -i >out2 | iuhe"); // readinput("minishell $ ");
		if (data.input && !is_empty_input(data.input)) // nest if condition inside
			process_input(&data);
		ft_printf("\033[0;35m=========================================================================\033[0m\n");
	}
	if (data.env)
	{
		env_dlst_clear(&data.env);
		data.env = NULL;
	}
	return (0);
}
