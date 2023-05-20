// Transceiver.cpp

#include "Transceiver.h"
#include "PHYLink.h"
#include <stdexcept>

Transceiver::Transceiver(uint8_t n, int x, int y) : xcoord(x), ycoord(y) {
    for (uint8_t i = 0; i < n; i++) {
        Port port;
        port.portnumber = i;
        ports.push_back(port);
    }
}

void Transceiver::connect_link(PHYLink* link, PortType type) {
    for (Port& port : ports) {
        if (port.type == PortType::EMPTY) {
            port.link = link;
            port.type = type;
            return;
        }
    }
    throw std::runtime_error("All ports are occupied");
}

void Transceiver::disconnect_port(uint8_t portnum) {
    if (portnum < ports.size()) {
        ports[portnum].link = nullptr;
        ports[portnum].type = PortType::EMPTY;
    }
    else {
        throw std::out_of_range("Invalid port number");
    }
}

void Transceiver::push_to_port(uint8_t portnum, int8_t dataval) {
    if (portnum < ports.size()) {
        if (ports[portnum].link != nullptr) {
            ports[portnum].link->push_to_end(ports[portnum].type, dataval);
        }
        else {
            throw std::runtime_error("Port is not connected or not a transmit port");
        }
    }
    else {
        throw std::out_of_range("Invalid port number");
    }
}

int8_t Transceiver::read_from_port(uint8_t portnum) {
    if (portnum < ports.size()) {
        if (ports[portnum].link != nullptr) {
            return ports[portnum].link->pop_from_end(ports[portnum].type);
        }
        else {
            throw std::runtime_error("Port is not connected or not a receive port");
        }
    }
    else {
        throw std::out_of_range("Invalid port number");
    }
}

int8_t Transceiver::port_read(uint8_t portnum) const{
    if (portnum < ports.size()) {
        if (ports[portnum].link != nullptr) {
            return ports[portnum].link->read_from_end(ports[portnum].type);
        }
        else {
            throw std::runtime_error("Port is not connected or not a receive port");
        }
    }
    else {
        throw std::out_of_range("Invalid port number");
    }
}