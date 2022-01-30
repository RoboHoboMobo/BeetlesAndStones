/*
  The Beetles and stones.

  Beetles don't like to be near each other and everyone hides under a separate stone and
  tries to choose stones as far away from their neighbors as possible. Bugs also like to
  be as far away from the edge as possible. Once the beetle has sat down behind a rock,
  it no longer moves. There are X stones in total in the line. And there Y beetles
  consistently run to hide. Find how many vacant stones will be on the left and right
  of the last beetle.

  Жуки не любят находиться рядом друг с другом и каждый прячется под отдельным камнем и
  старается выбирать камни, максимально удаленные от соседей. Так же жуки любят
  находится максимально далеко от края. Как только жук сел за камень, он более не
  перемещается. Всего в линии лежат X камней. И туда последовательно бежит прятаться
  Y жуков. Найти сколько свободных камней будет слева и справа от последнего жука.

  The idea of algorithm:
  1. Stone line can be considered as segment. Each hidden beetle divides each segment in
  two (almost) equal ones.
  2. Beetle divides even segmet in two so that the smaller segment is on the left side.
  3. Acc. p.1 the initial segment (length == x) can be divided in m == 2^h (h == 0, ...)
  (almost) equal segments by b == m - 1 hidden beetles.
  4. If number of all beetles is y, then: h == (int)log2(y).
  5. Minimal length of each segment is: lmin == (int)((x - b) / m).
  6. There can be several segments longer lmin by 1: k == x - (b + m * lmin).
  7. Exposed beetles: eb = y - b.
  8. Because beetles prefer longer segment k-segments will be picked at first:
  eb <= k ? pick(lmin + 1) : pick(lmin).
  9. If h >= (int)log2(x) then length of each segment is:
  (int)(x/h^2) < 2, e.g. segment length == 0 || 1 => return [0, 0].
  10. The case y == 1 must be considered individually.
*/

#include <iostream>

#include <utility>
#include <cmath>

std::pair<size_t, size_t> func(size_t x, size_t y)
{
  if (y > x)
    return {0, 0};

  auto pick = [](size_t segment) {
    return std::make_pair((segment - 1) / 2, ceil((segment - 1) / 2.0));
  };

  if (y == 1)
    return pick(x);

  const size_t h = std::log2(y); // Height of BST
  const size_t m = pow(2, h);    // Number of segments
  const size_t b = m - 1;        // Number of hidden beetles

  if (h == (size_t)(std::log2(x))) // All remaining segment are too short
    return {0, 0};

  const size_t lmin = (x - b) / m;   // Minimal length of segment
  const size_t k = x - b - m * lmin; // Number of segments longer than lmin
  const size_t eb = y - b;           // Beetles that must be hidden

  return eb <= k ? pick(lmin + 1) : pick(lmin);
}

int main()
{
  auto print = [](std::pair<size_t, size_t> value) {
    std::cout << "left: " << value.first << "\t" <<
                 "right: " << value.second << std::endl;
  };

  size_t n = 1000;
  for (size_t i = 1; i <= n; ++i) {
    auto result = func(n, i);
    
    std::cout << "Beetles: " << i << "\t";
    print(result);
  }

  std::cout << "\nLarge numbers test" << std::endl;
  std::cout << "Stones: 1000000001\tBeetles: 123456789\t";
  print(func(1000000001, 123456789));

  return 0;
}
