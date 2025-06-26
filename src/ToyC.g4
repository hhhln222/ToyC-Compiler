grammar ToyC;               // 定义文法的名字

compUnit: funcDef+;

funcDef: (INT | VOID) ID '(' (param (',' param)*)? ')' block;

param: INT ID;

block: '{' stmt* '}';

stmt: block                                  # blockStmt
    | ';'                                    # emptyStmt
    | expr ';'                               # exprStmt
    | ID '=' expr ';'                        # assignStmt
    | INT ID '=' expr ';'                    # declStmt
    | IF '(' expr ')' stmt (ELSE stmt)?      # ifStmt
    | WHILE '(' expr ')' stmt                # whileStmt
    | BREAK ';'                              # breakStmt
    | CONTINUE ';'                           # continueStmt
    | RETURN expr ';'                        # returnStmt
    ;

expr: lOrExpr;

lOrExpr: lAndExpr ('||' lAndExpr)*;

lAndExpr: relExpr ('&&' relExpr)*;

relExpr: addExpr (('<' | '>' | '<=' | '>=' | '==' | '!=') addExpr)?;

addExpr: mulExpr (('+' | '-') mulExpr)*;

mulExpr: unaryExpr (('*' | '/' | '%') unaryExpr)*;

unaryExpr: ('+' | '-' | '!') unaryExpr | primaryExpr;

primaryExpr
    : ID                                    # idExpr
    | NUMBER                                 # numExpr
    | '(' expr ')'                           # parenExpr
    | ID '(' (expr (',' expr)*)? ')'        # callExpr
    ;

// Lexer Rules
INT: 'int';
VOID: 'void';
IF: 'if';
ELSE: 'else';
WHILE: 'while';
BREAK: 'break';
CONTINUE: 'continue';
RETURN: 'return';

ID: [a-zA-Z_] [a-zA-Z_0-9]*;
NUMBER: [0-9]+;

// Operators
PLUS: '+';
MINUS: '-';
MUL: '*';
DIV: '/';
MOD: '%';
NOT: '!';
ASSIGN: '=';
LT: '<';
GT: '>';
LE: '<=';
GE: '>=';
EQ: '==';
NE: '!=';
AND: '&&';
OR: '||';

// Separators
LPAREN: '(';
RPAREN: ')';
LBRACE: '{';
RBRACE: '}';
COMMA: ',';
SEMI: ';';

WS: [ \t\r\n]+ -> skip;