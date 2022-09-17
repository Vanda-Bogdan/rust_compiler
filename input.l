%option noyywrap
%option never-interactive

%%

as { printf("Found KW_AS"); }
break { printf("Found KW_BREAK"); }
const { printf("Found KW_CONST"); }
continue { printf("Found KW_CONTINUE"); }
crate { printf("Found KW_CRATE"); }
else { printf("Found KW_ELSE"); }
enum { printf("Found KW_ENUM"); }
extern { printf("Found KW_EXTERN"); }
false { printf("Found KW_FALSE"); }
fn { printf("Found KW_FN"); }
for { printf("Found KW_FOR"); }
if { printf("Found KW_IF"); }
impl { printf("Found KW_IMPL"); }
in { printf("Found KW_IN"); }
let { printf("Found KW_LET"); }
loop { printf("Found KW_LOOP"); }
match { printf("Found KW_MATCH"); }
mod { printf("Found KW_MOD"); }
move { printf("Found KW_MOVE"); }
mut { printf("Found KW_MUT"); }
pub { printf("Found KW_PUB"); }
ref { printf("Found KW_REF"); }
return { printf("Found KW_RETURN"); }
self { printf("Found KW_SELFVALUE"); }
Self { printf("Found KW_SELFTYPE"); }
static { printf("Found KW_STATIC"); }
struct { printf("Found KW_STRUCT"); }
super { printf("Found KW_SUPER"); }
trait { printf("Found KW_TRAIT"); }
true { printf("Found KW_TRUE"); }
type { printf("Found KW_TYPE"); }
unsafe { printf("Found KW_UNSAFE"); }
use { printf("Found KW_USE"); }
where { printf("Found KW_WHERE"); }
while { printf("Found KW_WHILE"); }
async { printf("Found KW_ASYNC"); }
await { printf("Found KW_AWAITE"); }
dyn { printf("Found KW_DYN"); }

%%

yywrap(){}

int main()
{
  yylex();  
  return 0; 
}
