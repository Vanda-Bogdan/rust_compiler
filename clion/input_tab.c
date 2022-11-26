
/*  A Bison parser, made from input.y with Bison version GNU Bison version 1.24
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	FOR	258
#define	LOOP	259
#define	IN	260
#define	IF	261
#define	ELSE	262
#define	WHILE	263
#define	LET	264
#define	MUT	265
#define	FN	266
#define	BREAK	267
#define	CONTINUE	268
#define	RETURN	269
#define	ENUM	270
#define	CONST	271
#define	STRUCT	272
#define	IMPL	273
#define	TRAIT	274
#define	PUB	275
#define	CRATE	276
#define	SELF	277
#define	SUPER	278
#define	ID	279
#define	INT_LITERAL	280
#define	TRUE	281
#define	FALSE	282
#define	STRING_LITERAL	283
#define	FLOAT_LITERAL	284
#define	CHAR_LITERAL	285
#define	INT	286
#define	BOOL	287
#define	STRING	288
#define	FLOAT	289
#define	CHAR	290
#define	RANGE	291
#define	RANGE_IN	292
#define	RIGHT_ARROW	293
#define	PLUS_ASGN	294
#define	MINUS_ASGN	295
#define	MUL_ASGN	296
#define	DIV_ASGN	297
#define	REM_ASGN	298
#define	AND	299
#define	OR	300
#define	LESS_EQUAL	301
#define	GREATER_EQUAL	302
#define	EQUAL	303
#define	NOT_EQUAL	304
#define	UMINUS	305

#line 20 "input.y"

#include tree_nodes.h

#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		269
#define	YYFLAG		-32768
#define	YYNTBASE	71

#define YYTRANSLATE(x) ((unsigned)(x) <= 305 ? yytranslate[x] : 115)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    61,     2,     2,     2,    68,     2,     2,    37,
    63,    59,    57,    64,    58,    67,    60,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,    70,    36,    51,
    43,    52,    69,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    65,     2,    66,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    38,     2,    39,     2,     2,     2,     2,     2,
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
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    40,    41,    42,    44,    45,    46,    47,    48,    49,    50,
    53,    54,    55,    56,    62
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     3,     6,     8,    10,    14,    16,    18,    20,
    22,    25,    27,    31,    33,    38,    43,    50,    54,    56,
    58,    60,    62,    64,    66,    68,    70,    72,    76,    80,
    84,    88,    92,    96,   100,   104,   108,   112,   116,   119,
   122,   125,   129,   133,   137,   141,   145,   149,   153,   157,
   161,   167,   171,   174,   177,   179,   183,   186,   189,   191,
   193,   195,   197,   199,   201,   204,   208,   214,   218,   224,
   228,   230,   232,   235,   238,   240,   242,   244,   246,   249,
   252,   255,   257,   265,   271,   277,   281,   283,   285,   287,
   289,   291,   293,   299,   306,   308,   312,   315,   317,   322,
   326,   333,   339,   347,   355,   362,   369,   370,   372,   375,
   377,   381,   385,   388,   394,   398,   399,   401,   404,   406,
   410,   415,   419,   421,   423,   429,   437,   443,   444,   446,
   448,   451,   454,   456,   459,   461,   467,   475,   481,   489,
   491,   493,   495,   497,   499,   501,   506,   511
};

static const short yyrhs[] = {    95,
     0,     0,    73,    64,     0,    73,     0,    74,     0,    73,
    64,    74,     0,    75,     0,    81,     0,    76,     0,    77,
     0,    12,    74,     0,    13,     0,    37,    74,    63,     0,
    78,     0,    74,    65,    74,    66,     0,    74,    37,    72,
    63,     0,    74,    67,    24,    37,    72,    63,     0,    74,
    67,    24,     0,    79,     0,    80,     0,    24,     0,    30,
     0,    28,     0,    25,     0,    29,     0,    26,     0,    27,
     0,    74,    57,    74,     0,    74,    58,    74,     0,    74,
    59,    74,     0,    74,    60,    74,     0,    74,    68,    74,
     0,    74,    55,    74,     0,    74,    56,    74,     0,    74,
    52,    74,     0,    74,    51,    74,     0,    74,    54,    74,
     0,    74,    53,    74,     0,    74,    69,     0,    58,    74,
     0,    61,    74,     0,    74,    50,    74,     0,    74,    49,
    74,     0,    74,    43,    74,     0,    74,    44,    74,     0,
    74,    45,    74,     0,    74,    46,    74,     0,    74,    47,
    74,     0,    74,    48,    74,     0,    65,    72,    66,     0,
    65,    74,    36,    74,    66,     0,    74,    40,    74,     0,
    74,    40,     0,    40,    74,     0,    40,     0,    74,    41,
    74,     0,    41,    74,     0,    14,    74,     0,    14,     0,
    86,     0,    82,     0,    83,     0,    84,     0,    85,     0,
     4,    86,     0,     8,    74,    86,     0,     3,    24,     5,
    74,    86,     0,     6,    74,    86,     0,     6,    74,    86,
     7,    86,     0,    38,    87,    39,     0,    88,     0,    75,
     0,    87,    88,     0,    87,    75,     0,    36,     0,    89,
     0,    90,     0,    91,     0,   114,    91,     0,    75,    36,
     0,    81,    36,     0,    81,     0,     9,    24,    70,   113,
    43,    74,    36,     0,     9,    24,    43,    74,    36,     0,
     9,    24,    70,   113,    36,     0,     9,    24,    36,     0,
    92,     0,    95,     0,   112,     0,   100,     0,   107,     0,
   104,     0,    15,    24,    38,    93,    39,     0,    15,    24,
    38,    93,    64,    39,     0,    94,     0,    93,    64,    94,
     0,   114,    24,     0,    24,     0,   114,    24,    43,    74,
     0,    24,    43,    74,     0,   114,    24,    43,    38,   101,
    39,     0,    24,    43,    38,   101,    39,     0,    11,    24,
    37,    96,    63,    99,    86,     0,    11,    24,    37,    96,
    63,    99,    36,     0,    11,    24,    37,    96,    63,    86,
     0,    11,    24,    37,    96,    63,    36,     0,     0,    97,
     0,    97,    64,     0,    98,     0,    97,    64,    98,     0,
    24,    70,   113,     0,    42,   113,     0,    17,    24,    38,
   101,    39,     0,    17,    24,    36,     0,     0,   102,     0,
   102,    64,     0,   103,     0,   102,    64,   103,     0,   114,
    24,    70,   113,     0,    24,    70,   113,     0,   105,     0,
   106,     0,    18,   113,    38,   108,    39,     0,    18,    24,
     3,   113,    38,   108,    39,     0,    19,    24,    38,   108,
    39,     0,     0,   109,     0,   110,     0,   109,   110,     0,
   114,    95,     0,    95,     0,   114,   111,     0,   111,     0,
    16,    24,    70,   113,    36,     0,    16,    24,    70,   113,
    43,    74,    36,     0,    16,    24,    70,   113,    36,     0,
    16,    24,    70,   113,    43,    74,    36,     0,    31,     0,
    33,     0,    35,     0,    34,     0,    32,     0,    20,     0,
    20,    37,    21,    63,     0,    20,    37,    22,    63,     0,
    20,    37,    23,    63,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    26,    32,    33,    34,    37,    38,    41,    42,    46,    47,
    48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
    58,    61,    62,    63,    64,    65,    66,    69,    70,    71,
    72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
    82,    83,    84,    85,    86,    87,    88,    89,    90,    93,
    94,    97,    98,    99,   100,   101,   102,   105,   106,   110,
   111,   112,   113,   114,   117,   120,   123,   126,   127,   130,
   135,   136,   137,   138,   141,   142,   143,   144,   145,   148,
   149,   150,   153,   154,   155,   156,   160,   161,   162,   163,
   164,   165,   169,   170,   173,   174,   177,   178,   179,   180,
   181,   182,   186,   187,   188,   189,   192,   193,   194,   197,
   198,   201,   204,   227,   228,   231,   232,   233,   236,   237,
   240,   241,   245,   246,   249,   252,   256,   259,   260,   263,
   264,   267,   268,   269,   270,   273,   274,   278,   279,   283,
   284,   285,   286,   287,   291,   292,   293,   294
};

static const char * const yytname[] = {   "$","error","$undefined.","FOR","LOOP",
"IN","IF","ELSE","WHILE","LET","MUT","FN","BREAK","CONTINUE","RETURN","ENUM",
"CONST","STRUCT","IMPL","TRAIT","PUB","CRATE","SELF","SUPER","ID","INT_LITERAL",
"TRUE","FALSE","STRING_LITERAL","FLOAT_LITERAL","CHAR_LITERAL","INT","BOOL",
"STRING","FLOAT","CHAR","';'","'('","'{'","'}'","RANGE","RANGE_IN","RIGHT_ARROW",
"'='","PLUS_ASGN","MINUS_ASGN","MUL_ASGN","DIV_ASGN","REM_ASGN","AND","OR","'<'",
"'>'","LESS_EQUAL","GREATER_EQUAL","EQUAL","NOT_EQUAL","'+'","'-'","'*'","'/'",
"'!'","UMINUS","')'","','","'['","']'","'.'","'%'","'?'","':'","Program","ExprList_final",
"ExprList","Expr","ExprWithoutBlock","Literal","OperatorExpr","ArrayExpr","RangeExpr",
"ReturnExpr","ExprWithBlock","LoopExpr","WhileExpr","ForExpr","IfExpr","BlockExpr",
"StmtList","Stmt","ExprStmt","LetStmt","OtherStmt","Enum","EnumItems","EnumItem",
"Function","FuncParamList_final","FuncParamList","FuncParam","FuncReturnType",
"Struct","StructFields_final","StructFields","StructField","Impl","InherentImpl",
"TraitImpl","Trait","AssociatedItems_final","AssociatedItems","AssociatedItem",
"ConstantItem","ConstStmt","Type","Visibility",""
};
#endif

static const short yyr1[] = {     0,
    71,    72,    72,    72,    73,    73,    74,    74,    75,    75,
    75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
    75,    76,    76,    76,    76,    76,    76,    77,    77,    77,
    77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
    77,    77,    77,    77,    77,    77,    77,    77,    77,    78,
    78,    79,    79,    79,    79,    79,    79,    80,    80,    81,
    81,    81,    81,    81,    82,    83,    84,    85,    85,    86,
    87,    87,    87,    87,    88,    88,    88,    88,    88,    89,
    89,    89,    90,    90,    90,    90,    91,    91,    91,    91,
    91,    91,    92,    92,    93,    93,    94,    94,    94,    94,
    94,    94,    95,    95,    95,    95,    96,    96,    96,    97,
    97,    98,    99,   100,   100,   101,   101,   101,   102,   102,
   103,   103,   104,   104,   105,   106,   107,   108,   108,   109,
   109,   110,   110,   110,   110,   111,   111,   112,   112,   113,
   113,   113,   113,   113,   114,   114,   114,   114
};

static const short yyr2[] = {     0,
     1,     0,     2,     1,     1,     3,     1,     1,     1,     1,
     2,     1,     3,     1,     4,     4,     6,     3,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
     2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     5,     3,     2,     2,     1,     3,     2,     2,     1,     1,
     1,     1,     1,     1,     2,     3,     5,     3,     5,     3,
     1,     1,     2,     2,     1,     1,     1,     1,     2,     2,
     2,     1,     7,     5,     5,     3,     1,     1,     1,     1,
     1,     1,     5,     6,     1,     3,     2,     1,     4,     3,
     6,     5,     7,     7,     6,     6,     0,     1,     2,     1,
     3,     3,     2,     5,     3,     0,     1,     2,     1,     3,
     4,     3,     1,     1,     5,     7,     5,     0,     1,     1,
     2,     2,     1,     2,     1,     5,     7,     5,     7,     1,
     1,     1,     1,     1,     1,     4,     4,     4
};

static const short yydefact[] = {     0,
     0,     1,     0,   107,     0,     0,   108,   110,     0,     0,
   109,   140,   144,   141,   143,   142,   112,   106,     0,     0,
   105,     0,   111,     0,     0,     0,     0,     0,     0,    12,
    59,     0,     0,     0,     0,     0,   145,    21,    24,    26,
    27,    23,    25,    22,    75,     0,    55,     0,     0,     0,
     2,     0,     7,     9,    10,    14,    19,    20,     8,    61,
    62,    63,    64,    60,     0,    71,    76,    77,    78,    87,
    88,    90,    92,   123,   124,    91,    89,     0,   113,   104,
   103,     0,    65,     0,     7,     8,     0,     0,    11,    58,
     0,     0,     0,     0,     0,     0,     0,     0,    54,    57,
    40,    41,     0,     4,     5,     2,    53,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    39,
    80,    81,    70,     7,    73,    79,     0,    68,    66,    86,
     0,     0,     0,     0,   115,   116,     0,   128,   128,     0,
     0,     0,    13,    50,     3,     0,     0,     5,    52,    56,
    44,    45,    46,    47,    48,    49,    43,    42,    36,    35,
    38,    37,    33,    34,    28,    29,    30,    31,     0,    18,
    32,     0,     0,     0,     0,    98,     0,    95,     0,     0,
     0,     0,   117,   119,     0,     0,     0,   133,     0,   129,
   130,   135,     0,     0,   146,   147,   148,     6,     0,    16,
    15,     2,    67,    69,    84,    85,     0,     0,    93,     0,
    97,   138,     0,     0,   114,   118,     0,   128,     0,   125,
   131,   132,   134,   127,    51,     0,     0,   116,   100,    94,
    96,     0,     0,   122,   120,     0,     0,     0,    17,    83,
    21,     0,     0,   116,    99,   139,   121,   126,     0,   102,
     0,   136,     0,   101,     0,   137,     0,     0,     0
};

static const short yydefgoto[] = {   267,
   103,   104,    52,    85,    54,    55,    56,    57,    58,    86,
    60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
    70,   187,   188,    71,     6,     7,     8,    22,    72,   192,
   193,   194,    73,    74,    75,    76,   199,   200,   201,   202,
    77,    17,   203
};

static const short yypact[] = {     3,
    -9,-32768,    -1,    30,   -24,    -7,     4,-32768,   254,    74,
    30,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   303,   254,
-32768,    33,-32768,    49,    40,   405,   405,    55,   405,-32768,
   405,    85,    89,    93,   147,    94,    20,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,   405,   405,   405,   405,   405,
   405,   945,   549,-32768,-32768,-32768,-32768,-32768,   587,-32768,
-32768,-32768,-32768,-32768,   243,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,   213,-32768,-32768,
-32768,   115,-32768,   813,-32768,-32768,   813,   -25,   945,   945,
    83,    63,   102,   134,   119,   122,   145,   846,   945,   945,
    82,    82,    77,    98,   644,   405,   405,   405,   405,   405,
   405,   405,   405,   405,   405,   405,   405,   405,   405,   405,
   405,   405,   405,   405,   405,   405,   405,   139,   405,-32768,
-32768,-32768,-32768,   625,-32768,-32768,   405,   162,-32768,-32768,
   405,   254,    17,   254,-32768,    31,   254,    19,    19,   112,
   113,   120,-32768,-32768,   405,   405,   121,   945,   945,   945,
   945,   945,   945,   945,   945,   945,     7,     7,    67,    67,
    67,    67,    67,    67,   105,   105,    82,    82,   879,   148,
   945,   813,    40,   678,   -17,   144,   -30,-32768,   164,     6,
   123,   150,   126,-32768,   170,   157,   172,-32768,   159,    19,
-32768,-32768,    22,   160,-32768,-32768,-32768,   945,   912,-32768,
-32768,   405,-32768,-32768,-32768,-32768,   405,   447,-32768,    -8,
   161,-32768,   405,   254,-32768,    31,   132,    19,   133,-32768,
-32768,-32768,-32768,-32768,-32768,   143,   712,   363,   945,-32768,
-32768,   489,   746,-32768,-32768,   254,   168,   254,-32768,-32768,
   123,   169,   137,   363,   945,-32768,-32768,-32768,    34,-32768,
   173,-32768,   405,-32768,   780,-32768,   209,   214,-32768
};

static const short yypgoto[] = {-32768,
   -98,-32768,   -26,   -13,-32768,-32768,-32768,-32768,-32768,   -12,
-32768,-32768,-32768,-32768,    18,-32768,   152,-32768,-32768,   -76,
-32768,-32768,    -5,    10,-32768,-32768,   207,-32768,-32768,  -225,
-32768,    -6,-32768,-32768,-32768,-32768,  -122,-32768,    27,    16,
-32768,    -3,   -15
};


#define	YYLAST		1014


static const short yytable[] = {    84,
    87,   136,    89,    78,    90,    53,    59,   157,   219,     2,
   140,    37,   252,     1,     3,   186,    79,   141,   216,    98,
    99,   100,   101,   102,   105,   217,   204,    21,   261,     1,
   240,    95,     1,   220,   197,     4,    37,   197,    37,    81,
   186,   222,    83,   106,   142,     9,   107,   108,   223,    78,
    37,   134,    59,     5,   191,    10,    97,   117,   118,   119,
   120,   121,   122,   123,   124,   125,   126,    11,    80,   262,
    19,   127,    82,   128,   129,   130,   263,    19,    88,   158,
   159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
   169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
   179,   138,   181,   106,   139,   247,   107,   108,    91,    18,
   182,    19,    92,   236,   184,    20,    93,    96,   106,   137,
   143,   107,   108,   123,   124,   125,   126,   189,   208,   209,
   195,   127,   144,   128,   129,   130,   147,   145,   185,   146,
   190,   106,   154,   196,   107,   108,   127,     1,   128,   129,
   130,    32,    33,    34,    35,    36,   148,   198,   198,   149,
   227,   155,   180,   125,   126,   150,   151,   152,   183,   127,
    94,   128,   129,   130,   205,   206,   136,    12,    13,    14,
    15,    16,   207,   210,   212,   158,   218,   221,   225,   226,
   237,   239,   224,   227,   228,   229,   243,   230,   234,   213,
   214,   246,   248,   242,   189,   249,   258,   260,   268,   198,
   195,   264,   232,   269,   241,   255,   135,    23,   233,   245,
   244,     0,   253,     1,    53,    59,   231,    32,    33,    34,
    35,    36,     0,     0,     0,     0,   265,   198,   253,     0,
    53,    59,   257,     0,   259,    24,    25,     0,    26,     0,
    27,    28,     0,     1,    29,    30,    31,    32,    33,    34,
    35,    36,    37,     0,     0,     0,    38,    39,    40,    41,
    42,    43,    44,     0,     0,     0,     0,     0,    45,    46,
    19,   133,    47,    48,    12,    13,    14,    15,    16,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    49,     0,     0,    50,     0,    24,    25,    51,    26,     0,
    27,    28,     0,     1,    29,    30,    31,    32,    33,    34,
    35,    36,    37,     0,     0,     0,    38,    39,    40,    41,
    42,    43,    44,     0,     0,     0,     0,     0,    45,    46,
    19,     0,    47,    48,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    49,     0,     0,    50,     0,    24,    25,    51,    26,     0,
    27,    28,     0,     1,    29,    30,    31,    32,    33,    34,
    35,    36,    37,     0,     0,     0,   251,    39,    40,    41,
    42,    43,    44,     0,     0,     0,     0,     0,    45,    46,
    19,     0,    47,    48,     0,     0,     0,    24,    25,     0,
    26,     0,    27,     0,     0,     0,    29,    30,    31,     0,
    49,     0,     0,    50,     0,     0,     0,    51,    38,    39,
    40,    41,    42,    43,    44,     0,     0,     0,     0,     0,
     0,    46,    19,     0,    47,    48,     0,     0,     0,    24,
    25,     0,    26,     0,    27,     0,     0,     0,    29,    30,
    31,     0,    49,     0,     0,    50,     0,     0,     0,    51,
    38,    39,    40,    41,    42,    43,    44,     0,     0,     0,
     0,     0,     0,    46,   238,     0,    47,    48,     0,     0,
     0,    24,    25,     0,    26,     0,    27,     0,     0,     0,
    29,    30,    31,     0,    49,     0,     0,    50,     0,     0,
     0,    51,    38,    39,    40,    41,    42,    43,    44,     0,
     0,     0,     0,     0,     0,    46,   254,     0,    47,    48,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    49,     0,     0,    50,
     0,   -72,   -72,    51,   -72,     0,   -72,   -72,     0,   -72,
   -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,     0,
     0,     0,   -72,   -72,   -72,   -72,   -72,   -72,   -72,     0,
     0,     0,     0,     0,   131,     0,   -72,   -72,     0,   -82,
   -82,     0,   -82,     0,   -82,   -82,     0,   -82,   -82,   -82,
   -82,   -82,   -82,   -82,   -82,   -82,   -82,     0,     0,   -72,
   -82,   -82,   -82,   -82,   -82,   -82,   -82,     0,     0,     0,
     0,     0,   132,     0,   -82,   -82,     0,   -74,   -74,     0,
   -74,     0,   -74,   -74,     0,   -74,   -74,   -74,   -74,   -74,
   -74,   -74,   -74,   -74,   -74,     0,     0,   -82,   -74,   -74,
   -74,   -74,   -74,   -74,   -74,     0,     0,     0,     0,     0,
   131,     0,   -74,   -74,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   156,
   106,     0,     0,   107,   108,   -74,   109,   110,   111,   112,
   113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
   123,   124,   125,   126,     0,     0,     0,     0,   127,     0,
   128,   129,   130,   215,   106,     0,     0,   107,   108,     0,
   109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
   119,   120,   121,   122,   123,   124,   125,   126,     0,     0,
     0,     0,   127,     0,   128,   129,   130,   250,   106,     0,
     0,   107,   108,     0,   109,   110,   111,   112,   113,   114,
   115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
   125,   126,     0,     0,     0,     0,   127,     0,   128,   129,
   130,   256,   106,     0,     0,   107,   108,     0,   109,   110,
   111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
   121,   122,   123,   124,   125,   126,     0,     0,     0,     0,
   127,     0,   128,   129,   130,   266,   106,     0,     0,   107,
   108,     0,   109,   110,   111,   112,   113,   114,   115,   116,
   117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     0,     0,     0,     0,   127,     0,   128,   129,   130,   106,
    19,     0,   107,   108,     0,   109,   110,   111,   112,   113,
   114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
   124,   125,   126,     0,     0,     0,     0,   127,     0,   128,
   129,   130,   106,     0,     0,   107,   108,     0,   109,   110,
   111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
   121,   122,   123,   124,   125,   126,     0,     0,   153,     0,
   127,     0,   128,   129,   130,   106,     0,     0,   107,   108,
     0,   109,   110,   111,   112,   113,   114,   115,   116,   117,
   118,   119,   120,   121,   122,   123,   124,   125,   126,     0,
     0,     0,     0,   127,   211,   128,   129,   130,   106,     0,
     0,   107,   108,     0,   109,   110,   111,   112,   113,   114,
   115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
   125,   126,     0,     0,     0,     0,   127,   235,   128,   129,
   130,   106,     0,     0,   107,   108,     0,   109,   110,   111,
   112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
   122,   123,   124,   125,   126,     0,     0,     0,     0,   127,
     0,   128,   129,   130
};

static const short yycheck[] = {    26,
    27,    78,    29,    19,    31,    19,    19,   106,    39,     0,
    36,    20,   238,    11,    24,    24,    20,    43,    36,    46,
    47,    48,    49,    50,    51,    43,   149,    10,   254,    11,
    39,    35,    11,    64,    16,    37,    20,    16,    20,    22,
    24,    36,    25,    37,    70,    70,    40,    41,    43,    65,
    20,    65,    65,    24,    24,    63,    37,    51,    52,    53,
    54,    55,    56,    57,    58,    59,    60,    64,    36,    36,
    38,    65,    24,    67,    68,    69,    43,    38,    24,   106,
   107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
   117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
   127,    84,   129,    37,    87,   228,    40,    41,    24,    36,
   137,    38,    24,   212,   141,    42,    24,    24,    37,     5,
    38,    40,    41,    57,    58,    59,    60,   143,   155,   156,
   146,    65,    70,    67,    68,    69,     3,    36,   142,    38,
   144,    37,    66,   147,    40,    41,    65,    11,    67,    68,
    69,    15,    16,    17,    18,    19,    38,   148,   149,    38,
    24,    64,    24,    59,    60,    21,    22,    23,     7,    65,
    24,    67,    68,    69,    63,    63,   253,    31,    32,    33,
    34,    35,    63,    63,    37,   212,    43,    24,    39,    64,
   217,   218,    70,    24,    38,    24,   223,    39,    39,   182,
   183,    70,    70,    43,   220,    63,    39,    39,     0,   200,
   226,    39,   203,     0,   220,   242,    65,    11,   203,   226,
   224,    -1,   238,    11,   238,   238,   200,    15,    16,    17,
    18,    19,    -1,    -1,    -1,    -1,   263,   228,   254,    -1,
   254,   254,   246,    -1,   248,     3,     4,    -1,     6,    -1,
     8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
    18,    19,    20,    -1,    -1,    -1,    24,    25,    26,    27,
    28,    29,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,
    38,    39,    40,    41,    31,    32,    33,    34,    35,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    58,    -1,    -1,    61,    -1,     3,     4,    65,     6,    -1,
     8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
    18,    19,    20,    -1,    -1,    -1,    24,    25,    26,    27,
    28,    29,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,
    38,    -1,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    58,    -1,    -1,    61,    -1,     3,     4,    65,     6,    -1,
     8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
    18,    19,    20,    -1,    -1,    -1,    24,    25,    26,    27,
    28,    29,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,
    38,    -1,    40,    41,    -1,    -1,    -1,     3,     4,    -1,
     6,    -1,     8,    -1,    -1,    -1,    12,    13,    14,    -1,
    58,    -1,    -1,    61,    -1,    -1,    -1,    65,    24,    25,
    26,    27,    28,    29,    30,    -1,    -1,    -1,    -1,    -1,
    -1,    37,    38,    -1,    40,    41,    -1,    -1,    -1,     3,
     4,    -1,     6,    -1,     8,    -1,    -1,    -1,    12,    13,
    14,    -1,    58,    -1,    -1,    61,    -1,    -1,    -1,    65,
    24,    25,    26,    27,    28,    29,    30,    -1,    -1,    -1,
    -1,    -1,    -1,    37,    38,    -1,    40,    41,    -1,    -1,
    -1,     3,     4,    -1,     6,    -1,     8,    -1,    -1,    -1,
    12,    13,    14,    -1,    58,    -1,    -1,    61,    -1,    -1,
    -1,    65,    24,    25,    26,    27,    28,    29,    30,    -1,
    -1,    -1,    -1,    -1,    -1,    37,    38,    -1,    40,    41,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    58,    -1,    -1,    61,
    -1,     3,     4,    65,     6,    -1,     8,     9,    -1,    11,
    12,    13,    14,    15,    16,    17,    18,    19,    20,    -1,
    -1,    -1,    24,    25,    26,    27,    28,    29,    30,    -1,
    -1,    -1,    -1,    -1,    36,    -1,    38,    39,    -1,     3,
     4,    -1,     6,    -1,     8,     9,    -1,    11,    12,    13,
    14,    15,    16,    17,    18,    19,    20,    -1,    -1,    61,
    24,    25,    26,    27,    28,    29,    30,    -1,    -1,    -1,
    -1,    -1,    36,    -1,    38,    39,    -1,     3,     4,    -1,
     6,    -1,     8,     9,    -1,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    -1,    -1,    61,    24,    25,
    26,    27,    28,    29,    30,    -1,    -1,    -1,    -1,    -1,
    36,    -1,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
    37,    -1,    -1,    40,    41,    61,    43,    44,    45,    46,
    47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
    57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,    -1,
    67,    68,    69,    36,    37,    -1,    -1,    40,    41,    -1,
    43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
    53,    54,    55,    56,    57,    58,    59,    60,    -1,    -1,
    -1,    -1,    65,    -1,    67,    68,    69,    36,    37,    -1,
    -1,    40,    41,    -1,    43,    44,    45,    46,    47,    48,
    49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
    59,    60,    -1,    -1,    -1,    -1,    65,    -1,    67,    68,
    69,    36,    37,    -1,    -1,    40,    41,    -1,    43,    44,
    45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
    55,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
    65,    -1,    67,    68,    69,    36,    37,    -1,    -1,    40,
    41,    -1,    43,    44,    45,    46,    47,    48,    49,    50,
    51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
    -1,    -1,    -1,    -1,    65,    -1,    67,    68,    69,    37,
    38,    -1,    40,    41,    -1,    43,    44,    45,    46,    47,
    48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
    58,    59,    60,    -1,    -1,    -1,    -1,    65,    -1,    67,
    68,    69,    37,    -1,    -1,    40,    41,    -1,    43,    44,
    45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
    55,    56,    57,    58,    59,    60,    -1,    -1,    63,    -1,
    65,    -1,    67,    68,    69,    37,    -1,    -1,    40,    41,
    -1,    43,    44,    45,    46,    47,    48,    49,    50,    51,
    52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
    -1,    -1,    -1,    65,    66,    67,    68,    69,    37,    -1,
    -1,    40,    41,    -1,    43,    44,    45,    46,    47,    48,
    49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
    59,    60,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
    69,    37,    -1,    -1,    40,    41,    -1,    43,    44,    45,
    46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,
    -1,    67,    68,    69
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 192 "bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#else
#define YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#endif

int
yyparse(YYPARSE_PARAM)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

}
   /* the action file gets copied in in place of this dollarsign */
#line 487 "bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 295 "input.y"
