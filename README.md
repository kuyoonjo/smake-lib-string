# C++ string tools
```c++
#include <array>
#include <cassert>
#include <ex/string.h>
#include <iostream>
#include <regex>
#include <string>
#include <tuple>
#include <vector>

int main() {
  std::string s1 = "  abc de fg ";
  std::string s2 = "  abc de fg ";
  std::string s3 = "  abc de fg ";
  ex::string::trim_start(s1);
  ex::string::trim_end(s2);
  ex::string::trim(s3);
  assert(s1 == "abc de fg ");
  assert(s2 == "  abc de fg");
  assert(s3 == "abc de fg");

  ex::string::replace(s1, "abc", "");
  assert(s1 == " de fg ");

  auto v1 = ex::string::split(s1, ' ');
  assert(v1.size() == 4);
  assert(v1[0] == "");
  assert(v1[1] == "de");
  assert(v1[2] == "fg");
  assert(v1[3] == "");

  ex::string::trim(s1);
  assert(ex::string::match(s1, "^d.*g$"));

  std::string s4 = "de 3dy de";
  assert(ex::string::starts_with(s4, "d"));
  assert(ex::string::starts_with(s4, "de"));
  assert(ex::string::ends_with(s4, "dy de"));
  assert(ex::string::ends_with(s4, "e"));

  ex::string::to_upper_case(s4);
  assert(s4 == "DE 3DY DE");
  ex::string::to_lower_case(s4);
  assert(s4 == "de 3dy de");

  ex::string::pad_start(s4, 12, '-');
  assert(s4 == "---de 3dy de");
  ex::string::pad_end(s4, 15, '!');
  assert(s4 == "---de 3dy de!!!");

  std::vector v2{0, 1, 2};
  auto s5 = ex::string::join(v2.begin(), v2.end(), "-");
  assert(s5 == "0-1-2");
  const char* v3[] = {"1", "2", "ss"};
  auto s6 = ex::string::join(v3, v3 + 3, ":");
  assert(s6 == "1:2:ss");
  std::array<char, 3> v4{'1', '2', 's'};
  auto s7 = ex::string::join(v4.begin(), v4.end(), "/");
  assert(s7 == "1/2/s");
  auto s8 = ex::string::join(std::make_tuple(1, 2, "xx"), "/");
  assert(s8 == "1/2/xx");

  std::cout << "pass!" << std::endl;
  return 0;
}
```