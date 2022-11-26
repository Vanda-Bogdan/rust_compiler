/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "grammar_with_code.y"

#include <stdio.h>
#include <stdbool.h>
#include "nodes.h"
#include "functions.c"
#include "tree_print.h"
extern int yylex(void);
struct program_node * prg;

#line 81 "grammar_with_code.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "grammar_with_code.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_FOR = 3,                        /* FOR  */
  YYSYMBOL_LOOP = 4,                       /* LOOP  */
  YYSYMBOL_IN = 5,                         /* IN  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_WHILE = 8,                      /* WHILE  */
  YYSYMBOL_LET = 9,                        /* LET  */
  YYSYMBOL_MUT = 10,                       /* MUT  */
  YYSYMBOL_FN = 11,                        /* FN  */
  YYSYMBOL_CONTINUE = 12,                  /* CONTINUE  */
  YYSYMBOL_ENUM = 13,                      /* ENUM  */
  YYSYMBOL_CONST = 14,                     /* CONST  */
  YYSYMBOL_STRUCT = 15,                    /* STRUCT  */
  YYSYMBOL_IMPL = 16,                      /* IMPL  */
  YYSYMBOL_TRAIT = 17,                     /* TRAIT  */
  YYSYMBOL_PUB = 18,                       /* PUB  */
  YYSYMBOL_CRATE = 19,                     /* CRATE  */
  YYSYMBOL_SELF = 20,                      /* SELF  */
  YYSYMBOL_SUPER = 21,                     /* SUPER  */
  YYSYMBOL_SELF_PARAM = 22,                /* SELF_PARAM  */
  YYSYMBOL_MUT_SELF_PARAM = 23,            /* MUT_SELF_PARAM  */
  YYSYMBOL_ID = 24,                        /* ID  */
  YYSYMBOL_INT_LITERAL = 25,               /* INT_LITERAL  */
  YYSYMBOL_TRUE = 26,                      /* TRUE  */
  YYSYMBOL_FALSE = 27,                     /* FALSE  */
  YYSYMBOL_STRING_LITERAL = 28,            /* STRING_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 29,             /* FLOAT_LITERAL  */
  YYSYMBOL_CHAR_LITERAL = 30,              /* CHAR_LITERAL  */
  YYSYMBOL_INT = 31,                       /* INT  */
  YYSYMBOL_BOOL = 32,                      /* BOOL  */
  YYSYMBOL_STRING = 33,                    /* STRING  */
  YYSYMBOL_FLOAT = 34,                     /* FLOAT  */
  YYSYMBOL_CHAR = 35,                      /* CHAR  */
  YYSYMBOL_36_ = 36,                       /* ';'  */
  YYSYMBOL_37_ = 37,                       /* '('  */
  YYSYMBOL_38_ = 38,                       /* '}'  */
  YYSYMBOL_39_ = 39,                       /* ']'  */
  YYSYMBOL_RIGHT_ARROW = 40,               /* RIGHT_ARROW  */
  YYSYMBOL_RETURN = 41,                    /* RETURN  */
  YYSYMBOL_BREAK = 42,                     /* BREAK  */
  YYSYMBOL_43_ = 43,                       /* '{'  */
  YYSYMBOL_44_ = 44,                       /* ':'  */
  YYSYMBOL_45_ = 45,                       /* '='  */
  YYSYMBOL_RANGE = 46,                     /* RANGE  */
  YYSYMBOL_RANGE_IN = 47,                  /* RANGE_IN  */
  YYSYMBOL_AND = 48,                       /* AND  */
  YYSYMBOL_OR = 49,                        /* OR  */
  YYSYMBOL_50_ = 50,                       /* '<'  */
  YYSYMBOL_51_ = 51,                       /* '>'  */
  YYSYMBOL_LESS_EQUAL = 52,                /* LESS_EQUAL  */
  YYSYMBOL_GREATER_EQUAL = 53,             /* GREATER_EQUAL  */
  YYSYMBOL_EQUAL = 54,                     /* EQUAL  */
  YYSYMBOL_NOT_EQUAL = 55,                 /* NOT_EQUAL  */
  YYSYMBOL_56_ = 56,                       /* '+'  */
  YYSYMBOL_57_ = 57,                       /* '-'  */
  YYSYMBOL_58_ = 58,                       /* '*'  */
  YYSYMBOL_59_ = 59,                       /* '/'  */
  YYSYMBOL_60_ = 60,                       /* '!'  */
  YYSYMBOL_UMINUS = 61,                    /* UMINUS  */
  YYSYMBOL_62_ = 62,                       /* '?'  */
  YYSYMBOL_63_ = 63,                       /* '.'  */
  YYSYMBOL_64_ = 64,                       /* '['  */
  YYSYMBOL_65_ = 65,                       /* ')'  */
  YYSYMBOL_66_ = 66,                       /* ','  */
  YYSYMBOL_YYACCEPT = 67,                  /* $accept  */
  YYSYMBOL_Program = 68,                   /* Program  */
  YYSYMBOL_ExprList_final = 69,            /* ExprList_final  */
  YYSYMBOL_ExprList = 70,                  /* ExprList  */
  YYSYMBOL_ExprWithoutBlock = 71,          /* ExprWithoutBlock  */
  YYSYMBOL_StructExprField = 72,           /* StructExprField  */
  YYSYMBOL_ExprWithBlock = 73,             /* ExprWithBlock  */
  YYSYMBOL_BlockExpr = 74,                 /* BlockExpr  */
  YYSYMBOL_StmtListSupreme = 75,           /* StmtListSupreme  */
  YYSYMBOL_StmtList = 76,                  /* StmtList  */
  YYSYMBOL_Stmt = 77,                      /* Stmt  */
  YYSYMBOL_StmtDecl = 78,                  /* StmtDecl  */
  YYSYMBOL_LetStmt = 79,                   /* LetStmt  */
  YYSYMBOL_DeclarationStmt = 80,           /* DeclarationStmt  */
  YYSYMBOL_Enum = 81,                      /* Enum  */
  YYSYMBOL_EnumItems_final = 82,           /* EnumItems_final  */
  YYSYMBOL_EnumItems = 83,                 /* EnumItems  */
  YYSYMBOL_EnumItem = 84,                  /* EnumItem  */
  YYSYMBOL_FunctionWithBlock = 85,         /* FunctionWithBlock  */
  YYSYMBOL_FunctionWithoutBlock = 86,      /* FunctionWithoutBlock  */
  YYSYMBOL_FuncParamList_final = 87,       /* FuncParamList_final  */
  YYSYMBOL_FuncParamList = 88,             /* FuncParamList  */
  YYSYMBOL_FuncParam = 89,                 /* FuncParam  */
  YYSYMBOL_Struct = 90,                    /* Struct  */
  YYSYMBOL_StructFields_final = 91,        /* StructFields_final  */
  YYSYMBOL_StructFields = 92,              /* StructFields  */
  YYSYMBOL_StructField = 93,               /* StructField  */
  YYSYMBOL_Impl = 94,                      /* Impl  */
  YYSYMBOL_AssociatedItemsImpl_final = 95, /* AssociatedItemsImpl_final  */
  YYSYMBOL_AssociatedItemsImpl = 96,       /* AssociatedItemsImpl  */
  YYSYMBOL_AssociatedItemImpl = 97,        /* AssociatedItemImpl  */
  YYSYMBOL_Trait = 98,                     /* Trait  */
  YYSYMBOL_AssociatedItems_final = 99,     /* AssociatedItems_final  */
  YYSYMBOL_AssociatedItems = 100,          /* AssociatedItems  */
  YYSYMBOL_AssociatedItem = 101,           /* AssociatedItem  */
  YYSYMBOL_ConstStmt = 102,                /* ConstStmt  */
  YYSYMBOL_Type = 103,                     /* Type  */
  YYSYMBOL_Visibility = 104                /* Visibility  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  34
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1426

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  242
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  421

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   302


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    60,     2,     2,     2,     2,     2,     2,
      37,    65,    58,    56,    66,    57,    63,    59,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    44,    36,
      50,    45,    51,    62,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    64,     2,    39,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    43,     2,    38,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    40,    41,    42,    46,    47,    48,    49,    52,    53,
      54,    55,    61
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   113,   113,   119,   120,   121,   124,   125,   126,   127,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   241,   242,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   257,   258,
     263,   264,   267,   268,   271,   272,   273,   274,   277,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   313,   316,   317,   318,   321,
     322,   325,   326,   327,   328,   329,   330,   331,   332,   336,
     337,   340,   341,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   357,   358,   361,   362,   367,   368,
     371,   372,   373,   376,   377,   380,   381,   385,   386,   389,
     390,   393,   394,   397,   398,   399,   400,   405,   408,   409,
     412,   413,   416,   417,   418,   419,   420,   421,   425,   426,
     427,   431,   432,   433,   434,   435,   436,   437,   438,   442,
     443,   444,   445
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "FOR", "LOOP", "IN",
  "IF", "ELSE", "WHILE", "LET", "MUT", "FN", "CONTINUE", "ENUM", "CONST",
  "STRUCT", "IMPL", "TRAIT", "PUB", "CRATE", "SELF", "SUPER", "SELF_PARAM",
  "MUT_SELF_PARAM", "ID", "INT_LITERAL", "TRUE", "FALSE", "STRING_LITERAL",
  "FLOAT_LITERAL", "CHAR_LITERAL", "INT", "BOOL", "STRING", "FLOAT",
  "CHAR", "';'", "'('", "'}'", "']'", "RIGHT_ARROW", "RETURN", "BREAK",
  "'{'", "':'", "'='", "RANGE", "RANGE_IN", "AND", "OR", "'<'", "'>'",
  "LESS_EQUAL", "GREATER_EQUAL", "EQUAL", "NOT_EQUAL", "'+'", "'-'", "'*'",
  "'/'", "'!'", "UMINUS", "'?'", "'.'", "'['", "')'", "','", "$accept",
  "Program", "ExprList_final", "ExprList", "ExprWithoutBlock",
  "StructExprField", "ExprWithBlock", "BlockExpr", "StmtListSupreme",
  "StmtList", "Stmt", "StmtDecl", "LetStmt", "DeclarationStmt", "Enum",
  "EnumItems_final", "EnumItems", "EnumItem", "FunctionWithBlock",
  "FunctionWithoutBlock", "FuncParamList_final", "FuncParamList",
  "FuncParam", "Struct", "StructFields_final", "StructFields",
  "StructField", "Impl", "AssociatedItemsImpl_final",
  "AssociatedItemsImpl", "AssociatedItemImpl", "Trait",
  "AssociatedItems_final", "AssociatedItems", "AssociatedItem",
  "ConstStmt", "Type", "Visibility", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-170)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     127,   -16,     4,     7,    19,     3,    23,    36,    60,   127,
    -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,   257,
      55,    58,    68,    92,   101,  -170,  -170,  -170,  -170,  -170,
      75,    73,    89,   110,  -170,  -170,  -170,  -170,  -170,  -170,
    -170,  -170,  -170,    -1,    -8,    75,  -170,    38,    75,  -170,
      97,    84,   100,    96,   116,   123,   162,   124,   125,   154,
     134,   146,  -170,    45,   169,   149,  -170,   186,    -4,   172,
     180,   158,  -170,   212,   201,   508,   221,  -170,   210,    84,
    -170,  -170,    34,  -170,  -170,   211,   100,  -170,  -170,    61,
    -170,  -170,  -170,   213,     9,     9,    75,    81,     9,    38,
     508,  -170,    -8,   119,  -170,   508,    75,  -170,    38,   214,
      84,   226,   223,   230,   239,  -170,  -170,    27,  -170,  -170,
    -170,  -170,  -170,  -170,   508,   508,   508,   563,   508,   508,
     508,   508,   916,  -170,   937,   240,  -170,  -170,  -170,  -170,
    -170,  -170,  -170,  -170,  -170,    75,   198,   228,  -170,  -170,
      75,   205,  -170,  -170,   241,  1293,  1313,  -170,    38,   508,
     583,   607,  -170,  -170,    75,   249,   254,  -170,   508,   508,
     508,   508,   453,  1125,  1146,  1293,  1313,  1293,  1313,   261,
    1332,   261,  1332,   121,   141,   121,   141,   253,   229,   631,
     655,  -170,   508,   563,   508,   508,   508,   508,   508,   508,
     508,   508,   508,   508,   508,   508,   508,  -170,   269,   508,
    -170,   508,   563,   508,   508,   508,   508,   508,   508,   508,
     508,   508,   508,   508,   508,   508,  -170,   272,   508,    -1,
    -170,     9,     9,   144,    15,  -170,  -170,   679,   703,   407,
    -170,  -170,  -170,   259,  1293,  1313,  -170,  -170,  -170,  -170,
     316,  1167,  1188,  1209,  1230,   262,  1293,  1313,   290,   305,
    1293,  1313,  -170,  -170,  -170,   508,   508,   508,  1293,  1313,
     261,  1332,   261,  1332,  1347,  1362,  1347,  1362,   138,   197,
     138,   197,   138,   197,   138,   197,   138,   197,   138,   197,
     164,   227,   164,   227,   121,   141,   121,   141,   293,   958,
     979,  1293,  1313,   261,  1332,   261,  1332,  1347,  1362,  1347,
    1362,   138,   197,   138,   197,   138,   197,   138,   197,   138,
     197,   138,   197,   164,   227,   164,   227,   121,   141,   121,
     141,   294,  1000,  1021,   267,  -170,  -170,   309,     6,  -170,
    -170,  -170,  -170,  -170,   508,   223,   223,   223,   223,  -170,
    -170,   298,  1293,  1313,  1042,  1063,  1084,  1105,   508,  -170,
    -170,   508,  -170,  -170,    46,     8,  -170,    75,   508,  1251,
    1272,   329,   331,  -170,  -170,   508,  -170,  -170,  -170,  -170,
     275,   276,    75,  -170,    75,   508,    10,   727,   751,   223,
     223,   223,   223,   277,  -170,  -170,   223,    13,   775,   799,
    -170,   508,  -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,
     508,  -170,  -170,   823,   847,   871,   895,  -170,  -170,  -170,
    -170
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,   239,     0,     2,
     130,   138,   151,   153,   155,   159,   163,   161,   157,     0,
       0,     0,     0,     0,   236,   231,   235,   232,   234,   233,
       0,     0,     0,     0,     1,   131,   152,   154,   156,   160,
     164,   162,   158,   183,   166,     0,   199,   200,     0,   236,
       0,   209,   218,     0,     0,     0,     0,   184,   186,     0,
       0,   188,   194,   172,     0,   167,   169,     0,     0,     0,
       0,   201,   203,     0,     0,     0,     0,   214,     0,   210,
     211,   216,     0,   223,   225,     0,   219,   220,   227,     0,
     240,   241,   242,     0,   185,   187,     0,     0,   189,   200,
       0,   165,   168,   171,   228,     0,     0,   198,   202,     0,
     209,     0,     0,     0,     0,    77,   114,   113,    12,    14,
      15,    11,    13,    10,     0,   112,    76,   103,     0,     0,
       0,     3,     0,   116,     0,     0,   207,   212,   213,   215,
     217,   221,   222,   224,   226,     0,   190,   192,   196,   182,
       0,     0,   180,   195,     0,   176,   175,   170,   200,     0,
       0,     0,   206,   204,     0,     0,     0,   119,     0,     0,
       3,     3,     0,     0,     0,   111,   110,    75,    74,   102,
     101,   109,   108,    59,    58,    61,    60,     0,     5,     7,
       6,   238,     0,   100,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    57,     0,     0,
     237,     0,    99,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    56,     0,     0,   183,
     197,   191,   193,     0,     0,   134,   129,     0,     0,     0,
     132,   137,   178,     0,   174,   173,   230,   229,   205,   208,
       0,     0,     0,     0,     0,     0,     7,     6,     0,     0,
     118,   117,    79,    78,    80,     4,     0,     0,    73,    71,
      98,    96,   107,   105,    69,    67,    65,    63,    44,    45,
      40,    41,    52,    53,    48,    49,    32,    33,    36,    37,
      16,    18,    20,    22,    24,    26,    28,    30,    94,     0,
       0,    72,    70,    97,    95,   106,   104,    68,    66,    64,
      62,    46,    47,    42,    43,    54,    55,    50,    51,    34,
      35,    38,    39,    17,    19,    21,    23,    25,    27,    29,
      31,    93,     0,     0,     0,   181,   179,     0,     0,   135,
     136,   128,   133,   177,     0,     0,     0,     0,     0,    89,
     115,     0,     9,     8,     0,     0,     0,     0,     3,    88,
      86,     3,    87,    85,     0,     0,   150,     0,     0,     0,
       0,   125,   124,   121,   120,     3,    84,    82,    83,    81,
       0,     0,     0,   148,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    91,    90,     0,     0,     0,     0,
     149,     0,   142,   141,   123,   122,   127,   126,    92,   147,
       0,   146,   145,     0,     0,     0,     0,   140,   139,   144,
     143
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -170,  -170,  -169,  -170,   -46,  -170,   175,  -108,  -170,  -170,
     106,   337,  -170,  -170,   330,  -170,  -170,   246,     5,   -12,
     122,   -82,   -95,   334,   -93,  -170,   242,   338,   248,  -170,
     280,   341,  -170,  -170,   270,    11,   -30,    17
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     8,   187,   188,   256,   133,   257,   152,     9,   239,
     240,    10,   241,    11,    12,    64,    65,    66,    77,    14,
      60,    61,    62,    15,    70,    71,    72,    16,    78,    79,
      80,    17,    85,    86,    87,    81,    31,    73
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      50,   255,   258,   153,   167,    13,   154,    38,    20,    56,
       7,    18,   146,   147,    13,    68,    63,    19,    74,    56,
      18,    57,    58,    59,    37,   337,    19,    24,    21,   132,
      42,    22,   104,    59,    25,    26,    27,    28,    29,   338,
      84,   105,   366,    23,   383,    76,   400,    32,     3,   409,
     367,   368,   384,   385,   155,   401,     7,    83,   410,   160,
      34,    67,    69,    88,   170,   243,   148,    30,    82,    89,
     171,   172,     1,    33,    84,     3,   162,   143,   173,   175,
     177,   179,   181,   183,   185,   189,   382,   138,    99,   151,
     100,    83,    43,   139,   142,    76,    82,    88,     3,    49,
     144,    44,     7,    89,    48,   237,    25,    26,    27,    28,
      29,     1,    45,   244,     3,   230,    51,   149,     7,    67,
     233,   150,   251,   253,   151,   336,   260,    82,    46,    53,
      54,    55,    52,    75,   248,    47,   153,   153,     1,    30,
       2,     3,     4,     5,     6,     7,   268,   270,   272,   274,
     276,   278,   280,   282,   284,   286,   288,   290,   292,   294,
     296,    90,   158,   299,   159,   301,   303,   305,   307,   309,
     311,   313,   315,   317,   319,   321,   323,   325,   327,   329,
     335,    91,   332,   207,   208,   209,    93,   151,    92,   380,
      94,    95,   381,   237,   203,   204,   205,   206,    96,    97,
     207,   208,   209,   226,   227,   228,   393,   101,   111,   112,
     103,   113,    98,   114,   234,   102,   106,   115,   107,   352,
     354,   356,   205,   206,   108,   116,   207,   208,   209,   117,
     118,   119,   120,   121,   122,   123,   109,   371,   372,   373,
     374,   235,   124,   236,   110,   135,   125,   126,   136,   140,
     134,   127,   128,   222,   223,   224,   225,   145,   164,   226,
     227,   228,   129,   166,   231,   130,   151,   168,     1,   131,
       2,     3,     4,     5,     6,   156,   169,   229,   250,   242,
     161,   404,   405,   406,   407,   224,   225,   249,   336,   226,
     227,   228,   264,   298,   232,   265,   331,   343,   369,   174,
     176,   178,   180,   182,   184,   186,   190,    -1,    -1,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   344,   387,   207,   208,   209,   238,   349,   350,   351,
     358,   361,   364,   365,   245,   375,   391,   386,   392,   398,
     394,   395,   408,   252,   254,   342,    35,   261,   157,    36,
     163,   334,   396,    39,   397,   413,   141,    40,   165,   137,
      41,     0,     0,     0,   415,     0,     0,   269,   271,   273,
     275,   277,   279,   281,   283,   285,   287,   289,   291,   293,
     295,   297,     0,     0,   300,     0,   302,   304,   306,   308,
     310,   312,   314,   316,   318,   320,   322,   324,   326,   328,
     330,     0,     0,   333,     0,     0,     0,     0,     0,     0,
     111,   112,     0,   113,   238,   114,   234,     0,     0,   115,
       0,     0,     0,     0,     0,     0,     0,   116,     0,     0,
       0,   117,   118,   119,   120,   121,   122,   123,     0,     0,
     353,   355,   357,   235,   124,   341,     0,     0,   125,   126,
       0,     0,     0,   127,   128,     0,   111,   112,     0,   113,
       0,   114,     0,     0,   129,   115,     0,   130,     0,     0,
       0,   131,     0,   116,     0,     0,     0,   117,   118,   119,
     120,   121,   122,   123,     0,     0,     0,     0,     0,     0,
     124,     0,     0,     0,   125,   126,     0,   259,     0,   127,
     128,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     129,   111,   112,   130,   113,     0,   114,   131,     0,   370,
     115,     0,     0,     0,     0,     0,     0,     0,   116,     0,
       0,     0,   117,   118,   119,   120,   121,   122,   123,     0,
       0,     0,     0,   388,     0,   124,     0,     0,     0,   125,
     126,     0,     0,     0,   127,   128,     0,     0,     0,     0,
     399,     0,     0,     0,     0,   129,   111,   112,   130,   113,
       0,   114,   131,     0,     0,   115,   414,     0,     0,     0,
       0,     0,     0,   116,     0,   416,     0,   117,   118,   119,
     120,   121,   122,   123,     0,     0,     0,     0,     0,     0,
     124,     0,     0,     0,   125,   126,     0,     0,     0,    -1,
      -1,     0,     0,     0,     0,     0,     0,     0,     0,   246,
     129,     0,     0,   130,     0,     0,     0,   131,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   247,     0,   207,   208,   209,     0,     0,
       0,     0,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   266,     0,   226,
     227,   228,     0,     0,     0,     0,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   267,     0,   207,   208,   209,     0,     0,     0,     0,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   339,     0,   226,   227,   228,
       0,     0,     0,     0,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   340,
       0,   207,   208,   209,     0,     0,     0,     0,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   402,     0,   226,   227,   228,     0,     0,
       0,     0,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   403,     0,   207,
     208,   209,     0,     0,     0,     0,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   411,     0,   226,   227,   228,     0,     0,     0,     0,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   412,     0,   207,   208,   209,
       0,     0,     0,     0,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   417,
       0,   226,   227,   228,     0,     0,     0,     0,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   418,     0,   207,   208,   209,     0,     0,
       0,     0,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   419,     0,   226,
     227,   228,     0,     0,     0,     0,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   420,     0,   207,   208,   209,     0,     0,     0,     0,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   191,     0,   226,   227,   228,
       0,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   210,     0,   207,   208,
     209,     0,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   359,     0,   226,
     227,   228,     0,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   360,     0,
     207,   208,   209,     0,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   362,
       0,   226,   227,   228,     0,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     363,     0,   207,   208,   209,     0,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   376,     0,   226,   227,   228,     0,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   377,     0,   207,   208,   209,     0,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   378,     0,   226,   227,   228,     0,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   379,     0,   207,   208,   209,     0,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,     0,     0,   226,   227,   228,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,     0,     0,   207,   208,   209,
     262,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,     0,     0,   226,   227,
     228,   263,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,     0,     0,   207,
     208,   209,   345,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,     0,     0,
     226,   227,   228,   346,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,     0,
       0,   207,   208,   209,   347,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
       0,     0,   226,   227,   228,   348,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,     0,     0,   207,   208,   209,   389,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,     0,     0,   226,   227,   228,   390,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,     0,     0,   207,   208,   209,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,     0,     0,   226,   227,   228,    -1,    -1,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,     0,     0,   226,   227,   228,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,     0,     0,   207,
     208,   209,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,     0,     0,   226,   227,   228
};

static const yytype_int16 yycheck[] =
{
      30,   170,   171,    98,   112,     0,    99,    19,    24,    10,
      18,     0,    94,    95,     9,    45,    24,     0,    48,    10,
       9,    22,    23,    24,    19,    10,     9,    24,    24,    75,
      19,    24,    36,    24,    31,    32,    33,    34,    35,    24,
      52,    45,    36,    24,    36,    11,    36,    24,    14,    36,
      44,    45,    44,    45,   100,    45,    18,    52,    45,   105,
       0,    44,    24,    52,    37,   158,    96,    64,    51,    52,
      43,    44,    11,    37,    86,    14,   106,    89,   124,   125,
     126,   127,   128,   129,   130,   131,    40,    82,    43,    43,
      45,    86,    37,    82,    89,    11,    79,    86,    14,    24,
      89,    43,    18,    86,     3,   151,    31,    32,    33,    34,
      35,    11,    44,   159,    14,   145,    43,    36,    18,   102,
     150,    40,   168,   169,    43,   233,   172,   110,    36,    19,
      20,    21,    43,    36,   164,    43,   231,   232,    11,    64,
      13,    14,    15,    16,    17,    18,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,    65,    43,   209,    45,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
      36,    65,   228,    62,    63,    64,    24,    43,    65,   358,
      66,    66,   361,   239,    56,    57,    58,    59,    44,    65,
      62,    63,    64,    62,    63,    64,   375,    38,     3,     4,
      24,     6,    66,     8,     9,    66,    44,    12,    38,   265,
     266,   267,    58,    59,    66,    20,    62,    63,    64,    24,
      25,    26,    27,    28,    29,    30,    24,   345,   346,   347,
     348,    36,    37,    38,    43,    24,    41,    42,    38,    38,
      75,    46,    47,    56,    57,    58,    59,    44,    44,    62,
      63,    64,    57,    37,    66,    60,    43,    37,    11,    64,
      13,    14,    15,    16,    17,   100,    37,    37,    24,    38,
     105,   389,   390,   391,   392,    58,    59,    38,   396,    62,
      63,    64,    39,    24,    66,    66,    24,    38,   344,   124,
     125,   126,   127,   128,   129,   130,   131,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,     5,   368,    62,    63,    64,   151,    65,    38,    24,
      37,    37,    65,    24,   159,    37,     7,   367,     7,   385,
      65,    65,    65,   168,   169,   239,     9,   172,   102,    19,
     108,   229,   382,    19,   384,   401,    86,    19,   110,    79,
      19,    -1,    -1,    -1,   410,    -1,    -1,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,    -1,    -1,   209,    -1,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,    -1,    -1,   228,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,    -1,     6,   239,     8,     9,    -1,    -1,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,
      -1,    24,    25,    26,    27,    28,    29,    30,    -1,    -1,
     265,   266,   267,    36,    37,    38,    -1,    -1,    41,    42,
      -1,    -1,    -1,    46,    47,    -1,     3,     4,    -1,     6,
      -1,     8,    -1,    -1,    57,    12,    -1,    60,    -1,    -1,
      -1,    64,    -1,    20,    -1,    -1,    -1,    24,    25,    26,
      27,    28,    29,    30,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    -1,    -1,    -1,    41,    42,    -1,    44,    -1,    46,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      57,     3,     4,    60,     6,    -1,     8,    64,    -1,   344,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    24,    25,    26,    27,    28,    29,    30,    -1,
      -1,    -1,    -1,   368,    -1,    37,    -1,    -1,    -1,    41,
      42,    -1,    -1,    -1,    46,    47,    -1,    -1,    -1,    -1,
     385,    -1,    -1,    -1,    -1,    57,     3,     4,    60,     6,
      -1,     8,    64,    -1,    -1,    12,   401,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    -1,   410,    -1,    24,    25,    26,
      27,    28,    29,    30,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    46,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      57,    -1,    -1,    60,    -1,    -1,    -1,    64,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    36,    -1,    62,    63,    64,    -1,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    36,    -1,    62,
      63,    64,    -1,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    36,    -1,    62,    63,    64,    -1,    -1,    -1,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    36,    -1,    62,    63,    64,
      -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    36,
      -1,    62,    63,    64,    -1,    -1,    -1,    -1,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    36,    -1,    62,    63,    64,    -1,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    36,    -1,    62,
      63,    64,    -1,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    36,    -1,    62,    63,    64,    -1,    -1,    -1,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    36,    -1,    62,    63,    64,
      -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    36,
      -1,    62,    63,    64,    -1,    -1,    -1,    -1,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    36,    -1,    62,    63,    64,    -1,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    36,    -1,    62,
      63,    64,    -1,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    36,    -1,    62,    63,    64,    -1,    -1,    -1,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    39,    -1,    62,    63,    64,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    39,    -1,    62,    63,
      64,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    39,    -1,    62,
      63,    64,    -1,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    39,    -1,
      62,    63,    64,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    39,
      -1,    62,    63,    64,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      39,    -1,    62,    63,    64,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    39,    -1,    62,    63,    64,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    39,    -1,    62,    63,    64,    -1,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    39,    -1,    62,    63,    64,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    39,    -1,    62,    63,    64,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    62,    63,    64,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    62,    63,    64,
      65,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    -1,    -1,    62,    63,
      64,    65,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    62,
      63,    64,    65,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    -1,    -1,
      62,    63,    64,    65,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    62,    63,    64,    65,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,    -1,    62,    63,    64,    65,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    62,    63,    64,    65,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    -1,    62,    63,    64,    65,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    62,    63,    64,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    62,    63,    64,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    -1,    62,    63,    64,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    62,
      63,    64,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    -1,    62,    63,    64
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    11,    13,    14,    15,    16,    17,    18,    68,    75,
      78,    80,    81,    85,    86,    90,    94,    98,   102,   104,
      24,    24,    24,    24,    24,    31,    32,    33,    34,    35,
      64,   103,    24,    37,     0,    78,    81,    85,    86,    90,
      94,    98,   102,    37,    43,    44,    36,    43,     3,    24,
     103,    43,    43,    19,    20,    21,    10,    22,    23,    24,
      87,    88,    89,    24,    82,    83,    84,   104,   103,    24,
      91,    92,    93,   104,   103,    36,    11,    85,    95,    96,
      97,   102,   104,    85,    86,    99,   100,   101,   102,   104,
      65,    65,    65,    24,    66,    66,    44,    65,    66,    43,
      45,    38,    66,    24,    36,    45,    44,    38,    66,    24,
      43,     3,     4,     6,     8,    12,    20,    24,    25,    26,
      27,    28,    29,    30,    37,    41,    42,    46,    47,    57,
      60,    64,    71,    72,    73,    24,    38,    97,    85,   102,
      38,   101,    85,    86,   102,    44,    88,    88,   103,    36,
      40,    43,    74,    89,    91,    71,    73,    84,    43,    45,
      71,    73,   103,    93,    44,    95,    37,    74,    37,    37,
      37,    43,    44,    71,    73,    71,    73,    71,    73,    71,
      73,    71,    73,    71,    73,    71,    73,    69,    70,    71,
      73,    39,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    62,    63,    64,
      39,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    62,    63,    64,    37,
     103,    66,    66,   103,     9,    36,    38,    71,    73,    76,
      77,    79,    38,    91,    71,    73,    36,    36,   103,    38,
      24,    71,    73,    71,    73,    69,    71,    73,    69,    44,
      71,    73,    65,    65,    39,    66,    36,    36,    71,    73,
      71,    73,    71,    73,    71,    73,    71,    73,    71,    73,
      71,    73,    71,    73,    71,    73,    71,    73,    71,    73,
      71,    73,    71,    73,    71,    73,    71,    73,    24,    71,
      73,    71,    73,    71,    73,    71,    73,    71,    73,    71,
      73,    71,    73,    71,    73,    71,    73,    71,    73,    71,
      73,    71,    73,    71,    73,    71,    73,    71,    73,    71,
      73,    24,    71,    73,    87,    36,    74,    10,    24,    36,
      36,    38,    77,    38,     5,    65,    65,    65,    65,    65,
      38,    24,    71,    73,    71,    73,    71,    73,    37,    39,
      39,    37,    39,    39,    65,    24,    36,    44,    45,    71,
      73,    74,    74,    74,    74,    37,    39,    39,    39,    39,
      69,    69,    40,    36,    44,    45,   103,    71,    73,    65,
      65,     7,     7,    69,    65,    65,   103,   103,    71,    73,
      36,    45,    36,    36,    74,    74,    74,    74,    65,    36,
      45,    36,    36,    71,    73,    71,    73,    36,    36,    36,
      36
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    67,    68,    69,    69,    69,    70,    70,    70,    70,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    72,    72,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    74,    74,
      75,    75,    76,    76,    77,    77,    77,    77,    78,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    81,    82,    82,    82,    83,
      83,    84,    84,    84,    84,    84,    84,    84,    84,    85,
      85,    86,    86,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    88,    88,    89,    89,    90,    90,
      91,    91,    91,    92,    92,    93,    93,    94,    94,    95,
      95,    96,    96,    97,    97,    97,    97,    98,    99,    99,
     100,   100,   101,   101,   101,   101,   101,   101,   102,   102,
     102,   103,   103,   103,   103,   103,   103,   103,   103,   104,
     104,   104,   104
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     1,     3,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     2,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     1,     1,     3,     3,
       3,     5,     5,     5,     5,     4,     4,     4,     4,     4,
       6,     6,     7,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     2,     1,     3,     3,     3,     3,     2,     2,
       2,     2,     1,     1,     1,     4,     1,     3,     3,     2,
       5,     5,     7,     7,     5,     5,     7,     7,     3,     2,
       1,     2,     1,     2,     1,     2,     2,     1,     1,     7,
       7,     5,     5,     8,     8,     6,     6,     6,     4,     5,
       3,     1,     2,     1,     2,     1,     2,     1,     2,     1,
       2,     1,     2,     1,     2,     5,     0,     1,     2,     1,
       3,     2,     1,     4,     4,     3,     3,     5,     4,     8,
       6,     8,     6,     0,     1,     2,     1,     2,     1,     2,
       3,     4,     3,     4,     1,     3,     3,     4,     5,     3,
       0,     1,     2,     1,     3,     4,     3,     5,     7,     0,
       1,     1,     2,     2,     1,     2,     1,     5,     0,     1,
       1,     2,     2,     1,     2,     1,     2,     1,     5,     7,
       7,     1,     1,     1,     1,     1,     1,     5,     5,     1,
       4,     4,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: StmtListSupreme  */
