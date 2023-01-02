#include "utilities.h"
#include <algorithm>
#include <iostream>

static const char* delim_line = "\r\n";
static const char* delim_param = " \r\n";

size_t ParseCommand(const char*& index, const char* end, char& command)
{
    size_t ret = 0;
    command = *index;
    ret = ToInteger<char, size_t>( index + 1, end, &index );
    return ret;
}

float ParseParam(const char *&index, const char *end, char& axis)
{
    float ret = 0.0f;
    axis = *index;
    ret = ToDouble<char, float>( index + 1, end, &index );
    return ret;
}

const char *NextParam(const char *index, const char *end)
{
    auto ret = WalkStringUntilNotOf(index, end, delim_param, delim_param + 3);
    if(*ret == ';')
        ret = end;
    return ret;
}
