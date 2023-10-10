# fmt_fails_with_enum
Short reproducible example of how printing enums with fmt sometimes can fail with version 10 of {fmt} (tested with 10.1.1 and 10.1.0), works with version 9.1.0. This is especially relevant for printing number of rows of a Dune vector.

Note that also using `static constexpr``` works:

```C++
template<int ROWS, int COLS>
struct FieldMatrixModernCPP {
      //! The number of rows.
  static constexpr int rows = ROWS;
      //! The number of columns.
  static constexpr int cols = COLS;
};
```
hence it seems to be an issue with the anonymous `enum`.

Compile with

```g++ -I/fmt/include /fmt/library.a src/main.cpp```


Example output from g++-13.2.1 (similar results hold for clang, and g++-11):

```bash
$ g++ -I/fmtinstall10111/include/ src/main.cpp  /fmtinstall10111/lib/libfmt.a 
In file included from /fmtinstall10111/include/fmt/format.h:49,
                 from src/main.cpp:1:
/fmtinstall10111/include/fmt/core.h: In instantiation of ‘constexpr fmt::v10::detail::value<Context> fmt::v10::detail::make_arg(T&) [with bool PACKED = true; Context = fmt::v10::basic_format_context<fmt::v10::appender, char>; T = FieldMatrix<1, 1>::<unnamed enum>; typename std::enable_if<PACKED, int>::type <anonymous> = 0]’:
/fmtinstall10111/include/fmt/core.h:1808:51:   required from ‘constexpr fmt::v10::format_arg_store<Context, Args>::format_arg_store(T& ...) [with T = {FieldMatrix<1, 1>::<unnamed enum>}; Context = fmt::v10::basic_format_context<fmt::v10::appender, char>; Args = {FieldMatrix<1, 1>::<unnamed enum>}]’
/fmtinstall10111/include/fmt/core.h:1826:18:   required from ‘constexpr fmt::v10::format_arg_store<Context, typename std::remove_cv<typename std::remove_reference<T>::type>::type ...> fmt::v10::make_format_args(T& ...) [with Context = basic_format_context<appender, char>; T = {FieldMatrix<1, 1>::<unnamed enum>}]’
/fmtinstall10111/include/fmt/core.h:2788:44:   required from ‘std::string fmt::v10::format(format_string<T ...>, T&& ...) [with T = {FieldMatrix<1, 1>::<unnamed enum>}; std::string = std::__cxx11::basic_string<char>; format_string<T ...> = basic_format_string<char, FieldMatrix<1, 1>::<unnamed enum> >]’
src/main.cpp:36:27:   required from ‘void printmatrixdoesnotcompile(const Matrix&) [with Matrix = BlockMatrix<FieldMatrix<1, 1> >]’
src/main.cpp:43:28:   required from here
/fmtinstall10111/include/fmt/core.h:1576:63: error: ‘fmt::v10::detail::type_is_unformattable_for<FieldMatrix<1, 1>::<unnamed enum>, char> _’ has incomplete type
 1576 |     type_is_unformattable_for<T, typename Context::char_type> _;
      |                                                               ^
/fmtinstall10111/include/fmt/core.h:1580:7: error: static assertion failed: Cannot format an argument. To make type T formattable provide a formatter<T> specialization: https://fmt.dev/latest/api.html#udt
 1580 |       formattable,
      |       ^~~~~~~~~~~
/fmtinstall10111/include/fmt/core.h:1580:7: note: ‘formattable’ evaluates to false

```