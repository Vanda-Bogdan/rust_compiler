/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_GRAMMAR_WITH_CODE_TAB_H_INCLUDED
# define YY_YY_GRAMMAR_WITH_CODE_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    FOR = 258,                     /* FOR  */
    LOOP = 259,                    /* LOOP  */
    IN = 260,                      /* IN  */
    IF = 261,                      /* IF  */
    ELSE = 262,                    /* ELSE  */
    WHILE = 263,                   /* WHILE  */
    LET = 264,                     /* LET  */
    MUT = 265,                     /* MUT  */
    FN = 266,                      /* FN  */
    CONTINUE = 267,                /* CONTINUE  */
    ENUM = 268,                    /* ENUM  */
    CONST = 269,                   /* CONST  */
    STRUCT = 270,                  /* STRUCT  */
    IMPL = 271,                    /* IMPL  */
    TRAIT = 272,                   /* TRAIT  */
    PUB = 273,                     /* PUB  */
    CRATE = 274,                   /* CRATE  */
    SELF = 275,                    /* SELF  */
    SUPER = 276,                   /* SUPER  */
    SELF_PARAM = 277,              /* SELF_PARAM  */
    MUT_SELF_PARAM = 278,          /* MUT_SELF_PARAM  */
    ID = 279,                      /* ID  */
    INT_LITERAL = 280,             /* INT_LITERAL  */
    TRUE = 281,                    /* TRUE  */
    FALSE = 282,                   /* FALSE  */
    STRING_LITERAL = 283,          /* STRING_LITERAL  */
    FLOAT_LITERAL = 284,           /* FLOAT_LITERAL  */
    CHAR_LITERAL = 285,            /* CHAR_LITERAL  */
    INT = 286,                     /* INT  */
    BOOL = 287,                    /* BOOL  */
    STRING = 288,                  /* STRING  */
    FLOAT = 289,                   /* FLOAT  */
    CHAR = 290,                    /* CHAR  */
    RIGHT_ARROW = 291,             /* RIGHT_ARROW  */
    RETURN = 292,                  /* RETURN  */
    BREAK = 293,                   /* BREAK  */
    RANGE = 294,                   /* RANGE  */
    RANGE_IN = 295,                /* RANGE_IN  */
    AND = 296,                     /* AND  */
    OR = 297,                      /* OR  */
    LESS_EQUAL = 298,              /* LESS_EQUAL  */
    GREATER_EQUAL = 299,           /* GREATER_EQUAL  */
    EQUAL = 300,                   /* EQUAL  */
    NOT_EQUAL = 301,               /* NOT_EQUAL  */
    UMINUS = 302                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 11 "grammar_with_code.y"

	struct program_node * prg;
	struct expr_node * expr;
	struct expr_list_node * expr_list;
	struct stmt_node * stmt_;
	struct stmt_list_node * stmt_list;
	struct let_stmt_node * let_stmt;
	struct decl_stmt_node * decl_stmt;
	struct struct_item_node * struct_item;
	struct struct_node * struct_;
	struct struct_list_node * struct_items;
	struct enum_node * enum_;
	struct enum_item_node * enum_item;
	struct enum_list_node * enum_items;
	struct function_param_node * function_param;
	struct function_node * function_;
	struct function_params_node * function_params;
	struct const_stmt_node * const_stmt;
	struct associated_item_node * associated_item;
	struct trait_node * trait_;
	struct associated_items_node * associated_items;
	struct impl_node * impl_;
	struct type_node * type_;
	int int_const;
	char * string_const;
	bool bool_const;
	float float_const;
	char char_const;
	enum visibility vis;

#line 142 "grammar_with_code.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_GRAMMAR_WITH_CODE_TAB_H_INCLUDED  */
