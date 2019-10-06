#include <iostream>
#include <zmq.hpp>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
    void *context = zmq_init (1);
    void *xsub = zmq_socket(context, ZMQ_XSUB);
    zmq_bind(xsub, "tcp://*:31337");

    void *xpub = zmq_socket(context, ZMQ_XPUB);
    zmq_bind(xpub, "tcp://*:31338");

    zmq_proxy(xsub, xpub, NULL);

    zmq_close(xsub);
    zmq_close(xpub);
    zmq_ctx_destroy(context);

    system("pause");

    return 0;
};