#line 113 "grammar_with_code.y"
                                                                                { (yyval.prg) = prg = ProgramCreate((yyvsp[0].stmt_list)); }
#line 1668 "grammar_with_code.tab.c"
    break;

  case 3: /* ExprList_final: %empty  */
#line 119 "grammar_with_code.y"
                                                                        { (yyval.expr_list) = ExprListFinal(0); }
#line 1674 "grammar_with_code.tab.c"
    break;

  case 4: /* ExprList_final: ExprList ','  */
#line 120 "grammar_with_code.y"
                                                                        { (yyval.expr_list) = ExprListFinal((yyvsp[-1].expr_list)); }
#line 1680 "grammar_with_code.tab.c"
    break;

  case 5: /* ExprList_final: ExprList  */
#line 121 "grammar_with_code.y"
                                                                        { (yyval.expr_list) = ExprListFinal((yyvsp[0].expr_list)); }
#line 1686 "grammar_with_code.tab.c"
    break;

  case 6: /* ExprList: ExprWithBlock  */
#line 124 "grammar_with_code.y"
                                                                        { (yyval.expr_list) = ExprList((yyvsp[0].expr)); }
#line 1692 "grammar_with_code.tab.c"
    break;

  case 7: /* ExprList: ExprWithoutBlock  */
