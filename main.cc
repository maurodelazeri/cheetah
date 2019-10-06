#include <chrono>
#include <iostream>
#include <thread>
#include <zmq.hpp>
#include <unistd.h>
#include <future>
#include <functional>
#include "Monitor.h"

using namespace std;

void doMonitor(Monitor &monitor, zmq::socket_t &socket, std::string &addr) {
    std::cout << "start" << std::endl;
    monitor.monitor(socket, addr, ZMQ_EVENT_ALL);
}

int main (int argc, char *argv[])
{
    std::unique_ptr<Monitor> monitor_front_;
    std::unique_ptr<Monitor> monitor_back_;

    zmq::context_t context;
    zmq::socket_t front(context, ZMQ_XSUB);
    zmq::socket_t back(context, ZMQ_XPUB);
    zmq::socket_t capture(context, ZMQ_XSUB);
    front.bind("tcp://*:31337");
    back.bind("tcp://*:31338");
    capture.bind("tcp://*:31339");

    auto f = std::async(std::launch::async, [&]() {
        auto s1 = std::move(front);
        auto s2 = std::move(back);
        auto s3 = std::move(capture);

        {
            monitor_front_ = make_unique<Monitor>();
            std::string addr = "inproc://monitor.front";
            std::thread thr = std::thread(std::bind(doMonitor, std::ref(*monitor_front_), std::ref(s1), addr));
            thr.detach();
        }

        {
            monitor_back_ = make_unique<Monitor>();
            std::string addr = "inproc://monitor.back";
            std::thread thr = std::thread(std::bind(doMonitor, std::ref(*monitor_back_), std::ref(s2),addr));
            thr.detach();
        }

        try
        {
            zmq::proxy(s1, s2, zmq::socket_ref(s3));
        }
        catch (const zmq::error_t& e)
        {
            return e.num() == ETERM;
        }
        return false;
    });

    sleep(10000);
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