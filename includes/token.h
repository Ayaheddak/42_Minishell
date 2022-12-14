/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 01:15:25 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/17 05:30:58 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_token
{
	enum
	{
		TOKEN_STRING,
		TOKEN_PIPE,
		TOKEN_IN,
		TOKEN_OUT,
		TOKEN_APPEND,
		TOKEN_DELIMITER,
		AMBIGUOUS_REDIR,
	}	e_type;
	char			*value;
	int				split;
	struct s_token	*next;
}	t_token;
#endif