#line 125 "grammar_with_code.y"
                                                                        { (yyval.expr_list) = ExprList((yyvsp[0].expr)); }
#line 1698 "grammar_with_code.tab.c"
    break;

  case 8: /* ExprList: ExprList ',' ExprWithBlock  */
#line 126 "grammar_with_code.y"
                                                                        { (yyval.expr_list) = ExprListAdd((yyvsp[-2].expr_list), (yyvsp[0].expr)); }
#line 1704 "grammar_with_code.tab.c"
    break;

  case 9: /* ExprList: ExprList ',' ExprWithoutBlock  */
#line 127 "grammar_with_code.y"
                                                                        { (yyval.expr_list) = ExprListAdd((yyvsp[-2].expr_list), (yyvsp[0].expr)); }
#line 1710 "grammar_with_code.tab.c"
    break;

  case 10: /* ExprWithoutBlock: CHAR_LITERAL  */
#line 131 "grammar_with_code.y"
                                                                        { (yyval.expr) = ExprFromCharLiteral((yyvsp[0].char_const)); }
#line 1716 "grammar_with_code.tab.c"
    break;

  case 11: /* ExprWithoutBlock: STRING_LITERAL  */
#line 132 "grammar_with_code.y"
                                                                                                        { (yyval.expr) = ExprFromStringLiteral((yyvsp[0].string_const)); }
#line 1722 "grammar_with_code.tab.c"
    break;

  case 12: /* ExprWithoutBlock: INT_LITERAL  */
