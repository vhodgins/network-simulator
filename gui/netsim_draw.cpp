#include "netsim_draw.h"

#define XBIAS 200
#define YBIAS 200
#define YLINEBIAS 10

void drawTransceiver(sf::RenderWindow& window, const Transceiver& transceiver){
    sf::RectangleShape rectangle(sf::Vector2f(30,20));     // Create a RectangleShape class object from the sf library called rectangle
    rectangle.setPosition(sf::Vector2f(transceiver.xcoord+XBIAS, transceiver.ycoord+YBIAS));
    rectangle.setFillColor(sf::Color::Black);
    window.draw(rectangle);

}

void drawPHYLink(sf::RenderWindow& window, const PHYLink& phyLink){
    sf::Vertex line[] = {
            {{phyLink.coords[0]+XBIAS, phyLink.coords[2]+YBIAS+YLINEBIAS}, sf::Color::Black},
            {{phyLink.coords[1]+XBIAS, phyLink.coords[3]+YBIAS+YLINEBIAS}, sf::Color::Black}};
    window.draw(line, 2, sf::Lines);
}