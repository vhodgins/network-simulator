#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "libs/Transceiver.h"
#include "libs/PHYLink.h"
#include "gui/netsim_draw.h"

int main() {

    // Load font
    sf::Font font;
    if (!font.loadFromFile("gui/arial.ttf")) {  
        std::cout << "Could not load font" << std::endl;
    }


    // Create transceivers
    std::vector<Transceiver> transceivers;
    transceivers.push_back(Transceiver(1, 0, 0));
    transceivers.push_back(Transceiver(2, 100, 0));
    transceivers.push_back(Transceiver(1, 100, 200));

    // Create links between transceivers
    std::vector<PHYLink> links;
    links.push_back(PHYLink(true, 1, 0, transceivers[0], transceivers[1]));
    links.push_back(PHYLink(true, 1, 0, transceivers[1], transceivers[2]));

    // Connect the links to transceivers
    transceivers[0].connect_link(&links[0], PortType::TX);
    transceivers[1].connect_link(&links[0], PortType::RX);
    transceivers[1].connect_link(&links[1], PortType::TX);
    transceivers[2].connect_link(&links[1], PortType::RX);

    // Render Window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML GUI");
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(100, 100));

    unsigned long int time = 0;
    while (window.isOpen()) {
        











        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        int id=0;
        for (const auto &transceiver : transceivers) {
            drawTransceiver(window, transceiver, id, font); id++;
        }

        id=0;
        for (const auto &link : links) {
            drawPHYLink(window, link, id); id++;
        }

        window.display();
    }

    return 0;
}
