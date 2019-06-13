/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 17:37:30 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:26:27 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

# define FFLEFT format->flag_left
# define FFZERO format->flag_zero
# define FFHASH format->flag_hash
# define FFSPAC format->flag_space
# define FFSIGN format->flag_sign
# define FWIDTH format->field_width
# define FPRECI format->precision
# define FCONV format->conversion
# define UCM ((unsigned char*)&m)
# define UCN ((unsigned char*)&n)
# define PFBUF 1024
# define HC ((t_format*)(head->content))

extern int g_fd;

typedef uint64_t	t_bint[17];
typedef uint64_t	t_hint[258];

typedef enum
{
	none,
	hh,
	h,
	l,
	ll,
	L,
	j,
	z
}	t_len_mod;

typedef struct		s_format
{
	unsigned short	flag_hash : 1;
	unsigned short	flag_zero : 1;
	unsigned short	flag_left: 1;
	unsigned short	flag_space : 1;
	unsigned short	flag_sign : 1;
	int				field_width;
	unsigned short	flag_prec : 1;
	int				precision;
	t_len_mod		len_mod;
	char			conversion;
	char			*buffer;
	int				buf_size;
}					t_format;

int					ft_printf(const char *format, ...);
int					ft_dprintf(int i, const char *format, ...);

/*
**	The input string is cut into different node of a linked list.
**	Each node contain a stuct that contain either:
**	- characters wich doesn't need conversion (classic string)
**	- characters wich needs conversion "%..."
*/

size_t				ft_size_word(const char *str);
t_format			*ft_iniformat(const char *str, size_t s, va_list args);
int					ft_ptf_atoi(const char *str, t_format *format, t_bool conv);
void				ft_formattozero(t_format *format);

/*
**	Those functions convert the printf's instructions into the wanted string.
**	One fuction for each type of conversion.
*/

int					ft_sub_unknown(t_format *format, va_list args, char *buff);
int					ft_sub_percent(t_format *format, va_list args, char *buff);
int					ft_sub_char(t_format *format, va_list args, char *buff);
int					ft_sub_string(t_format *format, va_list args, char *buff);
int					ft_sub_address(t_format *format, va_list args, char *buff);
int					ft_sub_dec(t_format *format, va_list args, char *buff);
int					ft_sub_uoctal(t_format *format, va_list args, char *buff);
int					ft_sub_udec(t_format *format, va_list args, char *buff);
int					ft_sub_uhex(t_format *format, va_list args, char *buff);
int					ft_sub_float(t_format *format, va_list args, char *buff);
int					ft_sub_bin(t_format *format, va_list args, char *buff);
uintmax_t			ft_lenmod_u(t_len_mod tlen, va_list args);

/*
**	The following functions are used in differents convertion types.
**	They give the output the expected format (width, flags, ...).
**	tools.c
*/

int					ft_buff(char *buff, char c, t_bool clear);
char				*ft_width(char *output, int width, t_bool left,\
						t_bool zero);
t_bool				ft_round(char *num, int len, t_bint *valnum, \
						t_bint *valdenum);
t_bool				ft_round_ld(char *num, int len, t_hint *valnum, \
						t_hint *valdenum);
t_bool				ft_round_e(char *num, int len, t_bint *valnum, \
						t_bint *valdenum);
t_bool				ft_round_ld_e(char *num, int len, t_hint *valnum, \
						t_hint *valdenum);
int					ft_parse_dbl(const double n, t_format *format, char *buff);
int					ft_parse_ldbl(const long double n, t_format *format, \
						char *buff);
int					ft_getfirstdigit_ldbl(long double n);
int					ft_get_len_uhex(uintmax_t num, t_format *format);
int					ft_post_printing(int ret, t_format *format);
int					ft_pre_printing_dec(t_format *format, int len, char *buff,\
						t_bool sign);
int					ft_pre_printing_float(t_format *format, int len, \
						t_bool sign);
