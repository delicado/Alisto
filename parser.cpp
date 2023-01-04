#include "parser.h"
#include "utilities.h"

#include <algorithm>
#include <string_view>
#include <iostream>
#include <charconv>

ParserParam* ParserDispatch::GetParam()
{
    return _param;
}

size_t ParserDispatch::GetParamSize() const
{
    return cfg_static_param_size;
}

void Parser::ReadFromMemory(std::string_view in, ParserDispatch& dispatcher)
{
    std::cout << in.size() << std::endl;
    auto delim = std::string_view("\r\n");
    size_t i = 0, j = 0;
    while((j = in.find_first_of(delim, i)) != in.npos ){
        this->ParseLine(in.substr(i, j - i), dispatcher.GetParam(), dispatcher.GetParamSize());
        i = in.find_first_not_of(delim, j);
    }
}

size_t Parser::ParseLine(std::string_view in, ParserParam *param, size_t param_size)
{
    int param_index = 0;
    auto idx = in.data();
    auto end = idx + in.size();
    if(in[0] != ';'){

        while(idx != end) {
            if(param_index == 0){
                param[param_index].type.number = ParseCommand(idx, end, param[param_index].name);
            }
            else
                param[param_index].paramf = ParseParam(idx, end, param[param_index].name);

            idx = NextParam(idx, end);
            param_index++;
        }
        param[0].type.size = param_index;

        std::cout << in << std::endl << "                       ";
        for(int i = 0; i < param_index; ++i){
            std::cout << param[i].name << (i > 0 ? param[i].paramf : float(param[i].type.number)) << ": ";
        }
        std::cout << std::endl;
    }
    return param_index;
}
