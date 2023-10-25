/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 07:27:44 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/20 16:04:30 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Compiling Command
	cc ./src/expansion/main.c ./src/expansion/utils.c ./src/expansion/expansion.c ./src/expansion/build_str.c -I./include/ -I./mylib/libft/ -I./mylib/ft_printf/ -I./mylib/get_next_line/ -L./mylib/ -lmylib
*/

int main(int argc, char **argv, char **env)
{
	char	*s0 = "This is $USER and other shit"; 			// ---> ncasteln and other shit
	char	*s1 = "$USERHELLO";								// ---> []
	char	*s2 = "USER$?USER"; 							// ---> USER0USER
	char	*s3 = "$USER $PWD"; 							// ---> ncastelnncasteln
	char	*s4 = "$USER?";									// ncasteln?
	char	*s5 = "I am $USER I am in $PWD, I've got a lot of $";
	char	*s6 = "--> $ <--";
	char	*s7 = "$$$ $ $ $USER$$$$$";
	char	*s8 = "$NOTEXIST";
	char	*s9 = "$$$ $USER $@$#$$ $% $^ $& $* $( $) $_ $+ $: $?";
	char	*s10 = "Hello $USER$NOTHING$!!!";
	char	*s11 = "$PWD$";
	char	*s12 = "     $WTF    ";							// [9 blank spaces]
	char	*s13 = "Hello my name is $USER and my last command was $_";							// [9 blank spaces]
	char	*s14 = "$USER$?$USER"; 							// ---> ncasteln99ncasteln
	char	*s15 = "$USER $USER$ $USER%$?"; 							// ---> ncasteln99ncasteln
	char	*s16 = "$HOME $_$ $TERM% \\$ {$?}"; 							// ---> ncasteln99ncasteln

	char *new_string = expansion(s2, 99, env);
	free(new_string);

	return (0);
}