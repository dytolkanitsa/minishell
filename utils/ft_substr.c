/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 19:02:40 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/22 19:58:31 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	n;

	n = 0;
	if (!s)
		return (0);
	result = (char *)malloc(len - start + 1);
	if (result == 0)
		return (0);
	while (start < len)
	{
		result[n] = s[start];
		n++;
		start++;
	}
	result[n] = 0;
	return (result);
}
