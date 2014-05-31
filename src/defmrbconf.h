#ifndef DEF_MRBCONF_H
#  define DEF_MRBCONF_H

#ifdef MRB_USE_FLOAT
# define DEF_MRB_USE_FLOAT 1
#else
# define DEF_MRB_USE_FLOAT 0
#endif
#ifdef MRB_INT16
# define DEF_MRB_INT16 1
#else
# define DEF_MRB_INT16 0
#endif
#ifdef MRB_INT64
# define DEF_MRB_INT64 1
#else
# define DEF_MRB_INT64 0
#endif
#ifdef MRB_NAN_BOXING
# define DEF_MRB_NAN_BOXING 1
#else
# define DEF_MRB_NAN_BOXING 0
#endif
#ifdef MRB_ENDIAN_BIG
# define DEF_MRB_ENDIAN_BIG 1
#else
# define DEF_MRB_ENDIAN_BIG 0
#endif
#ifdef MRB_WORD_BOXING
# define DEF_MRB_WORD_BOXING 1
#else
# define DEF_MRB_WORD_BOXING 0
#endif
#ifdef MRB_USE_IV_SEGLIST
# define DEF_MRB_USE_IV_SEGLIST 1
#else
# define DEF_MRB_USE_IV_SEGLIST 0
#endif
#ifndef MRB_FUNCALL_ARGC_MAX
# define MRB_FUNCALL_ARGC_MAX 16 /* default value from mruby/src/vm.c */
#endif
#ifndef MRB_HEAP_PAGE_SIZE
# define MRB_HEAP_PAGE_SIZE 1024 /* default value from mruby/src/vm.c */
#endif
#ifndef MRB_IVHASH_INIT_SIZE
# define MRB_IVHASH_INIT_SIZE 8 /* default value from mruby/src/variable.c */
#endif
#ifdef MRB_GC_TURN_OFF_GENERATIONAL
# define DEF_MRB_GC_TURN_OFF_GENERATIONAL 1
#else
# define DEF_MRB_GC_TURN_OFF_GENERATIONAL 0
#endif
#ifndef POOL_ALIGNMENT
# define POOL_ALIGNMENT 4 /* default value from mruby/src/pool.c */
#endif
#ifndef POOL_PAGE_SIZE
# define POOL_PAGE_SIZE 1600 /* default value from mruby/src/pool.c */
#endif
#ifndef MRB_STR_BUF_MIN_SIZE
# define MRB_STR_BUF_MIN_SIZE 128 /* default value from mruby/src/string.c */
#endif
#ifdef MRB_GC_FIXED_ARENA
# define DEF_MRB_GC_FIXED_ARENA 1
#else
# define DEF_MRB_GC_FIXED_ARENA 0
#endif
#ifdef ENABLE_DEBUG
# define DEF_ENABLE_DEBUG 1
#else
# define DEF_ENABLE_DEBUG 0
#endif
#ifdef DISABLE_DEBUG
# define DEF_DISABLE_DEBUG 1
#else
# define DEF_DISABLE_DEBUG 0
#endif
#ifdef DISABLE_STDIO
# define DEF_DISABLE_STDIO 1
#else
# define DEF_DISABLE_STDIO 0
#endif
#ifdef ENABLE_STDIO
# define DEF_ENABLE_STDIO 1
#else
# define DEF_ENABLE_STDIO 0
#endif


#endif /* ifndef DEF_MRBCONF_H */
