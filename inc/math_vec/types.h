
/* Defines basic types for 2d vector storage and operations */ 
#ifndef MATH_VEC_TYPES_H
# define MATH_VEC_TYPES_H

typedef char			v2sc __attribute__((vector_size(2)));
typedef unsigned char	v2uc __attribute__((vector_size(2)));

typedef int				v2si __attribute__((vector_size(8)));
typedef unsigned int	v2ui __attribute__((vector_size(8)));

typedef long			v2sl __attribute__((vector_size(8)));
typedef unsigned long	v2ul __attribute__((vector_size(8)));

typedef float			v2f __attribute__((vector_size(8)));

typedef double			v2d __attribute__((vector_size(16)));

#endif
