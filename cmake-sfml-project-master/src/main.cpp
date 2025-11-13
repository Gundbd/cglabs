#include <SFML/Graphics.hpp>
#include "Shape.hpp"
#include "HandleInput.hpp"
#include "BezierCurve.hpp"
#include <iostream>

//TODO: rotation manipulate with handl input + shape.rotate(); 
//TODO: class handleInput depends on the figure in constr, to manipulate, points on Bezier Curve need another class for Handle input? - bad idea;
//TODO: pretty men where you can pick objects: shapes, curves, and it's will draw automaticaly

int main()
{
    try {
        sf::RenderWindow window(sf::VideoMode({800u, 600u}), "My window");
        
        StrangeShape shape;
        shape.resize(200);
        shape.move({400, 300});


        while (window.isOpen())
        {
            while (const std::optional event = window.pollEvent())
            {

                if (event->is<sf::Event::Closed>())
                    window.close();
            } 
                

                window.clear();
                shape.draw(window);
                window.display();
        }

        
    
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;

}