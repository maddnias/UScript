grammar UScript;

module
    : block EOF
    ;

block
    : stat* retstat?
    ;

stat
    : 'func' name=funcname funcbody		#FunctionDeclStatement
	| varDecl							#VarDeclStatement
	| functioncall						#FuncCallStatement
	| retstat							#ReturnStatement
    ;

retstat
    : 'return' exp?
    ;

label
    : '::' NAME '::'
    ;

funcname
    : NAME
    ;

varlist
    : var (',' var)*
    ;

namelist
    : NAME (',' NAME)*
    ;

explist
    : exp (',' exp)*
    ;

exp
    : '(' exp ')'							#testerexp
	| 'nil'									#NilExp
	| 'false'								#FalseExp
	| 'true'								#TrueExp
    | number								#NumberExp
	| var									#VarExp
    | string								#StringExp
	| <assoc=right> exp operatorPower exp	#PowerExp
    | operatorUnary exp						#UnaryExp
    | exp operatorMulDivMod exp				#MulDivModExp
    | exp operatorAddSub exp				#AddSubExp
    | exp operatorComparison exp			#CmpExp
    | exp operatorAnd exp					#AndExp
    | exp operatorOr exp					#OrExp
    | exp operatorBitwise exp				#BitwiseExp
    ;

prefixexp
    : varOrExp nameAndArgs*
    ;

functioncall
    //: varOrExp nameAndArgs+
	: target=funcname argList
    ;

argList
	: '(' explist? ')'
	;

varOrExp
    : var | '(' exp ')'
    ;

var
    : NAME
    ;

varDecl
	: 'def' name=NAME ('=' initData=exp)?
	;

varSuffix
    : nameAndArgs* ('[' exp ']' | '.' NAME)
    ;

nameAndArgs
    : (':' NAME)? args
    ;

param
	: var (':' paramType=type)?
	;

type
	: TYPE_BYTE
	| TYPE_CHAR
	| TYPE_INT
	| TYPE_FLOAT
	| TYPE_STRING
	;

args
    : '(' explist? ')' | tableconstructor | string
    ;

functiondef
    : 'function' funcbody
    ;

funcbody
    : '(' params=parlist? ')' block 'end'
    ;

parlist
    : param? (',' param)*
    ;

tableconstructor
    : '{' fieldlist? '}'
    ;

fieldlist
    : field (fieldsep field)* fieldsep?
    ;

field
    : '[' exp ']' '=' exp | NAME '=' exp | exp
    ;

fieldsep
    : ',' | ';'
    ;

operatorOr 
	: 'or';

operatorAnd 
	: 'and';

operatorComparison 
	: '<' | '>' | '<=' | '>=' | '~=' | '==';

operatorStrcat
	: '..';

operatorAddSub
	: '+' | '-';

operatorMulDivMod
	: '*' | '/' | '%' | '//';

operatorBitwise
	: '&' | '|' | '~' | '<<' | '>>';

operatorUnary
    : 'not' | '#' | '-' | '~';

operatorPower
    : '^';

number
    : INT | HEX | FLOAT | HEX_FLOAT
    ;

string
    : strData=NORMALSTRING 
	| strData=CHARSTRING 
	| strData=LONGSTRING
    ;

// LEXER

TYPE_BYTE
	: 'Byte'
	;

TYPE_INT
	: 'Int'
	;

TYPE_FLOAT
	: 'Float'
	;

TYPE_STRING
	: 'String'
	;

TYPE_CHAR
	: 'Char'
	;

NAME
    : [a-zA-Z_][a-zA-Z_0-9]*
    ;

NORMALSTRING
    : '"' ( EscapeSequence | ~('\\'|'"') )* '"' 
    ;

CHARSTRING
    : '\'' ( EscapeSequence | ~('\''|'\\') )* '\''
    ;

LONGSTRING
    : '[' NESTED_STR ']'
    ;

fragment
NESTED_STR
    : '=' NESTED_STR '='
    | '[' .*? ']'
    ;

INT
    : Digit+
    ;

HEX
    : '0' [xX] HexDigit+
    ;

FLOAT
    : Digit+ '.' Digit* ExponentPart?
    | '.' Digit+ ExponentPart?
    | Digit+ ExponentPart
    ;

HEX_FLOAT
    : '0' [xX] HexDigit+ '.' HexDigit* HexExponentPart?
    | '0' [xX] '.' HexDigit+ HexExponentPart?
    | '0' [xX] HexDigit+ HexExponentPart
    ;

fragment
ExponentPart
    : [eE] [+-]? Digit+
    ;

fragment
HexExponentPart
    : [pP] [+-]? Digit+
    ;

