////
//// Created by Tolqinbek Isoqov on 12/3/17.
////
#include "server.h"

int main() {

    struct Server *server = new(Server);
    server_listen(server);
}