grammar ToyC;               // 定义文法的名字

compUnit: funcDef+;

funcDef: (INT | VOID) ID LPAREN (param (COMMA param)*)? RPAREN block;

param: INT ID;

stmt: block                             # BlockStmt
    | SEMI                              # EmptyStmt
    | expr SEMI                         # ExprStmt
    | ID ASSIGN expr SEMI               # AssignStmt
    | INT ID ASSIGN expr SEMI           # DeclStmt
    | IF LPAREN expr RPAREN stmt (ELSE stmt)?  # IfStmt
    | WHILE LPAREN expr RPAREN stmt     # WhileStmt
    | BREAK SEMI                        # BreakStmt
    | CONTINUE SEMI                     # ContinueStmt
    | RETURN expr? SEMI                  # ReturnStmt
    ;

block: LBRACE stmt* RBRACE;

expr: lOrExpr;

lOrExpr: lAndExpr                 # SingleLOr
       | lOrExpr OR lAndExpr      # mulLOrExpr
       ;

lAndExpr: relExpr                 # SingleLAnd
        | lAndExpr AND relExpr    # mulLAndExpr
        ;

relExpr: addExpr                            # SingleRel
       | relExpr (LT | GT | LE | GE | EQ | NE) addExpr  # mulRelExpr
       ;

addExpr: mulExpr                     # SingleAdd
       | addExpr (ADD | SUB) mulExpr  # mulAddExpr
       ;

mulExpr: unaryExpr                     # SingleMul
       | mulExpr (MUL | DIV | MOD) unaryExpr  # mulMulExpr
       ;

unaryExpr: primaryExpr              # SingleUnary
         | (ADD | SUB | NOT) unaryExpr  # mulUnaryOp
         ;

primaryExpr: ID                          # Identifier
           | NUMBER                      # NumberLiteral
           | LPAREN expr RPAREN          # ParenthesizedExpr
           | ID LPAREN (expr (COMMA expr)*)? RPAREN  # FunctionCall
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

OR: '||';
AND: '&&';
LT: '<';
GT: '>';
LE: '<=';
GE: '>=';
EQ: '==';
NE: '!=';
ADD: '+';
SUB: '-';
MUL: '*';
DIV: '/';
MOD: '%';
NOT: '!';
ASSIGN: '=';
SEMI: ';';
COMMA: ',';
LPAREN: '(';
RPAREN: ')';
LBRACE: '{';
RBRACE: '}';

ID: [a-zA-Z_][a-zA-Z0-9_]*;//标识符
//NUMBER: '-'? ('0' | [1-9][0-9]*);//整数
NUMBER: '0' | [1-9][0-9]*;//非负整数，负号做一元运算符
LINE_COMMENT : '//' ~[\r\n]* -> skip;//单行注释
COMMENT : '/*' .*? '*/' -> skip;//多行注释
WS: [ \t\r\n]+ -> skip;//空格