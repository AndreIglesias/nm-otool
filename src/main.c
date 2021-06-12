/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 22:32:16 by ciglesia          #+#    #+#             */
/*   Updated: 2021/06/13 01:34:11 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static	void	print_header(t_elf *elf)
{
	int	i;
	char	*arch[3] = {NULL, "ELF32", "ELF64"};

	ft_printf("ELF Header:\n");
	ft_printf("  Magic:   ");
	i = 0;
	while (i < EI_NIDENT)
		ft_printf("%.2x ", elf->identifier[i++]);
	ft_printf("\n  Class:                             ");
	ft_printf("%s\n", arch[elf->identifier[EI_CLASS]]);
	ft_printf("  Data:                              ");
	ft_printf("%u\n", elf->identifier[EI_DATA]);
}

/*
**	ELF_OSABI:
**	0x00 	System V
**	0x01 	HP-UX
**	0x02 	NetBSD
**	0x03 	Linux
**	0x04 	GNU Hurd
**	0x06 	Solaris
**	0x07 	AIX
**	0x08 	IRIX
**	0x09 	FreeBSD
**	0x0A 	Tru64
**	0x0B 	Novell Modesto
**	0x0C 	OpenBSD
**	0x0D 	OpenVMS
**	0x0E 	NonStop Kernel
**	0x0F 	AROS
**	0x10 	Fenix OS
**	0x11 	CloudABI
**	0x12 	Stratus Technologies OpenVOS
*/

static int		elf_ident(t_elf *elf)
{
	if ((elf->fd = open(elf->obj, O_RDONLY)) < 0)
	{
		ft_printf_fd(2, "ft_nm: '%s': No such file\n", elf->obj);
		return (0);
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

static void	ft_nm(char *obj)
{
	t_elf	*elf;

	if (!(elf = (t_elf *)malloc(sizeof(t_elf))))
		return ;
	elf->obj = obj;
	if (!elf_ident(elf))
	{
		free(elf);
		ft_printf_fd(2, "ft_nm: '%s': file format not recognized\n", obj);
		return ;
	}
	elf->class = elf->identifier[EI_CLASS];
	if (elf_header(elf))
		print_header(elf);
	free(elf);
}

int	main(int ac, char **av)
{
	char	*obj;
	int		i;

	obj = (ac == 1) ? "a.out" : av[1];
	ft_nm(obj);
	i = 2;
	while (i < ac)
		ft_nm(av[i++]);
	return (EXIT_SUCCESS);
}
