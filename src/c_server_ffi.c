#include "c_server_ffi.h"
#include <stdlib.h>

//This is the FFI for C++
struct server_state* init_server_state() {
    foo();
    init_server();
    struct server_state* ret = malloc(sizeof(struct server_state));
    return ret;
}
void drop_server_state(struct server_state* dropped) {
    free(dropped);
    drop_server();
}