fragment
EscapeSequence
    : '\\' [abfnrtvz"'\\]
    | '\\' '\r'? '\n'
    | DecimalEscape
    | HexEscape
    | UtfEscape
    ;
    
fragment
DecimalEscape
    : '\\' Digit
    | '\\' Digit Digit
    | '\\' [0-2] Digit Digit
    ;
    
fragment
HexEscape
    : '\\' 'x' HexDigit HexDigit
    ;
fragment
UtfEscape
    : '\\' 'u{' HexDigit+ '}'
    ;
fragment
Digit
    : [0-9]
    ;
fragment
HexDigit
    : [0-9a-fA-F]
    ;
COMMENT
    : '--[' NESTED_STR ']' -> channel(HIDDEN)
    ;
    
LINE_COMMENT
    : '--'
    (                                               // --
    | '[' '='*                                      // --[==
    | '[' '='* ~('='|'['|'\r'|'\n') ~('\r'|'\n')*   // --[==AA
    | ~('['|'\r'|'\n') ~('\r'|'\n')*                // --AAA
    ) ('\r\n'|'\r'|'\n'|EOF)
    -> channel(HIDDEN)
    ;
    
WS  
    : [ \t\u000C\r\n]+ -> skip
    ;
SHEBANG
    : '#' '!' ~('\n'|'\r')* -> channel(HIDDEN)
    ;

/*grammar UScript;

compileUnit
	: block* EOF
	;

block
	: expression
	| statement
	;

statement
	: funcDecl	#FuncDeclStatement
	| return	#ReturnStatement
	| varDecl	#VarDeclStatement
	;

return
	: RETURN expression
	;

expression
	: identifier						#IdentifierExpression
	| number							#NumberExpression
	| constant							#ConstantExpression
	| expression ARITH_ADD expression	#AdditionExpression
	| expression ARITH_SUB expression	#SubtractionExpression
	| OPEN_PARENTH expression CLOSE_PARENTH	#ParenthExpr
	;

funcDecl
	: 'func' funcName=NAME argList=argumentList? funcBody
	;

funcBody
	: block* return? 'end'
	;

varDecl
	: 'def' varName=NAME
	| 'def' varName=NAME varInit
	;

varInit
	: '=' varConst=constant
	;

constant
	: number
	| identifier
	| NORMALSTRING
	;

argument
	: argName=identifier (':' varType=type)?
	;

argumentList
	: OPEN_PARENTH argument? (',' argument)? CLOSE_PARENTH
	;

identifier
	: NAME
	;

type
	: TYPE_BYTE
	| TYPE_INT
	| TYPE_DECIMAL
	| TYPE_STRING
	;

number
    : INT | HEX | FLOAT | HEX_FLOAT
    ;

// LEXER

OPEN_PARENTH
	: '('
	;

CLOSE_PARENTH
	: ')'
	;

TYPE_BYTE
	: 'Byte'
	;

TYPE_INT
	: 'Int'
	;

TYPE_DECIMAL
	: 'Decimal'
	;

TYPE_STRING
	: 'String'
	;

ARITH_ADD
	: '+'
	;

ARITH_SUB
	: '-'
	;

NAME
    : [a-zA-Z_][a-zA-Z_0-9]*
    ;

RETURN
	: 'return'
	;

NORMALSTRING
    : '"' ( EscapeSequence | ~('\\'|'"') )* '"' 
    ;

CHARSTRING
    : '\'' ( EscapeSequence | ~('\''|'\\') )* '\''
    ;

LONGSTRING
    : '[' NESTED_STR ']'
    ;

fragment
NESTED_STR
    : '=' NESTED_STR '='
    | '[' .*? ']'
    ;

INT
    : Digit+
    ;

HEX
    : '0' [xX] HexDigit+
    ;

FLOAT
    : Digit+ '.' Digit* ExponentPart?
    | '.' Digit+ ExponentPart?
    | Digit+ ExponentPart
    ;

HEX_FLOAT
    : '0' [xX] HexDigit+ '.' HexDigit* HexExponentPart?
    | '0' [xX] '.' HexDigit+ HexExponentPart?
    | '0' [xX] HexDigit+ HexExponentPart
    ;

fragment
ExponentPart
    : [eE] [+-]? Digit+
    ;

fragment
HexExponentPart
    : [pP] [+-]? Digit+
    ;

fragment
EscapeSequence
    : '\\' [abfnrtvz"'\\]
    | '\\' '\r'? '\n'
    | DecimalEscape
    | HexEscape
    | UtfEscape
    ;
    
fragment
DecimalEscape
    : '\\' Digit
    | '\\' Digit Digit
    | '\\' [0-2] Digit Digit
    ;
    
fragment
HexEscape
    : '\\' 'x' HexDigit HexDigit
    ;

fragment
UtfEscape
    : '\\' 'u{' HexDigit+ '}'
    ;

fragment
Digit
    : [0-9]
    ;

fragment
HexDigit
    : [0-9a-fA-F]
    ;

COMMENT
    : '--[' NESTED_STR ']' -> channel(HIDDEN)
    ;
    
LINE_COMMENT
    : '--'
    (                                               // --
    | '[' '='*                                      // --[==
    | '[' '='* ~('='|'['|'\r'|'\n') ~('\r'|'\n')*   // --[==AA
    | ~('['|'\r'|'\n') ~('\r'|'\n')*                // --AAA
    ) ('\r\n'|'\r'|'\n'|EOF)
    -> channel(HIDDEN)
    ;
    
WS  
    : [ \t\u000C\r\n]+ -> skip
    ;

SHEBANG
    : '#' '!' ~('\n'|'\r')* -> channel(HIDDEN)
    ;*/