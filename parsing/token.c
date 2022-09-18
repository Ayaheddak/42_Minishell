/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:35:49 by aheddak           #+#    #+#             */
/*   Updated: 2022/09/18 04:35:50 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

token_t *init_token(int type, char *value)
{
	token_t *token = malloc (sizeof(token_t));
	token->type = type;
	token->value = value;
	return (token);
}