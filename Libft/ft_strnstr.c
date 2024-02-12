/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 10:58:28 by molla             #+#    #+#             */
/*   Updated: 2024/02/09 18:36:24 by molla            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	p;
	char	*str;

	str = (char *)haystack;
	i = 0;
	if (!*needle || (len == 0 && needle == NULL))
		return (str);
	if (len == 0)
		return (NULL);
	while (str[i] && i < len)
	{
		p = 0;
		if (needle[p] == str[i])
		{
			while (needle[p] == str[i + p] && i + p < len)
			{
				if (needle[++p] == '\0')
					return (str + i);
			}
		}
		i++;
	}
	return (NULL);
}
