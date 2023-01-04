#ifndef PARSER_H
#define PARSER_H
#include "config.h"

#include <cstdint>
#include <string_view>

struct ParserParam {
    char name;
    union {
        struct {
            uint16_t  number;
            uint8_t  size;
        } type;
        int parami;
        float paramf;
    };
};

class ParserDispatch {
protected:
    ParserParam _param[cfg_static_param_size];

    ParserParam* GetParam();
    size_t GetParamSize() const;
public:


    friend class Parser;
};

class Parser
{
public:
    Parser() = default;

    void ReadFromMemory(std::string_view in, ParserDispatch &dispatcher);
    size_t ParseLine(std::string_view in, ParserParam* param, size_t param_size);
};

#endif // PARSER_H
