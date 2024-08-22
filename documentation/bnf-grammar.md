# BNF Grammar for LambdaMia

```
<prog>               := <list-statement> '$'
<list-statement>     := <list-statement> ';' <statement>
                      | <statement>
<statement>          := <lambda-declaration>
                      | <lambda-expression>
<lambda-declaration> := <lambda-var> '=' <lambda-expression>

<lambda-expression>  := <lambda-application>
                      | <lambda-term>

<lambda-term>        := '\' <list-var> '.' <lambda-term>
                      | <if-expression>
                      | <let-expression>
                      | <list-construction>
                      | <lambda-var>
                      | <var>
                      | <literal>
                      | '(' <lambda-expression> ')'


<lambda-application> := <lambda-application> <lambda-term>
                      | <lambda-term>

<if-expression>      := 'if' <lambda-expression> 'then' <lambda-expression> 'else' <lambda-expression>

<let-expression>     := 'let' <list-declaration> 'in' <lambda-expression>

<list-declaration>   := <list-declaration> ',' <lambda-declaration>
                      | <lambda-declaration>

<list-construction>  := <lambda-expression> ':' <lambda-expression>

<literal>            := <character>
                      | <integer>
                      | <float>
                      | <list-literal>

<list-literal>       := '[' <list-elements> ']'
<list-elements>      := <lambda-expression>
                      | <list-elements> ',' <lambda-expression>      // Type analysis: all literals should have same type

<list-var>           := <var>
                      | <list-var> <var>

<var>                := <id-var>
<lambda-var>         := <id-lambda-var>

// Terminal symbols

<id-var>        := [a-z][a-zA-Z0-9_]*
<id-lambda-var> := [A-Z][a-zA-Z0-9_]*
<character>     := '[^']'
<integer>       := -?\d+
<float>         := -?\d+\.\d+

```
