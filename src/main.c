/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 22:32:16 by ciglesia          #+#    #+#             */
/*   Updated: 2021/06/14 01:04:39 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int		elf_ident(t_elf *elf)
{
	if ((elf->fd = open(elf->obj, O_RDONLY)) < 0)
	{
		ft_printf_fd(2, "ft_nm: '%s': No such file\n", elf->obj);
		return (-1);
	}
	if (read(elf->fd, elf->identifier, EI_NIDENT) < EI_NIDENT)
	{
		close(elf->fd);
		return (0);
	}
	close(elf->fd);
	if (ft_strncmp((char *)elf->identifier, ELFMAG, SELFMAG))
		return (0);
	if (elf->identifier[EI_CLASS] != ELFCLASS32 &&
		elf->identifier[EI_CLASS] != ELFCLASS64)
		return (0);
	if (elf->identifier[EI_DATA] != ELFDATA2LSB &&
		elf->identifier[EI_DATA] != ELFDATA2MSB)
		return (0);
	if (elf->identifier[EI_VERSION] != EV_CURRENT)
		return (0);
	if (elf->identifier[EI_OSABI] > 0x12)
		return (0);
	return (1);
}

static int	elf_header(t_elf *elf)
{
	if ((elf->fd = open(elf->obj, O_RDONLY)) < 0)
	{
		ft_printf_fd(2, "ft_nm: '%s': No such file\n", elf->obj);
		return (0);
	}
	if (elf->class == ELFCLASS32)
	{
		if (read(elf->fd, &elf->elf_32, sizeof(elf->elf_32))
							< (ssize_t)sizeof(elf->elf_32))
		{
			close(elf->fd);
			return (0);
		}
	}
	else
	{
		if (read(elf->fd, &elf->elf_64, sizeof(elf->elf_64))
							< (ssize_t)sizeof(elf->elf_64))
		{
			close(elf->fd);
			return (0);
		}
	}
	close(elf->fd);
	return (1);
}

static void	ft_nm(char *obj, int nparams, int h)
{
	t_elf	*elf;
	int		err;

	if (!(elf = (t_elf *)malloc(sizeof(t_elf))))
		return ;
	elf->obj = obj;
	err = elf_ident(elf);
	if (err <= 0)
		free(elf);
	if (!err)
	{
		ft_printf_fd(2, "ft_nm: '%s': file format not recognized\n", obj);
		return ;
	}
	else if (err < 0)
		return ;
	elf->class = elf->identifier[EI_CLASS];
	if (nparams)
		ft_printf("%s:\n", obj);
	if (elf_header(elf) && h)
		print_header(elf);
	free(elf);
}

int	main(int ac, char **av)
{
	char	*obj;
	int		i;
	int		h;

	i = 1;
	h = 0;
	while (i < ac)
		h += (ft_strcmp(av[i++], "-h") == 0);
	obj = (ac == 1) ? "a.out" : av[1];
	ft_nm(obj, ac - 1, h > 0);
	i = 2;
	while (i < ac)
	{
		if (av[i][0] != '-')
			ft_nm(av[i], ac - 1, h > 0);
		i++;
	}
	return (EXIT_SUCCESS);
}