int					ft_pre_printing_add(t_format *format, int len, char *buff);
int					ft_pre_printing_uhex(t_format *format, int len, char *buff,\
						int tmp);
int					ft_pre_printing_uoct(t_format *format, int len, char *buff,\
						int tmp);
int					ft_mod(t_format *format, char *buff, t_bool sign);
int					ft_endzero(t_format *format, int len, char *buff, int tmp);
int					ft_getstr_supone_de(t_bint *valnum, t_bint *valdenum, \
						int *tab, t_format *format);
int					ft_getstr_minone_de(t_bint *valnum, t_bint *valdenum, \
						int *tab, t_format *format);
int					ft_getstr_supone_lde(t_hint *valnum, t_hint *valdenum, \
						int *tab, t_format *format);
int					ft_getstr_minone_lde(t_hint *valnum, t_hint *valdenum, \
						int *tab, t_format *format);
void				ft_postround(int *fdigitexp, int *tmp, int *ret);
void				ft_expo(char *str, int *tab, int *ret);

/*
**	Those functions are used to manage float types.
**	Bint refers to double and hint to long double.
*/

uintmax_t			ft_lenmod_u(t_len_mod tlen, va_list args);
int					ft_getfirstdigit_d(double n);
int					ft_getstr_supone_d(t_bint *valnum, t_bint *valdenum,\
						int *tab, t_format *format);
int					ft_getstr_minone_d(t_bint *valnum, t_bint *valdenum,\
						int *tab, t_format *format);
int					ft_getfirstdigit_ld(double n);
int					ft_getstr_supone_ld(t_hint *valnum, t_hint *valdenum,\
						int *tab, t_format *format);
int					ft_getstr_minone_ld(t_hint *valnum, t_hint *valdenum,\
						int *tab, t_format *format);
void				ft_init_numdenum_ld(t_hint *valnum, t_hint *valdenum,\
						long double n, int firstdigitexpo);
void				ft_init_numdenum_d(t_bint *valnum, t_bint *valdenum,\
						double n, int firstdigitexpo);
char				ft_getnextdigit_dbl(t_bint *valnum, t_bint *valdenum);
char				ft_getnextdigit_ldbl(t_hint *valnum, t_hint *valdenum);

/*
**	Basic mathematical operations.
**	(bint/hint)_ope(down/up).c
*/

void				ft_init_bint(t_bint *num, uint64_t value, int32_t shift);
void				ft_mult_binti(t_bint *result, const t_bint *n, int m);
void				ft_pwd_bint(t_bint *result, int n, int pow);
t_bool				ft_bint_difzero(t_bint const *n);
unsigned char		ft_div_bint(t_bint *remainer, const t_bint *dividend, \
						t_bint const *divisor);
void				ft_init_hint(t_hint *num, uint64_t value, int32_t shift);
void				ft_mult_hinti(t_hint *result, const t_hint *n, int m);
void				ft_pwd_hint(t_hint *result, int n, int pow);
t_bool				ft_hint_difzero(t_hint const *n);
char				ft_div_hint(t_hint *remainer, const t_hint *dividend, \
						t_hint const *divisor);
uint64_t			ft_pwd_uint64(uint64_t n, int pow);

/*
**	Manipulation of those custom variables.
**	(bint/hint)_manip.c
*/

void				ft_lshift(t_bint *map, int shift);
void				ft_rshift(t_bint *map, int shift);
void				ft_bint_settozero(t_bint *n);
void				ft_add_bint(t_bint *result, const t_bint *n, \
						const t_bint *m);
void				ft_bintcpy(t_bint *dest, const t_bint *src);
void				ft_hint_lshift(t_hint *map, int shift);
void				ft_hint_rshift(t_hint *map, int shift);
void				ft_hint_settozero(t_hint *n);
void				ft_add_hint(t_hint *result, const t_hint *n, \
						const t_hint *m);
void				ft_hintcpy(t_hint *dest, const t_hint *src);

#endif
