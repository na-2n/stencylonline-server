#pragma once

#include <cstring>

struct vec2 {
    float x;
    float y;

    static inline vec2 from(char* in)
    {
        vec2 out;

        std::memcpy(&out, in, sizeof(vec2));

        return out;
    }

    inline void write_to(char* out) const
    {
        std::memcpy(out, this, sizeof(vec2));
    }
};

