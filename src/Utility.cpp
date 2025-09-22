#include "Utility.hpp"

std::pair<int, int> vector(const std::pair<int, int> a, const std::pair<int, int> b){
    return {b.first-a.first, b.second-a.second};
}