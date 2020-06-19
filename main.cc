#include <iostream>
#include <thread>
#include <zmq.hpp>
#include "Monitor.h"

using namespace std;

int main(int argc, char *argv[]) {
    try {
        std::unique_ptr<Monitor> monitor_front_;
        std::unique_ptr<Monitor> monitor_back_;

        zmq::context_t context;
        zmq::socket_t front(context, ZMQ_XSUB);
        zmq::socket_t back(context, ZMQ_XPUB);
        front.bind("tcp://*:31337");
        back.bind("tcp://*:31338");
        {
            std::thread thr([&front = front](){
                std::string addr = "inproc://monitor.front";
                std::cout << "start monitor " << addr << std::endl;
                std::unique_ptr<Monitor> monitor_front_ = make_unique<Monitor>();
                monitor_front_->monitor(front, addr, ZMQ_EVENT_ALL);
            });
            thr.detach();
        }

        {
            std::thread thr([&back = back](){
                std::string addr = "inproc://monitor.back";
                std::cout << "start monitor " << addr << std::endl;
                std::unique_ptr<Monitor> monitor_back_ = make_unique<Monitor>();
                monitor_back_->monitor(back, addr, ZMQ_EVENT_ALL);
            });
            thr.detach();
        }
        zmq::proxy(front, back);

    }
    catch (const zmq::error_t &e) {
        return e.num() == ETERM;
    }

    return 0;
}