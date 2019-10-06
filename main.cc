#include <iostream>
#include <thread>
#include <zmq.hpp>
#include <functional>
#include "Monitor.h"

using namespace std;

void doMonitor(Monitor &monitor, zmq::socket_t &socket, std::string &addr) {
    std::cout << "start" << std::endl;
    monitor.monitor(socket, addr, ZMQ_EVENT_ALL);
}

int main(int argc, char *argv[]) {
    try {
        std::unique_ptr<Monitor> monitor_front_;
        std::unique_ptr<Monitor> monitor_back_;

        zmq::context_t context;
        zmq::socket_t front(context, ZMQ_XSUB);
        zmq::socket_t back(context, ZMQ_XPUB);
        //zmq::socket_t capture(context, ZMQ_XSUB);
        front.bind("tcp://*:31337");
        back.bind("tcp://*:31338");
        // capture.bind("tcp://*:31339");

        {
            monitor_front_ = make_unique<Monitor>();
            std::string addr = "inproc://monitor.front";
            std::thread thr = std::thread(std::bind(doMonitor, std::ref(*monitor_front_), std::ref(front), addr));
            thr.detach();
        }

        {
            monitor_back_ = make_unique<Monitor>();
            std::string addr = "inproc://monitor.back";
            std::thread thr = std::thread(std::bind(doMonitor, std::ref(*monitor_back_), std::ref(back), addr));
            thr.detach();
        }

        //zmq::proxy(front, back, zmq::socket_ref(capture));
        zmq::proxy(front, back, nullptr);

    }
    catch (const zmq::error_t &e) {
        return e.num() == ETERM;
    }

    return 0;
}

//int main(int argc, char *argv[])
//{
//    void *context = zmq_init (1);
//    void *xsub = zmq_socket(context, ZMQ_XSUB);
//    zmq_bind(xsub, "tcp://*:31337");
//
//    void *xpub = zmq_socket(context, ZMQ_XPUB);
//    zmq_bind(xpub, "tcp://*:31338");
//
//    zmq_proxy(xsub, xpub, NULL);
//
//    zmq_close(xsub);
//    zmq_close(xpub);
//    zmq_ctx_destroy(context);
//
//    system("pause");
//
//    return 0;
//};