#line 133 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = ExprFromIntLiteral((yyvsp[0].int_const)); }
#line 1728 "grammar_with_code.tab.c"
    break;

  case 13: /* ExprWithoutBlock: FLOAT_LITERAL  */
#line 134 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = ExprFromFloatLiteral((yyvsp[0].float_const)); }
#line 1734 "grammar_with_code.tab.c"
    break;

  case 14: /* ExprWithoutBlock: TRUE  */
#line 135 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = ExprFromBoolLiteral((yyvsp[0].bool_const)); }
#line 1740 "grammar_with_code.tab.c"
    break;

  case 15: /* ExprWithoutBlock: FALSE  */
#line 136 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = ExprFromBoolLiteral((yyvsp[0].bool_const)); }
#line 1746 "grammar_with_code.tab.c"
    break;

  case 16: /* ExprWithoutBlock: ExprWithoutBlock '+' ExprWithoutBlock  */
#line 137 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(plus, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1752 "grammar_with_code.tab.c"
    break;

  case 17: /* ExprWithoutBlock: ExprWithBlock '+' ExprWithoutBlock  */
#line 138 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(plus, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1758 "grammar_with_code.tab.c"
    break;

  case 18: /* ExprWithoutBlock: ExprWithoutBlock '+' ExprWithBlock  */
#line 139 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(plus, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1764 "grammar_with_code.tab.c"
    break;

  case 19: /* ExprWithoutBlock: ExprWithBlock '+' ExprWithBlock  */
