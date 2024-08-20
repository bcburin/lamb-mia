# BNF Grammar for LambdaMia

```
<prog>               := <list-statement> '$'
<list-statement>     := <list-statement> ';' <statement>
                      | <statement>
<statement>          := <lambda-declaration>
                      | <lambda-expression>
<lambda-declaration> := <lambda-var> '=' <lambda-expression>

<lambda-expression>  := <lambda-application>
                      | <if-expression>
                      | <list-construction>
                      | <literal>

<lambda-application> := <lambda-term> <list-lambda-params>

<lambda-term>        := '\' <list-var> '.' <lambda-expression>
                      | <lambda-var>
                      | '(' <lambda-expression> ')'
                      | <literal>

<list-lambda-params> := <list-lambda-params> <lambda-term>
                      | <lambda-term>

<if-expression>      := 'if' <lambda-expression> 'then' <lambda-expression> 'else' <lambda-expression>

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
