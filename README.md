# fmt_fails_with_enum
Short reproducible example of how printing enums with fmt sometimes can fail. This is especially relevant for printing number of rows of a Dune vector.

Compile with

```g++ -I/fmt/include /fmt/library.a src/main.cpp```
