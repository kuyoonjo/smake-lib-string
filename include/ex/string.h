#pragma once

#include <cctype>
#include <cstring>
#include <functional>
#include <numeric>
#include <regex>
#include <sstream>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

namespace ex {
namespace string {
// trim from start (in place)
inline void trim_start(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
          }));
}

// trim from end (in place)
inline void trim_end(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       [](unsigned char ch) { return !std::isspace(ch); })
              .base(),
          s.end());
}

// trim from both ends (in place)
inline void trim(std::string &s) {
  trim_start(s);
  trim_end(s);
}

inline std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> r;
  auto send = s.end();
  for (auto p = s.begin();; ++p) {
    auto q = p;
    p = std::find(p, send, delim);
    r.emplace_back(q, p);
    if (p == send)
      return r;
  }
}

inline std::vector<std::string> split(const std::string &s,
                                             const std::string &regex) {
  std::regex reg(regex);
  return {std::sregex_token_iterator(s.begin(), s.end(), reg, -1),
          std::sregex_token_iterator()};
}

template <typename... Args>
inline void replace(std::string &s, const std::string &regex,
                           Args &&...args) {
  s = std::regex_replace(s, std::regex(regex), std::forward<Args>(args)...);
}

template <typename... Args>
inline bool match(const std::string &s, const std::string &regex,
                         Args &&...args) {
  return std::regex_match(s, std::regex(regex), std::forward<Args>(args)...);
}

inline size_t strlen(const char *str) { return ::strlen(str); }
inline size_t strlen(char c) { return 1; }
inline size_t strlen(const std::string &s) { return s.size(); }

inline bool starts_with(const std::string &s,
                               const std::string &prefix) {
  return s.rfind(prefix, 0) == 0;
}

inline bool ends_with(const std::string &s, const std::string &suffix) {
  auto s_len = s.size();
  auto suf_len = suffix.size();
  if (s_len >= suf_len) {
    return (0 == s.compare(s_len - suf_len, suf_len, suffix));
  } else {
    return false;
  }
}

inline void to_lower_case(std::string &s) {
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::tolower(c); });
}

inline void to_upper_case(std::string &s) {
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::toupper(c); });
}

inline void pad_start(std::string &s, size_t target_size, char c) {
  auto len = s.size();
  if (target_size > len) {
    s.insert(s.begin(), target_size - len, c);
  }
}

inline void pad_end(std::string &s, size_t target_size, char c) {
  auto len = s.size();
  if (target_size > len) {
    s.insert(s.end(), target_size - len, c);
  }
}

inline std::string to_string(const char c) {
  std::string s;
  s.append(1, c);
  return s;
}

inline std::string to_string(const char *str) { return str; }

inline std::string to_string(const std::string &t) {
  return t;
}

template <typename T> inline std::string to_string(const T &t) {
  return std::to_string(t);
}

template<class InputIterator>
inline std::string join(InputIterator first, const InputIterator last, const std::string &sep) {
  auto second = std::next(first);
  if (first + 1 != last) {
    return std::accumulate(second, last, to_string(*first),
                           [&sep](std::string a, auto b) {
                             return std::move(a) + sep + to_string(b);
                           });
  } else {
    return to_string(*first);
  }
}

template <typename... ARGS>
const inline std::string join(const std::tuple<ARGS...> t,
                                     const std::string &sep) {
  auto s = sizeof...(ARGS);

  if (s > 1) {
    std::string a;
    std::apply(
        [&a, &sep](auto const &...b) {
          size_t i = 0;
          a = a + (((i++ > 0 ? sep : "") + to_string(b)) + ...);
        },
        t);
    return a;
  } else {
    return to_string(std::get<0>(t));
  }
}

} // namespace string
} // namespace ex