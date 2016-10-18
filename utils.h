#ifndef _UTILS_H_
#define _UTILS_H_
#include <string>

namespace utils {
bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
}

#endif /* _UTILS_H_ */