#line 140 "grammar_with_code.y"
                                                                                                        { (yyval.expr) = OperatorExpr(plus, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1770 "grammar_with_code.tab.c"
    break;

  case 20: /* ExprWithoutBlock: ExprWithoutBlock '-' ExprWithoutBlock  */
#line 141 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(minus, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1776 "grammar_with_code.tab.c"
    break;

  case 21: /* ExprWithoutBlock: ExprWithBlock '-' ExprWithoutBlock  */
#line 142 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(minus, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1782 "grammar_with_code.tab.c"
    break;

  case 22: /* ExprWithoutBlock: ExprWithoutBlock '-' ExprWithBlock  */
#line 143 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(minus, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1788 "grammar_with_code.tab.c"
    break;

  case 23: /* ExprWithoutBlock: ExprWithBlock '-' ExprWithBlock  */
#line 144 "grammar_with_code.y"
                                                                                                        { (yyval.expr) = OperatorExpr(minus, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1794 "grammar_with_code.tab.c"
    break;

  case 24: /* ExprWithoutBlock: ExprWithoutBlock '*' ExprWithoutBlock  */
#line 145 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(mul, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1800 "grammar_with_code.tab.c"
    break;

  case 25: /* ExprWithoutBlock: ExprWithBlock '*' ExprWithoutBlock  */
#line 146 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(mul, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1806 "grammar_with_code.tab.c"
    break;

  case 26: /* ExprWithoutBlock: ExprWithoutBlock '*' ExprWithBlock  */
#line 147 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(mul, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1812 "grammar_with_code.tab.c"
    break;

  case 27: /* ExprWithoutBlock: ExprWithBlock '*' ExprWithBlock  */
#line 148 "grammar_with_code.y"
                                                                                                        { (yyval.expr) = OperatorExpr(mul, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1818 "grammar_with_code.tab.c"
    break;

  case 28: /* ExprWithoutBlock: ExprWithoutBlock '/' ExprWithoutBlock  */
#line 149 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(div_expr, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1824 "grammar_with_code.tab.c"
    break;

  case 29: /* ExprWithoutBlock: ExprWithBlock '/' ExprWithoutBlock  */
#line 150 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(div_expr, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1830 "grammar_with_code.tab.c"
    break;

  case 30: /* ExprWithoutBlock: ExprWithoutBlock '/' ExprWithBlock  */
#line 151 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(div_expr, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1836 "grammar_with_code.tab.c"
    break;

  case 31: /* ExprWithoutBlock: ExprWithBlock '/' ExprWithBlock  */
#line 152 "grammar_with_code.y"
                                                                                                        { (yyval.expr) = OperatorExpr(div_expr, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1842 "grammar_with_code.tab.c"
    break;

  case 32: /* ExprWithoutBlock: ExprWithoutBlock EQUAL ExprWithoutBlock  */
#line 153 "grammar_with_code.y"
                                                                                                        { (yyval.expr) = OperatorExpr(equal, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1848 "grammar_with_code.tab.c"
    break;

  case 33: /* ExprWithoutBlock: ExprWithoutBlock EQUAL ExprWithBlock  */
#line 154 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(equal, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1854 "grammar_with_code.tab.c"
    break;

  case 34: /* ExprWithoutBlock: ExprWithBlock EQUAL ExprWithoutBlock  */
#line 155 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(equal, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1860 "grammar_with_code.tab.c"
    break;

  case 35: /* ExprWithoutBlock: ExprWithBlock EQUAL ExprWithBlock  */
#line 156 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(equal, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1866 "grammar_with_code.tab.c"
    break;

  case 36: /* ExprWithoutBlock: ExprWithoutBlock NOT_EQUAL ExprWithoutBlock  */
#line 157 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(not_equal, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1872 "grammar_with_code.tab.c"
    break;

  case 37: /* ExprWithoutBlock: ExprWithoutBlock NOT_EQUAL ExprWithBlock  */
#line 158 "grammar_with_code.y"
                                                                                                        { (yyval.expr) = OperatorExpr(not_equal, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1878 "grammar_with_code.tab.c"
    break;

  case 38: /* ExprWithoutBlock: ExprWithBlock NOT_EQUAL ExprWithoutBlock  */
#line 159 "grammar_with_code.y"
                                                                                                        { (yyval.expr) = OperatorExpr(not_equal, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1884 "grammar_with_code.tab.c"
    break;

  case 39: /* ExprWithoutBlock: ExprWithBlock NOT_EQUAL ExprWithBlock  */
#line 160 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(not_equal, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1890 "grammar_with_code.tab.c"
    break;

  case 40: /* ExprWithoutBlock: ExprWithoutBlock '>' ExprWithoutBlock  */
#line 161 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(greater, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1896 "grammar_with_code.tab.c"
    break;

  case 41: /* ExprWithoutBlock: ExprWithoutBlock '>' ExprWithBlock  */
#line 162 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(greater, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1902 "grammar_with_code.tab.c"
    break;

  case 42: /* ExprWithoutBlock: ExprWithBlock '>' ExprWithoutBlock  */
#line 163 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(greater, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1908 "grammar_with_code.tab.c"
    break;

  case 43: /* ExprWithoutBlock: ExprWithBlock '>' ExprWithBlock  */
#line 164 "grammar_with_code.y"
                                                                                                        { (yyval.expr) = OperatorExpr(greater, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1914 "grammar_with_code.tab.c"
    break;

  case 44: /* ExprWithoutBlock: ExprWithoutBlock '<' ExprWithoutBlock  */
#line 165 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(less, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1920 "grammar_with_code.tab.c"
    break;

  case 45: /* ExprWithoutBlock: ExprWithoutBlock '<' ExprWithBlock  */
#line 166 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(less, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1926 "grammar_with_code.tab.c"
    break;

  case 46: /* ExprWithoutBlock: ExprWithBlock '<' ExprWithoutBlock  */
#line 167 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(less, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1932 "grammar_with_code.tab.c"
    break;

  case 47: /* ExprWithoutBlock: ExprWithBlock '<' ExprWithBlock  */
#line 168 "grammar_with_code.y"
                                                                                                        { (yyval.expr) = OperatorExpr(less, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1938 "grammar_with_code.tab.c"
    break;

  case 48: /* ExprWithoutBlock: ExprWithoutBlock GREATER_EQUAL ExprWithoutBlock  */
#line 169 "grammar_with_code.y"
                                                                                                        { (yyval.expr) = OperatorExpr(greater_equal, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1944 "grammar_with_code.tab.c"
    break;

  case 49: /* ExprWithoutBlock: ExprWithoutBlock GREATER_EQUAL ExprWithBlock  */
#line 170 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(greater_equal, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1950 "grammar_with_code.tab.c"
    break;

  case 50: /* ExprWithoutBlock: ExprWithBlock GREATER_EQUAL ExprWithoutBlock  */
#line 171 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(greater_equal, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1956 "grammar_with_code.tab.c"
    break;

  case 51: /* ExprWithoutBlock: ExprWithBlock GREATER_EQUAL ExprWithBlock  */
#line 172 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(greater_equal, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1962 "grammar_with_code.tab.c"
    break;

  case 52: /* ExprWithoutBlock: ExprWithoutBlock LESS_EQUAL ExprWithoutBlock  */
#line 173 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(less_equal, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1968 "grammar_with_code.tab.c"
    break;

  case 53: /* ExprWithoutBlock: ExprWithoutBlock LESS_EQUAL ExprWithBlock  */
#line 174 "grammar_with_code.y"
                                                                                                                { (yyval.expr) = OperatorExpr(less_equal, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1974 "grammar_with_code.tab.c"
    break;

  case 54: /* ExprWithoutBlock: ExprWithBlock LESS_EQUAL ExprWithoutBlock  */
#line 175 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(less_equal, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1980 "grammar_with_code.tab.c"
    break;

  case 55: /* ExprWithoutBlock: ExprWithBlock LESS_EQUAL ExprWithBlock  */
#line 176 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(less_equal, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1986 "grammar_with_code.tab.c"
    break;

  case 56: /* ExprWithoutBlock: ExprWithBlock '?'  */
#line 177 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(qt, (yyvsp[-1].expr), 0); }
#line 1992 "grammar_with_code.tab.c"
    break;

  case 57: /* ExprWithoutBlock: ExprWithoutBlock '?'  */
#line 178 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(qt, (yyvsp[-1].expr), 0); }
#line 1998 "grammar_with_code.tab.c"
    break;

  case 58: /* ExprWithoutBlock: '-' ExprWithBlock  */
#line 179 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(uminus, (yyvsp[0].expr), 0); }
#line 2004 "grammar_with_code.tab.c"
    break;

  case 59: /* ExprWithoutBlock: '-' ExprWithoutBlock  */
#line 180 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(uminus, (yyvsp[0].expr), 0); }
#line 2010 "grammar_with_code.tab.c"
    break;

  case 60: /* ExprWithoutBlock: '!' ExprWithBlock  */
#line 181 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(neg, (yyvsp[0].expr), 0); }
#line 2016 "grammar_with_code.tab.c"
    break;

  case 61: /* ExprWithoutBlock: '!' ExprWithoutBlock  */
#line 182 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(neg, (yyvsp[0].expr), 0); }
#line 2022 "grammar_with_code.tab.c"
    break;

  case 62: /* ExprWithoutBlock: ExprWithBlock OR ExprWithBlock  */
#line 183 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(or, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2028 "grammar_with_code.tab.c"
    break;

  case 63: /* ExprWithoutBlock: ExprWithoutBlock OR ExprWithBlock  */
#line 184 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(or, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2034 "grammar_with_code.tab.c"
    break;

  case 64: /* ExprWithoutBlock: ExprWithBlock OR ExprWithoutBlock  */
#line 185 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(or, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2040 "grammar_with_code.tab.c"
    break;

  case 65: /* ExprWithoutBlock: ExprWithoutBlock OR ExprWithoutBlock  */
#line 186 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(or, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2046 "grammar_with_code.tab.c"
    break;

  case 66: /* ExprWithoutBlock: ExprWithBlock AND ExprWithBlock  */
#line 187 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(and, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2052 "grammar_with_code.tab.c"
    break;

  case 67: /* ExprWithoutBlock: ExprWithoutBlock AND ExprWithBlock  */
#line 188 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(and, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2058 "grammar_with_code.tab.c"
    break;

  case 68: /* ExprWithoutBlock: ExprWithBlock AND ExprWithoutBlock  */
#line 189 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(and, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2064 "grammar_with_code.tab.c"
    break;

  case 69: /* ExprWithoutBlock: ExprWithoutBlock AND ExprWithoutBlock  */
#line 190 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(and, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2070 "grammar_with_code.tab.c"
    break;

  case 70: /* ExprWithoutBlock: ExprWithBlock '=' ExprWithBlock  */
#line 191 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(asgn, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2076 "grammar_with_code.tab.c"
    break;

  case 71: /* ExprWithoutBlock: ExprWithoutBlock '=' ExprWithBlock  */
#line 192 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(asgn, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2082 "grammar_with_code.tab.c"
    break;

  case 72: /* ExprWithoutBlock: ExprWithBlock '=' ExprWithoutBlock  */
#line 193 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(asgn, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2088 "grammar_with_code.tab.c"
    break;

  case 73: /* ExprWithoutBlock: ExprWithoutBlock '=' ExprWithoutBlock  */
#line 194 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(asgn, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2094 "grammar_with_code.tab.c"
    break;

  case 74: /* ExprWithoutBlock: BREAK ExprWithBlock  */
#line 195 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(break_expr, (yyvsp[0].expr), 0); }
#line 2100 "grammar_with_code.tab.c"
    break;

  case 75: /* ExprWithoutBlock: BREAK ExprWithoutBlock  */
#line 196 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(break_expr, (yyvsp[0].expr), 0); }
#line 2106 "grammar_with_code.tab.c"
    break;

  case 76: /* ExprWithoutBlock: BREAK  */
#line 197 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(break_expr, 0, 0); }
#line 2112 "grammar_with_code.tab.c"
    break;

  case 77: /* ExprWithoutBlock: CONTINUE  */
#line 198 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(continue_expr, 0, 0); }
#line 2118 "grammar_with_code.tab.c"
    break;

  case 78: /* ExprWithoutBlock: '(' ExprWithBlock ')'  */
#line 199 "grammar_with_code.y"
                                                                        { (yyval.expr) = (yyvsp[-1].expr); }
#line 2124 "grammar_with_code.tab.c"
    break;

  case 79: /* ExprWithoutBlock: '(' ExprWithoutBlock ')'  */
#line 200 "grammar_with_code.y"
                                                                        { (yyval.expr) = (yyvsp[-1].expr); }
#line 2130 "grammar_with_code.tab.c"
    break;

  case 80: /* ExprWithoutBlock: '[' ExprList_final ']'  */
#line 201 "grammar_with_code.y"
                                                                        { (yyval.expr) = ArrExprFromList((yyvsp[-1].expr_list)); }
#line 2136 "grammar_with_code.tab.c"
    break;

  case 81: /* ExprWithoutBlock: '[' ExprWithBlock ';' ExprWithBlock ']'  */
#line 202 "grammar_with_code.y"
                                                                        { (yyval.expr) = ArrExprAutoFill((yyvsp[-3].expr), (yyvsp[-1].expr)); }
#line 2142 "grammar_with_code.tab.c"
    break;

  case 82: /* ExprWithoutBlock: '[' ExprWithoutBlock ';' ExprWithBlock ']'  */
#line 203 "grammar_with_code.y"
                                                                        { (yyval.expr) = ArrExprAutoFill((yyvsp[-3].expr), (yyvsp[-1].expr)); }
#line 2148 "grammar_with_code.tab.c"
    break;

  case 83: /* ExprWithoutBlock: '[' ExprWithBlock ';' ExprWithoutBlock ']'  */
#line 204 "grammar_with_code.y"
                                                                        { (yyval.expr) = ArrExprAutoFill((yyvsp[-3].expr), (yyvsp[-1].expr)); }
#line 2154 "grammar_with_code.tab.c"
    break;

  case 84: /* ExprWithoutBlock: '[' ExprWithoutBlock ';' ExprWithoutBlock ']'  */
#line 205 "grammar_with_code.y"
                                                                        { (yyval.expr) = ArrExprAutoFill((yyvsp[-3].expr), (yyvsp[-1].expr)); }
#line 2160 "grammar_with_code.tab.c"
    break;

  case 85: /* ExprWithoutBlock: ExprWithBlock '[' ExprWithBlock ']'  */
#line 206 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(index_expr, (yyvsp[-3].expr), (yyvsp[-1].expr)); }
#line 2166 "grammar_with_code.tab.c"
    break;

  case 86: /* ExprWithoutBlock: ExprWithoutBlock '[' ExprWithBlock ']'  */
#line 207 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(index_expr, (yyvsp[-3].expr), (yyvsp[-1].expr)); }
#line 2172 "grammar_with_code.tab.c"
    break;

  case 87: /* ExprWithoutBlock: ExprWithBlock '[' ExprWithoutBlock ']'  */
#line 208 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(index_expr, (yyvsp[-3].expr), (yyvsp[-1].expr)); }
#line 2178 "grammar_with_code.tab.c"
    break;

  case 88: /* ExprWithoutBlock: ExprWithoutBlock '[' ExprWithoutBlock ']'  */
#line 209 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(index_expr, (yyvsp[-3].expr), (yyvsp[-1].expr)); }
#line 2184 "grammar_with_code.tab.c"
    break;

  case 89: /* ExprWithoutBlock: ID '(' ExprList_final ')'  */
#line 210 "grammar_with_code.y"
                                                                        { (yyval.expr) = CallAccessExpr(call_expr, (yyvsp[-3].string_const), 0, (yyvsp[-1].expr_list)); }
#line 2190 "grammar_with_code.tab.c"
    break;

  case 90: /* ExprWithoutBlock: ExprWithBlock '.' ID '(' ExprList_final ')'  */
#line 211 "grammar_with_code.y"
                                                                        { (yyval.expr) = CallAccessExpr(method_expr, (yyvsp[-3].string_const), (yyvsp[-5].expr), (yyvsp[-1].expr_list)); }
#line 2196 "grammar_with_code.tab.c"
    break;

  case 91: /* ExprWithoutBlock: ExprWithoutBlock '.' ID '(' ExprList_final ')'  */
#line 212 "grammar_with_code.y"
                                                                        { (yyval.expr) = CallAccessExpr(method_expr, (yyvsp[-3].string_const), (yyvsp[-5].expr), (yyvsp[-1].expr_list)); }
#line 2202 "grammar_with_code.tab.c"
    break;

  case 92: /* ExprWithoutBlock: ID ':' ':' ID '(' ExprList_final ')'  */
#line 213 "grammar_with_code.y"
                                                                    { (yyval.expr) = StaticMethodExpr(static_method, (yyvsp[-3].string_const), (yyvsp[-6].string_const), (yyvsp[-1].expr_list)); }
#line 2208 "grammar_with_code.tab.c"
    break;

  case 93: /* ExprWithoutBlock: ExprWithBlock '.' ID  */
#line 214 "grammar_with_code.y"
                                                                        { (yyval.expr) = CallAccessExpr(field_access_expr, (yyvsp[0].string_const), (yyvsp[-2].expr), 0); }
#line 2214 "grammar_with_code.tab.c"
    break;

  case 94: /* ExprWithoutBlock: ExprWithoutBlock '.' ID  */
#line 215 "grammar_with_code.y"
                                                                        { (yyval.expr) = CallAccessExpr(field_access_expr, (yyvsp[0].string_const), (yyvsp[-2].expr), 0); }
#line 2220 "grammar_with_code.tab.c"
    break;

  case 95: /* ExprWithoutBlock: ExprWithBlock RANGE ExprWithBlock  */
#line 216 "grammar_with_code.y"
                                                                        { (yyval.expr) = RangeExpr(range_expr, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2226 "grammar_with_code.tab.c"
    break;

  case 96: /* ExprWithoutBlock: ExprWithoutBlock RANGE ExprWithBlock  */
#line 217 "grammar_with_code.y"
                                                                        { (yyval.expr) = RangeExpr(range_expr, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2232 "grammar_with_code.tab.c"
    break;

  case 97: /* ExprWithoutBlock: ExprWithBlock RANGE ExprWithoutBlock  */
#line 218 "grammar_with_code.y"
                                                                        { (yyval.expr) = RangeExpr(range_expr, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2238 "grammar_with_code.tab.c"
    break;

  case 98: /* ExprWithoutBlock: ExprWithoutBlock RANGE ExprWithoutBlock  */
#line 219 "grammar_with_code.y"
                                                                        { (yyval.expr) = RangeExpr(range_expr, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2244 "grammar_with_code.tab.c"
    break;

  case 99: /* ExprWithoutBlock: ExprWithBlock RANGE  */
#line 220 "grammar_with_code.y"
                                                                        { (yyval.expr) = RangeExpr(range_left, (yyvsp[-1].expr), 0); }
#line 2250 "grammar_with_code.tab.c"
    break;

  case 100: /* ExprWithoutBlock: ExprWithoutBlock RANGE  */
#line 221 "grammar_with_code.y"
                                                                        { (yyval.expr) = RangeExpr(range_left, (yyvsp[-1].expr), 0); }
#line 2256 "grammar_with_code.tab.c"
    break;

  case 101: /* ExprWithoutBlock: RANGE ExprWithBlock  */
#line 222 "grammar_with_code.y"
                                                                        { (yyval.expr) = RangeExpr(range_right, (yyvsp[0].expr), 0); }
#line 2262 "grammar_with_code.tab.c"
    break;

  case 102: /* ExprWithoutBlock: RANGE ExprWithoutBlock  */
#line 223 "grammar_with_code.y"
                                                                        { (yyval.expr) = RangeExpr(range_right, (yyvsp[0].expr), 0); }
#line 2268 "grammar_with_code.tab.c"
    break;

  case 103: /* ExprWithoutBlock: RANGE  */
#line 224 "grammar_with_code.y"
                                                                        { (yyval.expr) = RangeExpr(range_right, 0, 0); }
#line 2274 "grammar_with_code.tab.c"
    break;

  case 104: /* ExprWithoutBlock: ExprWithBlock RANGE_IN ExprWithBlock  */
#line 225 "grammar_with_code.y"
                                                                        { (yyval.expr) = RangeExpr(range_in_expr, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2280 "grammar_with_code.tab.c"
    break;

  case 105: /* ExprWithoutBlock: ExprWithoutBlock RANGE_IN ExprWithBlock  */
#line 226 "grammar_with_code.y"
                                                                        { (yyval.expr) = RangeExpr(range_in_expr, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2286 "grammar_with_code.tab.c"
    break;

  case 106: /* ExprWithoutBlock: ExprWithBlock RANGE_IN ExprWithoutBlock  */
#line 227 "grammar_with_code.y"
                                                                        { (yyval.expr) = RangeExpr(range_in_expr, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2292 "grammar_with_code.tab.c"
    break;

  case 107: /* ExprWithoutBlock: ExprWithoutBlock RANGE_IN ExprWithoutBlock  */
#line 228 "grammar_with_code.y"
                                                                        { (yyval.expr) = RangeExpr(range_in_expr, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2298 "grammar_with_code.tab.c"
    break;

  case 108: /* ExprWithoutBlock: RANGE_IN ExprWithBlock  */
#line 229 "grammar_with_code.y"
                                                                        { (yyval.expr) = RangeExpr(range_in_right, (yyvsp[0].expr), 0); }
#line 2304 "grammar_with_code.tab.c"
    break;

  case 109: /* ExprWithoutBlock: RANGE_IN ExprWithoutBlock  */
#line 230 "grammar_with_code.y"
                                                                        { (yyval.expr) = RangeExpr(range_in_right, (yyvsp[0].expr), 0); }
#line 2310 "grammar_with_code.tab.c"
    break;

  case 110: /* ExprWithoutBlock: RETURN ExprWithBlock  */
#line 231 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(return_expr, (yyvsp[0].expr), 0); }
#line 2316 "grammar_with_code.tab.c"
    break;

  case 111: /* ExprWithoutBlock: RETURN ExprWithoutBlock  */
#line 232 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(return_expr, (yyvsp[0].expr), 0); }
#line 2322 "grammar_with_code.tab.c"
    break;

  case 112: /* ExprWithoutBlock: RETURN  */
#line 233 "grammar_with_code.y"
                                                                        { (yyval.expr) = OperatorExpr(return_expr, 0, 0); }
#line 2328 "grammar_with_code.tab.c"
    break;

  case 113: /* ExprWithoutBlock: ID  */
#line 234 "grammar_with_code.y"
                                                                        { (yyval.expr) = CallAccessExpr(id, (yyvsp[0].string_const), 0, 0); }
#line 2334 "grammar_with_code.tab.c"
    break;

  case 114: /* ExprWithoutBlock: SELF  */
#line 235 "grammar_with_code.y"
                                                { (yyval.expr) = CallAccessExpr(self_expr, "self", 0, 0); }
#line 2340 "grammar_with_code.tab.c"
    break;

  case 115: /* ExprWithoutBlock: ID '{' ExprList_final '}'  */
#line 236 "grammar_with_code.y"
                                                    { (yyval.expr) = StructExpr((yyvsp[-3].string_const), (yyvsp[-1].expr_list)); }
#line 2346 "grammar_with_code.tab.c"
    break;

  case 116: /* ExprWithoutBlock: StructExprField  */
#line 237 "grammar_with_code.y"
                                                             { (yyval.expr) = (yyvsp[0].expr) ;}
#line 2352 "grammar_with_code.tab.c"
    break;

  case 117: /* StructExprField: ID ':' ExprWithBlock  */
#line 241 "grammar_with_code.y"
                                                { (yyval.expr) = ExprFromStructField((yyvsp[-2].string_const), (yyvsp[0].expr)); }
#line 2358 "grammar_with_code.tab.c"
    break;

  case 118: /* StructExprField: ID ':' ExprWithoutBlock  */
#line 242 "grammar_with_code.y"
                                                { (yyval.expr) = ExprFromStructField((yyvsp[-2].string_const), (yyvsp[0].expr)); }
#line 2364 "grammar_with_code.tab.c"
    break;

  case 119: /* ExprWithBlock: LOOP BlockExpr  */
#line 246 "grammar_with_code.y"
                                                                        { (yyval.expr) = CycleExpr(loop_expr, 0, (yyvsp[0].expr), 0); }
#line 2370 "grammar_with_code.tab.c"
    break;

  case 120: /* ExprWithBlock: WHILE '(' ExprWithBlock ')' BlockExpr  */
#line 247 "grammar_with_code.y"
                                                                                { (yyval.expr) = CycleExpr(loop_while, (yyvsp[-2].expr), (yyvsp[0].expr), 0); }
#line 2376 "grammar_with_code.tab.c"
    break;

  case 121: /* ExprWithBlock: WHILE '(' ExprWithoutBlock ')' BlockExpr  */
#line 248 "grammar_with_code.y"
                                                                                { (yyval.expr) = CycleExpr(loop_while, (yyvsp[-2].expr), (yyvsp[0].expr), 0); }
#line 2382 "grammar_with_code.tab.c"
    break;

  case 122: /* ExprWithBlock: FOR '(' ID IN ExprWithBlock ')' BlockExpr  */
#line 249 "grammar_with_code.y"
                                                                                { (yyval.expr) = CycleExpr(loop_for, (yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-4].string_const)); }
#line 2388 "grammar_with_code.tab.c"
    break;

  case 123: /* ExprWithBlock: FOR '(' ID IN ExprWithoutBlock ')' BlockExpr  */
#line 250 "grammar_with_code.y"
                                                                                { (yyval.expr) = CycleExpr(loop_for, (yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-4].string_const)); }
#line 2394 "grammar_with_code.tab.c"
    break;

  case 124: /* ExprWithBlock: IF '(' ExprWithBlock ')' BlockExpr  */
#line 251 "grammar_with_code.y"
                                                                                { (yyval.expr) = IfExpr((yyvsp[-2].expr), (yyvsp[0].expr), 0); }
#line 2400 "grammar_with_code.tab.c"
    break;

  case 125: /* ExprWithBlock: IF '(' ExprWithoutBlock ')' BlockExpr  */
#line 252 "grammar_with_code.y"
                                                                                { (yyval.expr) = IfExpr((yyvsp[-2].expr), (yyvsp[0].expr), 0); }
#line 2406 "grammar_with_code.tab.c"
    break;

  case 126: /* ExprWithBlock: IF '(' ExprWithBlock ')' BlockExpr ELSE BlockExpr  */
#line 253 "grammar_with_code.y"
                                                                                { (yyval.expr) = IfExpr((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2412 "grammar_with_code.tab.c"
    break;

  case 127: /* ExprWithBlock: IF '(' ExprWithoutBlock ')' BlockExpr ELSE BlockExpr  */
#line 254 "grammar_with_code.y"
                                                                                { (yyval.expr) = IfExpr((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2418 "grammar_with_code.tab.c"
    break;

  case 128: /* BlockExpr: '{' StmtList '}'  */
#line 257 "grammar_with_code.y"
                                                                        { (yyval.expr) = BlockExpr((yyvsp[-1].stmt_list)); }
#line 2424 "grammar_with_code.tab.c"
    break;

  case 129: /* BlockExpr: '{' '}'  */
#line 258 "grammar_with_code.y"
                                                                        { (yyval.expr) = BlockExpr(0); }
#line 2430 "grammar_with_code.tab.c"
    break;

  case 130: /* StmtListSupreme: StmtDecl  */
#line 263 "grammar_with_code.y"
                                            { (yyval.stmt_list) = StmtListNode((yyvsp[0].stmt_)); }
#line 2436 "grammar_with_code.tab.c"
    break;

  case 131: /* StmtListSupreme: StmtListSupreme StmtDecl  */
#line 264 "grammar_with_code.y"
                                            { (yyval.stmt_list) = StmtListAdd((yyvsp[-1].stmt_list), (yyvsp[0].stmt_)); }
#line 2442 "grammar_with_code.tab.c"
    break;

  case 132: /* StmtList: Stmt  */
#line 267 "grammar_with_code.y"
                                                                            { (yyval.stmt_list) = StmtListNode((yyvsp[0].stmt_)); }
#line 2448 "grammar_with_code.tab.c"
    break;

  case 133: /* StmtList: StmtList Stmt  */
#line 268 "grammar_with_code.y"
                                                                        { (yyval.stmt_list) = StmtListAdd((yyvsp[-1].stmt_list), (yyvsp[0].stmt_)); }
#line 2454 "grammar_with_code.tab.c"
    break;

  case 134: /* Stmt: ';'  */
#line 271 "grammar_with_code.y"
                                                                        { (yyval.stmt_) = StmtNode(semicolon, 0, 0, 0); }
#line 2460 "grammar_with_code.tab.c"
    break;

  case 135: /* Stmt: ExprWithoutBlock ';'  */
#line 272 "grammar_with_code.y"
                                                                        { (yyval.stmt_) = StmtNode(expr, (yyvsp[-1].expr), 0, 0); }
#line 2466 "grammar_with_code.tab.c"
    break;

  case 136: /* Stmt: ExprWithBlock ';'  */
#line 273 "grammar_with_code.y"
                                                                        { (yyval.stmt_) = StmtNode(expr, (yyvsp[-1].expr), 0, 0); }
#line 2472 "grammar_with_code.tab.c"
    break;

  case 137: /* Stmt: LetStmt  */
#line 274 "grammar_with_code.y"
                                                                        { (yyval.stmt_) = StmtNode(let, 0, 0, (yyvsp[0].let_stmt)); }
#line 2478 "grammar_with_code.tab.c"
    break;

  case 138: /* StmtDecl: DeclarationStmt  */
#line 277 "grammar_with_code.y"
                                                                { (yyval.stmt_) = StmtNode(declaration, 0, (yyvsp[0].decl_stmt), 0); }
#line 2484 "grammar_with_code.tab.c"
    break;

  case 139: /* LetStmt: LET ID ':' Type '=' ExprWithBlock ';'  */
#line 281 "grammar_with_code.y"
                                                                        { (yyval.let_stmt) = LetStmt((yyvsp[-5].string_const), (yyvsp[-3].type_), notMut, (yyvsp[-1].expr)); }
#line 2490 "grammar_with_code.tab.c"
    break;

  case 140: /* LetStmt: LET ID ':' Type '=' ExprWithoutBlock ';'  */
#line 282 "grammar_with_code.y"
                                                                        { (yyval.let_stmt) = LetStmt((yyvsp[-5].string_const), (yyvsp[-3].type_), notMut, (yyvsp[-1].expr)); }
#line 2496 "grammar_with_code.tab.c"
    break;

  case 141: /* LetStmt: LET ID '=' ExprWithBlock ';'  */
#line 283 "grammar_with_code.y"
                                                                        { (yyval.let_stmt) = LetStmt((yyvsp[-3].string_const), 0, notMut, (yyvsp[-1].expr)); }
#line 2502 "grammar_with_code.tab.c"
    break;

  case 142: /* LetStmt: LET ID '=' ExprWithoutBlock ';'  */
#line 284 "grammar_with_code.y"
                                                                        { (yyval.let_stmt) = LetStmt((yyvsp[-3].string_const), 0, notMut, (yyvsp[-1].expr)); }
#line 2508 "grammar_with_code.tab.c"
    break;

  case 143: /* LetStmt: LET MUT ID ':' Type '=' ExprWithBlock ';'  */
#line 285 "grammar_with_code.y"
                                                                        { (yyval.let_stmt) = LetStmt((yyvsp[-5].string_const), (yyvsp[-3].type_), mut, (yyvsp[-1].expr)); }
#line 2514 "grammar_with_code.tab.c"
    break;

  case 144: /* LetStmt: LET MUT ID ':' Type '=' ExprWithoutBlock ';'  */
#line 286 "grammar_with_code.y"
                                                                        { (yyval.let_stmt) = LetStmt((yyvsp[-5].string_const), (yyvsp[-3].type_), mut, (yyvsp[-1].expr)); }
#line 2520 "grammar_with_code.tab.c"
    break;

  case 145: /* LetStmt: LET MUT ID '=' ExprWithBlock ';'  */
#line 287 "grammar_with_code.y"
                                                                        { (yyval.let_stmt) = LetStmt((yyvsp[-3].string_const), 0, mut, (yyvsp[-1].expr)); }
#line 2526 "grammar_with_code.tab.c"
    break;

  case 146: /* LetStmt: LET MUT ID '=' ExprWithoutBlock ';'  */
#line 288 "grammar_with_code.y"
                                                                        { (yyval.let_stmt) = LetStmt((yyvsp[-3].string_const), 0, mut, (yyvsp[-1].expr)); }
#line 2532 "grammar_with_code.tab.c"
    break;

  case 147: /* LetStmt: LET MUT ID ':' Type ';'  */
#line 289 "grammar_with_code.y"
                                                                        { (yyval.let_stmt) = LetStmt((yyvsp[-3].string_const), (yyvsp[-1].type_), mut, 0); }
#line 2538 "grammar_with_code.tab.c"
    break;

  case 148: /* LetStmt: LET MUT ID ';'  */
#line 290 "grammar_with_code.y"
                                                                        { (yyval.let_stmt) = LetStmt((yyvsp[-1].string_const), 0, mut, 0); }
#line 2544 "grammar_with_code.tab.c"
    break;

  case 149: /* LetStmt: LET ID ':' Type ';'  */
#line 291 "grammar_with_code.y"
                                                                        { (yyval.let_stmt) = LetStmt((yyvsp[-3].string_const), (yyvsp[-1].type_), notMut, 0); }
#line 2550 "grammar_with_code.tab.c"
    break;

  case 150: /* LetStmt: LET ID ';'  */
#line 292 "grammar_with_code.y"
                                                                        { (yyval.let_stmt) = LetStmt((yyvsp[-1].string_const), 0, notMut, 0); }
#line 2556 "grammar_with_code.tab.c"
    break;

  case 151: /* DeclarationStmt: Enum  */
#line 296 "grammar_with_code.y"
                                                                        { (yyval.decl_stmt) = DeclarationEnum(self, (yyvsp[0].enum_)); }
#line 2562 "grammar_with_code.tab.c"
    break;

  case 152: /* DeclarationStmt: Visibility Enum  */
#line 297 "grammar_with_code.y"
                                                                        { (yyval.decl_stmt) = DeclarationEnum((yyvsp[-1].vis), (yyvsp[0].enum_)); }
#line 2568 "grammar_with_code.tab.c"
    break;

  case 153: /* DeclarationStmt: FunctionWithBlock  */
#line 298 "grammar_with_code.y"
                                                                                { (yyval.decl_stmt) = DeclarationFunction(self, (yyvsp[0].function_)); }
#line 2574 "grammar_with_code.tab.c"
    break;

  case 154: /* DeclarationStmt: Visibility FunctionWithBlock  */
#line 299 "grammar_with_code.y"
                                                                                { (yyval.decl_stmt) = DeclarationFunction((yyvsp[-1].vis), (yyvsp[0].function_)); }
#line 2580 "grammar_with_code.tab.c"
    break;

  case 155: /* DeclarationStmt: FunctionWithoutBlock  */
#line 300 "grammar_with_code.y"
                                                                                { (yyval.decl_stmt) = DeclarationFunction(self, (yyvsp[0].function_)); }
#line 2586 "grammar_with_code.tab.c"
    break;

  case 156: /* DeclarationStmt: Visibility FunctionWithoutBlock  */
#line 301 "grammar_with_code.y"
                                                                                        { (yyval.decl_stmt) = DeclarationFunction((yyvsp[-1].vis), (yyvsp[0].function_)); }
#line 2592 "grammar_with_code.tab.c"
    break;

  case 157: /* DeclarationStmt: ConstStmt  */
#line 302 "grammar_with_code.y"
                                                                        { (yyval.decl_stmt) = DeclarationConst(self, (yyvsp[0].const_stmt)); }
#line 2598 "grammar_with_code.tab.c"
    break;

  case 158: /* DeclarationStmt: Visibility ConstStmt  */
#line 303 "grammar_with_code.y"
                                                                        { (yyval.decl_stmt) = DeclarationConst((yyvsp[-1].vis), (yyvsp[0].const_stmt)); }
#line 2604 "grammar_with_code.tab.c"
    break;

  case 159: /* DeclarationStmt: Struct  */
#line 304 "grammar_with_code.y"
                                                                        { (yyval.decl_stmt) = DeclarationStruct(self, (yyvsp[0].struct_)); }
#line 2610 "grammar_with_code.tab.c"
    break;

  case 160: /* DeclarationStmt: Visibility Struct  */
#line 305 "grammar_with_code.y"
                                                                        { (yyval.decl_stmt) = DeclarationStruct((yyvsp[-1].vis), (yyvsp[0].struct_)); }
#line 2616 "grammar_with_code.tab.c"
    break;

  case 161: /* DeclarationStmt: Trait  */
#line 306 "grammar_with_code.y"
                                                                        { (yyval.decl_stmt) = DeclarationTrait(self, (yyvsp[0].trait_)); }
#line 2622 "grammar_with_code.tab.c"
    break;

  case 162: /* DeclarationStmt: Visibility Trait  */
#line 307 "grammar_with_code.y"
                                                                        { (yyval.decl_stmt) = DeclarationTrait((yyvsp[-1].vis), (yyvsp[0].trait_)); }
#line 2628 "grammar_with_code.tab.c"
    break;

  case 163: /* DeclarationStmt: Impl  */
#line 308 "grammar_with_code.y"
                                                                        { (yyval.decl_stmt) = DeclarationImpl(self, (yyvsp[0].impl_)); }
#line 2634 "grammar_with_code.tab.c"
    break;

  case 164: /* DeclarationStmt: Visibility Impl  */
#line 309 "grammar_with_code.y"
                                                                        { (yyval.decl_stmt) = DeclarationImpl((yyvsp[-1].vis), (yyvsp[0].impl_)); }
#line 2640 "grammar_with_code.tab.c"
    break;

  case 165: /* Enum: ENUM ID '{' EnumItems_final '}'  */
#line 313 "grammar_with_code.y"
                                                                        { (yyval.enum_) = EnumNode((yyvsp[-3].string_const), (yyvsp[-1].enum_items)); }
#line 2646 "grammar_with_code.tab.c"
    break;

  case 166: /* EnumItems_final: %empty  */
#line 316 "grammar_with_code.y"
                                                                        { (yyval.enum_items) = 0; }
#line 2652 "grammar_with_code.tab.c"
    break;

  case 167: /* EnumItems_final: EnumItems  */
#line 317 "grammar_with_code.y"
                                                                        { (yyval.enum_items) = EnumListFinal((yyvsp[0].enum_items)); }
#line 2658 "grammar_with_code.tab.c"
    break;

  case 168: /* EnumItems_final: EnumItems ','  */
#line 318 "grammar_with_code.y"
                                                                { (yyval.enum_items) = EnumListFinal((yyvsp[-1].enum_items)); }
#line 2664 "grammar_with_code.tab.c"
    break;

  case 169: /* EnumItems: EnumItem  */
#line 321 "grammar_with_code.y"
                                                                        { (yyval.enum_items) = EnumListNode((yyvsp[0].enum_item)); }
#line 2670 "grammar_with_code.tab.c"
    break;

  case 170: /* EnumItems: EnumItems ',' EnumItem  */
#line 322 "grammar_with_code.y"
                                                                        { (yyval.enum_items) = EnumListAdd((yyvsp[-2].enum_items), (yyvsp[0].enum_item)); }
#line 2676 "grammar_with_code.tab.c"
    break;

  case 171: /* EnumItem: Visibility ID  */
#line 325 "grammar_with_code.y"
                                                                        { (yyval.enum_item) = EnumItemNode((yyvsp[0].string_const), (yyvsp[-1].vis), 0, 0); }
#line 2682 "grammar_with_code.tab.c"
    break;

  case 172: /* EnumItem: ID  */
#line 326 "grammar_with_code.y"
                                                                        { (yyval.enum_item) = EnumItemNode((yyvsp[0].string_const), 0, 0, 0); }
#line 2688 "grammar_with_code.tab.c"
    break;

  case 173: /* EnumItem: Visibility ID '=' ExprWithBlock  */
#line 327 "grammar_with_code.y"
                                                                        { (yyval.enum_item) = EnumItemNode((yyvsp[-2].string_const), (yyvsp[-3].vis), 0, (yyvsp[0].expr)); }
#line 2694 "grammar_with_code.tab.c"
    break;

  case 174: /* EnumItem: Visibility ID '=' ExprWithoutBlock  */
#line 328 "grammar_with_code.y"
                                                                        { (yyval.enum_item) = EnumItemNode((yyvsp[-2].string_const), (yyvsp[-3].vis), 0, (yyvsp[0].expr)); }
#line 2700 "grammar_with_code.tab.c"
    break;

  case 175: /* EnumItem: ID '=' ExprWithBlock  */
#line 329 "grammar_with_code.y"
                                                                        { (yyval.enum_item) = EnumItemNode((yyvsp[-2].string_const), 0, 0, (yyvsp[0].expr)); }
#line 2706 "grammar_with_code.tab.c"
    break;

  case 176: /* EnumItem: ID '=' ExprWithoutBlock  */
#line 330 "grammar_with_code.y"
                                                                        { (yyval.enum_item) = EnumItemNode((yyvsp[-2].string_const), 0, 0, (yyvsp[0].expr)); }
#line 2712 "grammar_with_code.tab.c"
    break;

  case 177: /* EnumItem: Visibility ID '{' StructFields_final '}'  */
#line 331 "grammar_with_code.y"
                                                                        { (yyval.enum_item) = EnumItemNode((yyvsp[-3].string_const), (yyvsp[-4].vis), (yyvsp[-1].struct_items), 0); }
#line 2718 "grammar_with_code.tab.c"
    break;

  case 178: /* EnumItem: ID '{' StructFields_final '}'  */
#line 332 "grammar_with_code.y"
                                                                        { (yyval.enum_item) = EnumItemNode((yyvsp[-3].string_const), 0, (yyvsp[-1].struct_items), 0); }
#line 2724 "grammar_with_code.tab.c"
    break;

  case 179: /* FunctionWithBlock: FN ID '(' FuncParamList_final ')' RIGHT_ARROW Type BlockExpr  */
#line 336 "grammar_with_code.y"
                                                                                { (yyval.function_) = FunctionNode((yyvsp[-6].string_const), (yyvsp[-1].type_), (yyvsp[-4].function_params), (yyvsp[0].expr)); }
#line 2730 "grammar_with_code.tab.c"
    break;

  case 180: /* FunctionWithBlock: FN ID '(' FuncParamList_final ')' BlockExpr  */
#line 337 "grammar_with_code.y"
                                                                                        { (yyval.function_) = FunctionNode((yyvsp[-4].string_const), 0, (yyvsp[-2].function_params), (yyvsp[0].expr)); }
#line 2736 "grammar_with_code.tab.c"
    break;

  case 181: /* FunctionWithoutBlock: FN ID '(' FuncParamList_final ')' RIGHT_ARROW Type ';'  */
#line 340 "grammar_with_code.y"
                                                                                { (yyval.function_) = FunctionNode((yyvsp[-6].string_const), (yyvsp[-1].type_), (yyvsp[-4].function_params), 0); }
#line 2742 "grammar_with_code.tab.c"
    break;

  case 182: /* FunctionWithoutBlock: FN ID '(' FuncParamList_final ')' ';'  */
#line 341 "grammar_with_code.y"
                                                                                                { (yyval.function_) = FunctionNode((yyvsp[-4].string_const), 0, (yyvsp[-2].function_params), 0); }
#line 2748 "grammar_with_code.tab.c"
    break;

  case 183: /* FuncParamList_final: %empty  */
#line 344 "grammar_with_code.y"
                                                                                { (yyval.function_params) = FunctionParamsFinal(associated, 0); }
#line 2754 "grammar_with_code.tab.c"
    break;

  case 184: /* FuncParamList_final: SELF_PARAM  */
#line 345 "grammar_with_code.y"
                                                            { (yyval.function_params) = FunctionParamsFinal(method_self, 0); }
#line 2760 "grammar_with_code.tab.c"
    break;

  case 185: /* FuncParamList_final: SELF_PARAM ','  */
#line 346 "grammar_with_code.y"
                                                            { (yyval.function_params) = FunctionParamsFinal(method_self, 0); }
#line 2766 "grammar_with_code.tab.c"
    break;

  case 186: /* FuncParamList_final: MUT_SELF_PARAM  */
#line 347 "grammar_with_code.y"
                                                            { (yyval.function_params) = FunctionParamsFinal(method_mut_self, 0); }
#line 2772 "grammar_with_code.tab.c"
    break;

  case 187: /* FuncParamList_final: MUT_SELF_PARAM ','  */
#line 348 "grammar_with_code.y"
                                                            { (yyval.function_params) = FunctionParamsFinal(method_mut_self, 0); }
#line 2778 "grammar_with_code.tab.c"
    break;

  case 188: /* FuncParamList_final: FuncParamList  */
#line 349 "grammar_with_code.y"
                                                                                { (yyval.function_params) = FunctionParamsFinal(associated, (yyvsp[0].function_params)); }
#line 2784 "grammar_with_code.tab.c"
    break;

  case 189: /* FuncParamList_final: FuncParamList ','  */
#line 350 "grammar_with_code.y"
                                                                        { (yyval.function_params) = FunctionParamsFinal(associated, (yyvsp[-1].function_params)); }
#line 2790 "grammar_with_code.tab.c"
    break;

  case 190: /* FuncParamList_final: SELF_PARAM ',' FuncParamList  */
#line 351 "grammar_with_code.y"
                                                                    { (yyval.function_params) = FunctionParamsFinal(method_self, (yyvsp[0].function_params)); }
#line 2796 "grammar_with_code.tab.c"
    break;

  case 191: /* FuncParamList_final: SELF_PARAM ',' FuncParamList ','  */
#line 352 "grammar_with_code.y"
                                                            { (yyval.function_params) = FunctionParamsFinal(method_self, (yyvsp[-1].function_params)); }
#line 2802 "grammar_with_code.tab.c"
    break;

  case 192: /* FuncParamList_final: MUT_SELF_PARAM ',' FuncParamList  */
#line 353 "grammar_with_code.y"
                                                                { (yyval.function_params) = FunctionParamsFinal(method_mut_self, (yyvsp[0].function_params)); }
#line 2808 "grammar_with_code.tab.c"
    break;

  case 193: /* FuncParamList_final: MUT_SELF_PARAM ',' FuncParamList ','  */
#line 354 "grammar_with_code.y"
                                                                { (yyval.function_params) = FunctionParamsFinal(method_mut_self, (yyvsp[-1].function_params)); }
#line 2814 "grammar_with_code.tab.c"
    break;

  case 194: /* FuncParamList: FuncParam  */
#line 357 "grammar_with_code.y"
                                                                        { (yyval.function_params) = FunctionParamsNode((yyvsp[0].function_param)); }
#line 2820 "grammar_with_code.tab.c"
    break;

  case 195: /* FuncParamList: FuncParamList ',' FuncParam  */
#line 358 "grammar_with_code.y"
                                                                        { (yyval.function_params) = FunctionParamsAdd((yyvsp[-2].function_params), (yyvsp[0].function_param)); }
#line 2826 "grammar_with_code.tab.c"
    break;

  case 196: /* FuncParam: ID ':' Type  */
#line 361 "grammar_with_code.y"
                                                                        { (yyval.function_param) = FunctionParamNode((yyvsp[-2].string_const), (yyvsp[0].type_), notMut); }
#line 2832 "grammar_with_code.tab.c"
    break;

  case 197: /* FuncParam: MUT ID ':' Type  */
#line 362 "grammar_with_code.y"
                                                                        { (yyval.function_param) = FunctionParamNode((yyvsp[-2].string_const), (yyvsp[0].type_), mut); }
#line 2838 "grammar_with_code.tab.c"
    break;

  case 198: /* Struct: STRUCT ID '{' StructFields_final '}'  */
#line 367 "grammar_with_code.y"
                                                                        { (yyval.struct_) = StructNode((yyvsp[-3].string_const), (yyvsp[-1].struct_items)); }
#line 2844 "grammar_with_code.tab.c"
    break;

  case 199: /* Struct: STRUCT ID ';'  */
#line 368 "grammar_with_code.y"
                                                                        { (yyval.struct_) = StructNode((yyvsp[-1].string_const), 0); }
#line 2850 "grammar_with_code.tab.c"
    break;

  case 200: /* StructFields_final: %empty  */
#line 371 "grammar_with_code.y"
                                                                        { (yyval.struct_items) = StructListFinal(0); }
#line 2856 "grammar_with_code.tab.c"
    break;

  case 201: /* StructFields_final: StructFields  */
#line 372 "grammar_with_code.y"
                                                                        { (yyval.struct_items) = StructListFinal((yyvsp[0].struct_items)); }
#line 2862 "grammar_with_code.tab.c"
    break;

  case 202: /* StructFields_final: StructFields ','  */
#line 373 "grammar_with_code.y"
                                                                        { (yyval.struct_items) = StructListFinal((yyvsp[-1].struct_items)); }
#line 2868 "grammar_with_code.tab.c"
    break;

  case 203: /* StructFields: StructField  */
#line 376 "grammar_with_code.y"
                                                                        { (yyval.struct_items) = StructListNode((yyvsp[0].struct_item)); }
#line 2874 "grammar_with_code.tab.c"
    break;

  case 204: /* StructFields: StructFields ',' StructField  */
#line 377 "grammar_with_code.y"
                                                                        { (yyval.struct_items) = StructListAdd((yyvsp[-2].struct_items), (yyvsp[0].struct_item)); }
#line 2880 "grammar_with_code.tab.c"
    break;

  case 205: /* StructField: Visibility ID ':' Type  */
#line 380 "grammar_with_code.y"
                                                                        { (yyval.struct_item) = StructItemNode((yyvsp[-2].string_const), (yyvsp[0].type_), (yyvsp[-3].vis)); }
#line 2886 "grammar_with_code.tab.c"
    break;

  case 206: /* StructField: ID ':' Type  */
#line 381 "grammar_with_code.y"
                                                                        { (yyval.struct_item) = StructItemNode((yyvsp[-2].string_const), (yyvsp[0].type_), self); }
#line 2892 "grammar_with_code.tab.c"
    break;

  case 207: /* Impl: IMPL Type '{' AssociatedItemsImpl_final '}'  */
#line 385 "grammar_with_code.y"
                                                                                { (yyval.impl_) = ImplNode(inherent, (yyvsp[-3].type_), 0, (yyvsp[-1].associated_items)); }
#line 2898 "grammar_with_code.tab.c"
    break;

  case 208: /* Impl: IMPL ID FOR Type '{' AssociatedItemsImpl_final '}'  */
#line 386 "grammar_with_code.y"
                                                                                { (yyval.impl_) = ImplNode(trait, (yyvsp[-3].type_), (yyvsp[-5].string_const), (yyvsp[-1].associated_items)); }
#line 2904 "grammar_with_code.tab.c"
    break;

  case 209: /* AssociatedItemsImpl_final: %empty  */
#line 389 "grammar_with_code.y"
                                                                        { (yyval.associated_items) = AssociatedListFinal(0); }
#line 2910 "grammar_with_code.tab.c"
    break;

  case 210: /* AssociatedItemsImpl_final: AssociatedItemsImpl  */
#line 390 "grammar_with_code.y"
                                                                                { (yyval.associated_items) = AssociatedListFinal((yyvsp[0].associated_items)); }
#line 2916 "grammar_with_code.tab.c"
    break;

  case 211: /* AssociatedItemsImpl: AssociatedItemImpl  */
#line 393 "grammar_with_code.y"
                                                                                { (yyval.associated_items) = AssociatedList((yyvsp[0].associated_item)); }
#line 2922 "grammar_with_code.tab.c"
    break;

  case 212: /* AssociatedItemsImpl: AssociatedItemsImpl AssociatedItemImpl  */
#line 394 "grammar_with_code.y"
                                                                                { (yyval.associated_items) = AssociatedListAdd((yyvsp[-1].associated_items), (yyvsp[0].associated_item)); }
#line 2928 "grammar_with_code.tab.c"
    break;

  case 213: /* AssociatedItemImpl: Visibility FunctionWithBlock  */
#line 397 "grammar_with_code.y"
                                                                                        { (yyval.associated_item) = AssociatedItemNode((yyvsp[-1].vis), (yyvsp[0].function_), 0); }
#line 2934 "grammar_with_code.tab.c"
    break;

  case 214: /* AssociatedItemImpl: FunctionWithBlock  */
#line 398 "grammar_with_code.y"
                                                                                { (yyval.associated_item) = AssociatedItemNode(0, (yyvsp[0].function_), 0); }
#line 2940 "grammar_with_code.tab.c"
    break;

  case 215: /* AssociatedItemImpl: Visibility ConstStmt  */
#line 399 "grammar_with_code.y"
                                                                                { (yyval.associated_item) = AssociatedItemNode((yyvsp[-1].vis), 0, (yyvsp[0].const_stmt)); }
#line 2946 "grammar_with_code.tab.c"
    break;

  case 216: /* AssociatedItemImpl: ConstStmt  */
#line 400 "grammar_with_code.y"
                                                                        { (yyval.associated_item) = AssociatedItemNode(0, 0, (yyvsp[0].const_stmt)); }
#line 2952 "grammar_with_code.tab.c"
    break;

  case 217: /* Trait: TRAIT ID '{' AssociatedItems_final '}'  */
#line 405 "grammar_with_code.y"
                                                                        { (yyval.trait_) = TraitNode((yyvsp[-3].string_const), (yyvsp[-1].associated_items)); }
#line 2958 "grammar_with_code.tab.c"
    break;

  case 218: /* AssociatedItems_final: %empty  */
#line 408 "grammar_with_code.y"
                                                                        { (yyval.associated_items) = AssociatedListFinal(0); }
#line 2964 "grammar_with_code.tab.c"
    break;

  case 219: /* AssociatedItems_final: AssociatedItems  */
#line 409 "grammar_with_code.y"
                                                                        { (yyval.associated_items) = AssociatedListFinal((yyvsp[0].associated_items)); }
#line 2970 "grammar_with_code.tab.c"
    break;

  case 220: /* AssociatedItems: AssociatedItem  */
#line 412 "grammar_with_code.y"
                                                                        { (yyval.associated_items) = AssociatedList((yyvsp[0].associated_item)); }
#line 2976 "grammar_with_code.tab.c"
    break;

  case 221: /* AssociatedItems: AssociatedItems AssociatedItem  */
#line 413 "grammar_with_code.y"
                                                                        { (yyval.associated_items) = AssociatedListAdd((yyvsp[-1].associated_items), (yyvsp[0].associated_item)); }
#line 2982 "grammar_with_code.tab.c"
    break;

  case 222: /* AssociatedItem: Visibility FunctionWithBlock  */
#line 416 "grammar_with_code.y"
                                                                                { (yyval.associated_item) = AssociatedItemNode((yyvsp[-1].vis), (yyvsp[0].function_), 0); }
#line 2988 "grammar_with_code.tab.c"
    break;

  case 223: /* AssociatedItem: FunctionWithBlock  */
#line 417 "grammar_with_code.y"
                                                                                { (yyval.associated_item) = AssociatedItemNode(0, (yyvsp[0].function_), 0); }
#line 2994 "grammar_with_code.tab.c"
    break;

  case 224: /* AssociatedItem: Visibility FunctionWithoutBlock  */
#line 418 "grammar_with_code.y"
                                                                                { (yyval.associated_item) = AssociatedItemNode((yyvsp[-1].vis), (yyvsp[0].function_), 0); }
#line 3000 "grammar_with_code.tab.c"
    break;

  case 225: /* AssociatedItem: FunctionWithoutBlock  */
#line 419 "grammar_with_code.y"
                                                                                { (yyval.associated_item) = AssociatedItemNode(0, (yyvsp[0].function_), 0); }
#line 3006 "grammar_with_code.tab.c"
    break;

  case 226: /* AssociatedItem: Visibility ConstStmt  */
#line 420 "grammar_with_code.y"
                                                                        { (yyval.associated_item) = AssociatedItemNode((yyvsp[-1].vis), 0, (yyvsp[0].const_stmt)); }
#line 3012 "grammar_with_code.tab.c"
    break;

  case 227: /* AssociatedItem: ConstStmt  */
#line 421 "grammar_with_code.y"
                                                                        { (yyval.associated_item) = AssociatedItemNode(0, 0, (yyvsp[0].const_stmt)); }
#line 3018 "grammar_with_code.tab.c"
    break;

  case 228: /* ConstStmt: CONST ID ':' Type ';'  */
#line 425 "grammar_with_code.y"
                                                                        { (yyval.const_stmt) = ConstStmt((yyvsp[-3].string_const), (yyvsp[-1].type_), 0); }
#line 3024 "grammar_with_code.tab.c"
    break;

  case 229: /* ConstStmt: CONST ID ':' Type '=' ExprWithBlock ';'  */
#line 426 "grammar_with_code.y"
                                                                        { (yyval.const_stmt) = ConstStmt((yyvsp[-5].string_const), (yyvsp[-3].type_), (yyvsp[-1].expr)); }
#line 3030 "grammar_with_code.tab.c"
    break;

  case 230: /* ConstStmt: CONST ID ':' Type '=' ExprWithoutBlock ';'  */
#line 427 "grammar_with_code.y"
                                                                        { (yyval.const_stmt) = ConstStmt((yyvsp[-5].string_const), (yyvsp[-3].type_), (yyvsp[-1].expr)); }
#line 3036 "grammar_with_code.tab.c"
    break;

  case 231: /* Type: INT  */
#line 431 "grammar_with_code.y"
                                                                        { (yyval.type_) = TypeFromLiteral(int_); }
#line 3042 "grammar_with_code.tab.c"
    break;

  case 232: /* Type: STRING  */
#line 432 "grammar_with_code.y"
                                                                { (yyval.type_) = TypeFromLiteral(string_); }
#line 3048 "grammar_with_code.tab.c"
    break;

  case 233: /* Type: CHAR  */
#line 433 "grammar_with_code.y"
                                                                        { (yyval.type_) = TypeFromLiteral(char_); }
#line 3054 "grammar_with_code.tab.c"
    break;

  case 234: /* Type: FLOAT  */
#line 434 "grammar_with_code.y"
                                                                        { (yyval.type_) = TypeFromLiteral(float_); }
#line 3060 "grammar_with_code.tab.c"
    break;

  case 235: /* Type: BOOL  */
#line 435 "grammar_with_code.y"
                                                                        { (yyval.type_) = TypeFromLiteral(bool_); }
#line 3066 "grammar_with_code.tab.c"
    break;

  case 236: /* Type: ID  */
#line 436 "grammar_with_code.y"
                                                                        { (yyval.type_) = TypeFromLiteral(id_); }
#line 3072 "grammar_with_code.tab.c"
    break;

  case 237: /* Type: '[' Type ';' ExprWithBlock ']'  */
#line 437 "grammar_with_code.y"
                                        { (yyval.type_) = TypeFromArray((yyvsp[-3].type_), (yyvsp[-1].expr));}
#line 3078 "grammar_with_code.tab.c"
    break;

  case 238: /* Type: '[' Type ';' ExprWithoutBlock ']'  */
#line 438 "grammar_with_code.y"
                                        { (yyval.type_) = TypeFromArray((yyvsp[-3].type_), (yyvsp[-1].expr));}
#line 3084 "grammar_with_code.tab.c"
    break;

  case 239: /* Visibility: PUB  */
#line 442 "grammar_with_code.y"
                                                                        { (yyval.vis) = pub; }
#line 3090 "grammar_with_code.tab.c"
    break;

  case 240: /* Visibility: PUB '(' CRATE ')'  */
#line 443 "grammar_with_code.y"
                                                                        { (yyval.vis) = crate; }
#line 3096 "grammar_with_code.tab.c"
    break;

  case 241: /* Visibility: PUB '(' SELF ')'  */
#line 444 "grammar_with_code.y"
                                                                        { (yyval.vis) = self; }
#line 3102 "grammar_with_code.tab.c"
    break;

  case 242: /* Visibility: PUB '(' SUPER ')'  */
#line 445 "grammar_with_code.y"
                                                                        { (yyval.vis) = super; }
#line 3108 "grammar_with_code.tab.c"
    break;


#line 3112 "grammar_with_code.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 447 "grammar_with_code.y"
