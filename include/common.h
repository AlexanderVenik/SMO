#ifndef SMO_COMMON_H
#define SMO_COMMON_H

#include "types.h"

namespace math {

template <typename T>
T factorial(T n) {
  if (n < 2) {
    return n;
  }
  return !n ? 1 : n * factorial(n - 1);
}

}  // namespace math

#endif  //SMO_COMMON_H
