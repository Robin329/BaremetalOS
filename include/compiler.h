#ifndef __COMPILER_H
#define __COMPILER_H

/*
 * The below symbols may be defined for one or more, but not ALL, of the above
 * compilers. We don't consider that to be an error, so set them to nothing.
 * For example, some of them are for compiler specific plugins.
 */
#ifndef __latent_entropy
#define __latent_entropy
#endif

#ifndef __randomize_layout
#define __randomize_layout __designated_init
#endif

#ifndef __no_randomize_layout
#define __no_randomize_layout
#endif

#ifndef randomized_struct_fields_start
#define randomized_struct_fields_start
#define randomized_struct_fields_end
#endif

#ifndef asm_volatile_goto
#define asm_volatile_goto(x...) asm goto(x)
#endif

#ifdef CONFIG_CC_HAS_ASM_INLINE
#define asm_inline asm __inline
#else
#define asm_inline asm
#endif

#ifndef __no_fgcse
#define __no_fgcse
#endif

/* Are two types/vars the same type (ignoring qualifiers)? */
#define __same_type(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))

/* Is this type a native word size -- useful for atomic operations */
#define __native_word(t)                                      \
  (sizeof(t) == sizeof(char) || sizeof(t) == sizeof(short) || \
   sizeof(t) == sizeof(int) || sizeof(t) == sizeof(long))

/* Helpers for emitting diagnostics in pragmas. */
#ifndef __diag
#define __diag(string)
#endif

#ifndef __diag_GCC
#define __diag_GCC(version, severity, string)
#endif

#define __diag_push() __diag(push)
#define __diag_pop() __diag(pop)

#define __diag_ignore(compiler, version, option, comment) \
  __diag_##compiler(version, ignore, option)
#define __diag_warn(compiler, version, option, comment) \
  __diag_##compiler(version, warn, option)
#define __diag_error(compiler, version, option, comment)                       \
  __diag_##compiler(version, error, option)

/* Compile time object size, -1 for unknown */
#ifndef __compiletime_object_size
#define __compiletime_object_size(obj) -1
#endif
#ifndef __compiletime_warning
#define __compiletime_warning(message)
#endif
#ifndef __compiletime_error
#define __compiletime_error(message)
#endif

#ifdef __OPTIMIZE__
#define __compiletime_assert(condition, msg, prefix, suffix)   \
  do {                                                         \
    extern void prefix##suffix(void) __compiletime_error(msg); \
    if (!(condition)) prefix##suffix();                        \
  } while (0)
#else
#define __compiletime_assert(condition, msg, prefix, suffix) \
  do {                                                       \
  } while (0)
#endif

#define _compiletime_assert(condition, msg, prefix, suffix) \
  __compiletime_assert(condition, msg, prefix, suffix)

/**
 * compiletime_assert - break build and emit msg if condition is false
 * @condition: a compile-time constant condition to check
 * @msg:       a message to emit if condition is false
 *
 * In tradition of POSIX assert, this macro will break the build if the
 * supplied condition is *false*, emitting the supplied error message if the
 * compiler has support to do so.
 */
#define compiletime_assert(condition, msg) \
  _compiletime_assert(condition, msg, __compiletime_assert_, __COUNTER__)

#define compiletime_assert_atomic_type(t) \
  compiletime_assert(__native_word(t),    \
                     "Need native word sized stores/loads for atomicity.")

/* &a[0] degrades to a pointer: a different type from an array */
#define __must_be_array(a) BUILD_BUG_ON_ZERO(__same_type((a), &(a)[0]))

#endif /* __COMPILER_H */