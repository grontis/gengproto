#pragma once

#include <functional>

struct Coordinate
{
    int x;
    int y;

    bool operator==(const Coordinate &other) const
    {
        return x == other.x && y == other.y;
    }
};

// Custom hash function for Coordinate struct
namespace std
{
    template <>
    struct hash<Coordinate>
    {
        std::size_t operator()(const Coordinate &coord) const
        {
            return std::hash<int>()(coord.x) ^ (std::hash<int>()(coord.y) << 1);
        }
    };
}