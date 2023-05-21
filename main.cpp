#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "libs/Transceiver.h"
#include "libs/PHYLink.h"
#include "gui/netsim_draw.h"
#include <thread>
#include <chrono>

#define TIMESTEP .010


int main() {

    // Load font
    sf::Font font;
    if (!font.loadFromFile("gui/arial.ttf")) {  
        std::cout << "Could not load font" << std::endl;
    }

    // Random Seed
    srand((unsigned) time(NULL));

    // Create transceivers
    std::vector<Transceiver> transceivers;
    transceivers.push_back(Transceiver(1, 0, 0));
    transceivers.push_back(Transceiver(3, 200, 0));
    transceivers.push_back(Transceiver(1, 200, 200));
    transceivers.push_back(Transceiver(2, 600, 0));
    transceivers.push_back(Transceiver(1, 800, 300));

    // Create links between transceivers
    std::vector<PHYLink> links;
    links.push_back(PHYLink(true, 20, 0, transceivers[0], transceivers[1]));
    links.push_back(PHYLink(true, 10, 0, transceivers[1], transceivers[2]));
    links.push_back(PHYLink(true, 5, 0, transceivers[1], transceivers[3]));
    links.push_back(PHYLink(true, 50, 0, transceivers[3], transceivers[4]));
    

    // Connect the links to transceivers
    transceivers[0].connect_link(&links[0], PortType::TX);
    transceivers[1].connect_link(&links[0], PortType::RX);

    transceivers[1].connect_link(&links[1], PortType::TX);
    transceivers[2].connect_link(&links[1], PortType::RX);

    transceivers[1].connect_link(&links[2], PortType::TX);
    transceivers[3].connect_link(&links[2], PortType::RX);

    transceivers[3].connect_link(&links[3], PortType::TX);
    transceivers[4].connect_link(&links[3], PortType::RX);


    int8_t tempval;

    // Render Window
    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML GUI");
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(100, 100));

    int temp1=0, temp2=0;
    unsigned long int time = 0;
    while (window.isOpen()) {
        std::this_thread::sleep_for(std::chrono::milliseconds((int)(TIMESTEP*1000)));
        

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        
        window.clear(sf::Color::White);
        int id=0;
        for (auto &transceiver : transceivers) {
            temp2=temp1=0;
            for (auto port : transceiver.ports){
                if (id==0){
                transceiver.push_to_port(port.portnumber, 1);
                transceiver.read_from_port(port.portnumber);
                } else {
                temp1 = transceiver.read_from_port(port.portnumber);
                if (temp1!=0){
                    temp2=temp1;
                }
                transceiver.push_to_port(port.portnumber, temp2);
                }

            }
            drawTransceiver(window, transceiver, id, font); id++;
        }

        id=0;
        for (auto &link : links) {
            link.updateAnimation(TIMESTEP);
            drawPHYLink(window, link, id); id++;
        }

        window.display();
        time++;
    }

    return 0;
}
