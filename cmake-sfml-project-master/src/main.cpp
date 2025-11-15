#include <SFML/Graphics.hpp>
#include "Shape.hpp"
#include "HandleInput.hpp"
#include "BezierCurve.hpp"
#include <iostream>

//TODO: handling input works damn god wrong 
//TODO: class handleInput depends on the figure in constr, to manipulate, points on Bezier Curve need another class for Handle input? - bad idea;
//TODO: pretty men where you can pick objects: shapes, curves, and it's will draw automaticaly

int main()
{
    try {
        sf::RenderWindow window(sf::VideoMode({800u, 600u}), "My window");
        
        PolygonalShape shape;

        HandleInput input(&shape, &window);

        shape.move({400.f, 300.f});
        shape.resize(100.f);
        shape.rotate(sf::degrees(-10));

        BezierCurve curve;
        curve.setControlPoints({shape.getPoint(0), shape.getPoint(1), shape.getPoint(2)});
        curve.addControlPoint({shape.getPoint(3)});
        curve.addControlPoint({shape.getPoint(4)});
        curve.addControlPoint({ shape.getPoint(5)});
    
        while (window.isOpen())
        {
            while (const std::optional event = window.pollEvent())
            {

                if (event->is<sf::Event::Closed>())
                    window.close();
            } 
                
                std::cout << input.isInside() << std::endl;
                std::cout << input.isUpperCorner() << std::endl;


                int cornerIndex = input.getCornerIndex();
                if(cornerIndex != -1){
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)){
                        if(input.isUpperCorner()){
                            shape.rotate(shape.getAngle() + sf::degrees(1));
                        }
                        else {
                            shape.rotate(shape.getAngle() - sf::degrees(1));
                        }
                    }
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                        if(input.isInside()){
                            shape.resize(shape.getSize() - 1);
                        }
                        else {
                            shape.resize(shape.getSize() + 1);
                        }
                    }
                }



                
                window.clear();
                curve.draw(window);
                shape.draw(window);

                window.display();
        }

        
    
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;

}