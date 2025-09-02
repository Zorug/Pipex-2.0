/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:58:28 by cgross-s          #+#    #+#             */
/*   Updated: 2024/11/02 19:58:29 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Allocates (with malloc(3)) and returns a new
string, which is the result of the concatenation
of ’s1’ and ’s2’.
*/
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*ss;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	ss = (char *)malloc((len + 1) * sizeof(char));
	if (!ss)
		return (NULL);
	ft_strlcpy(ss, s1, ft_strlen(s1) + 1);
	ft_strlcat(ss, s2, len + 1);
	return (ss);
}

/*
The new string.
NULL if the allocation fails.
*/