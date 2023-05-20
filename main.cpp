#include <iostream>
#include <SFML/Graphics.hpp>
#include "libs/Transceiver.h"
#include "libs/PHYLink.h"
#include "gui/netsim_draw.h"


int main() {
    // Create two transceivers
    Transceiver t1(1, 0, 0);
    Transceiver t2(2, 100, 0);
    Transceiver t3(2, 100, 200);

    // Create a link between transceivers
    PHYLink link(true, 1, 0, t1, t2);
    PHYLink link1(true, 1, 0, t2, t3);
    

    // Connect the link to transceivers
    t1.connect_link(&link, PortType::TX);
    t2.connect_link(&link, PortType::RX);
    t2.connect_link(&link1, PortType::TX);
    t3.connect_link(&link1, PortType::RX);
    

    // Render Window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML GUI");
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(100, 100));


    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

        window.clear(sf::Color::White);
        drawTransceiver(window, t1);
        drawTransceiver(window, t2);
        drawTransceiver(window, t3);
        drawPHYLink(window, link);
        drawPHYLink(window, link1);
        window.display();
    }



    return 0;
}
