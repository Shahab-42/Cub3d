/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:48:32 by mbin-nas          #+#    #+#             */
/*   Updated: 2022/08/01 13:48:35 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *str, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i] != '\0')
	{
		f(i, &str[i]);
		i++;
	}
}

// int main()
// {
//     char str1[] = "abcdefghijklm";
// 	ft_striteri(str1, NULL);
// 	printf("%s\n", str1);
//     return(0);

// }