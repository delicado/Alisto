#ifndef GENERAL_OBJECT_H
#define GENERAL_OBJECT_H

struct Param {
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

enum OIClassOffset {
};

using Command = int (*)(const Param*);

union GeneralObject {
    struct {
        Command g[500];
        Command m[1000];
    } func_table;
};

#endif // GENERAL_OBJECT_H
