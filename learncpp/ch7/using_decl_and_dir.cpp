/*
`using` directives allows all identifiers in a given namespace to be referenced without qualification from the scope of
the using-directive.
`using` declarations allows to use an unqualified name (with no scope) as an alias for a qualified name.

Declarations, such as using std::cout is OK to use in cpp files after #includes.
using declarations shadow identifers with the same names, directives don't - compiler will throw an ambiguity error

Directives, such as "using namespace std;" are better avoided, except for "using namespace std::literals;" ...
using declarations are OK to use but not in headers and namespaces (especially in global)

If dir or decl are used withing a block, they have a block scope. If used in global namespace, they have a file scope.
*/
