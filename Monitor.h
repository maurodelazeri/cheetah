//
// Created by mauro on 10/6/19.
//

#pragma once
#include <zmq.hpp>
#include <iostream>
#include <thread>
#include "dbg.h"

class Monitor : zmq::monitor_t {
public:
    Monitor();
public:
public:
    void monitor(zmq::socket_t &socket, std::string const& addr, int events = ZMQ_EVENT_ALL) {
        zmq::monitor_t::monitor(socket, addr, events);
    }

    void on_monitor_started() { std::cout << "monitor start" << std::endl; }
        inline void on_event_connected(const zmq_event_t &event_, const char* addr_) { std::cout << "on_event_connected" << addr_ << std::endl; }
    inline void on_event_connect_delayed(const zmq_event_t &event_, const char* addr_) { std::cout << "on_event_connect_delayed" << addr_ << std::endl; }
    inline void on_event_connect_retried(const zmq_event_t &event_, const char* addr_) { std::cout << "on_event_connect_retried" << addr_ << std::endl; }
    inline void on_event_listening(const zmq_event_t &event_, const char* addr_){ std::cout << "on_event_listening" << addr_ << std::endl; }
    inline void on_event_bind_failed(const zmq_event_t &event_, const char* addr_) { std::cout << "on_event_bind_failed" << addr_ << std::endl; }
    inline void on_event_accepted(const zmq_event_t &event_, const char* addr_) { std::cout << "on_event_accepted" << addr_ << std::endl; }
    inline void on_event_accept_failed(const zmq_event_t &event_, const char* addr_) { std::cout << "on_event_accept_failed" << addr_ << std::endl; }
    inline void on_event_closed(const zmq_event_t &event_, const char* addr_) { std::cout << "on_event_closed" << addr_ << std::endl; }
    inline void on_event_close_failed(const zmq_event_t &event_, const char* addr_) { std::cout << "on_event_close_failed" << addr_ << std::endl; }
    inline void on_event_disconnected(const zmq_event_t &event_, const char* addr_) { std::cout << "on_event_disconnected" << addr_ << std::endl; }
    inline void on_event_unknown(const zmq_event_t &event_, const char* addr_) override { std::cout << "on_event_unknown" << addr_ << std::endl; }

};