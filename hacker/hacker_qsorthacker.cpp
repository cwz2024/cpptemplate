// Hacking quicksort solutions during competitions
// The code belongs to Halyavin (CF handle).

#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <cstdint>
#include <numeric>

std::vector<int> anti_sort(size_t n) // 2n + 1
{
    std::vector<int> res(2 * n + 1);
    std::iota(res.begin(), res.end(), 0);
    for (size_t i = n; i-- > 0;)
    {
        std::swap(res[2 * i + 1], res[i + n]);
    }
    return res;
}

void genB(std::ostream &out)
{
    std::vector<int> gen = anti_sort(124500);
    int n = gen.size();
    out << n << std::endl;
    for (int i = 0; i < n; i++)
    {
        if (i > 0)
        {
            out << " ";
        }
        out << gen[i] + 1;
    }
    out << std::endl;
}

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
    freopen("1.out", "w", stdout);
    genB(std::cout);
    return 0;
}
