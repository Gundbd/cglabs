#include <SFML\Graphics.hpp>

class HandleInput {
private:

    Shape* m_shape;
    sf::RenderWindow* m_window;

public:

    HandleInput(Shape* shape, sf::RenderWindow* window) : m_shape(shape), m_window(window) {}

    bool isOnBottom(){
        float y_bottom = m_shape->getPosition().y + (m_shape->getSize() / 2);
        float x_shapeRight = m_shape->getPosition().x + (m_shape->getSize() / 2);
        float x_shapeLeft = m_shape->getPosition().x - (m_shape->getSize() / 2);
        
        float mouse_x = sf::Mouse::getPosition(*m_window).x;
        float mouse_y = sf::Mouse::getPosition(*m_window).y;

        return((std::abs(mouse_y - y_bottom) <= 15) &&
        (mouse_x >=  x_shapeLeft - 15) && 
        (mouse_x <= x_shapeRight + 15)); 

    }

    bool isOnTop(){
        float y_top = m_shape->getPosition().y - (m_shape->getSize() / 2);
        float x_shapeRight = m_shape->getPosition().x + (m_shape->getSize() / 2);
        float x_shapeLeft = m_shape->getPosition().x - (m_shape->getSize() / 2);

        float mouse_x = sf::Mouse::getPosition(*m_window).x;
        float mouse_y = sf::Mouse::getPosition(*m_window).y; 
        
        return((std::abs(mouse_y - y_top) <= 15) &&
        (mouse_x >= x_shapeLeft - 15) &&
        (mouse_x <= x_shapeRight + 15)); 

    }

    bool isOnRight(){
        float mouse_x = sf::Mouse::getPosition(*m_window).x;
        float mouse_y = sf::Mouse::getPosition(*m_window).y; 

        float x_right = m_shape->getPosition().x + (m_shape->getSize() / 2);
        float y_shapeBottom = m_shape->getPosition().y + (m_shape->getSize() / 2);
        float y_shapeTop = m_shape->getPosition().y - (m_shape->getSize() / 2);

        return((std::abs(mouse_x - x_right) <= 15) &&
        (mouse_y <= y_shapeBottom + 15) &&
        (mouse_y >= y_shapeTop - 15));
    }

    bool isOnLeft(){
        float mouse_x = sf::Mouse::getPosition(*m_window).x;
        float mouse_y = sf::Mouse::getPosition(*m_window).y; 

        float x_left = m_shape->getPosition().x - (m_shape->getSize() / 2);
        float y_shapeBottom = m_shape->getPosition().y + (m_shape->getSize() / 2);
        float y_shapeTop = m_shape->getPosition().y - (m_shape->getSize() / 2);

        return((std::abs(mouse_x - x_left) <= 50) &&
        (mouse_y <= y_shapeBottom + 15) &&
        (mouse_y >= y_shapeTop - 15));

    } 

    //is mouse on cross right and top of bound of shape
    bool isOnRTcross() {
        return(isOnTop() && isOnRight());
    }

    bool isOnRBcross() {
        return(isOnBottom() && isOnRight());
    }

    //Labusi tut ne prichem
    bool isOnLTcross() {
        return(isOnLeft() && isOnTop());
    }

    bool isOnLBcross() {
        return(isOnLeft() && isOnBottom());
    }

    bool isInside() {
        float x_mouse = sf::Mouse::getPosition(*m_window).x;
        float y_mouse = sf::Mouse::getPosition(*m_window).y;

        float x_shapeLeft = m_shape->getPosition().x - (m_shape->getSize() / 2);
        float x_shapeRight = m_shape->getPosition().x + (m_shape->getSize() / 2);

        float y_shapeBottom = m_shape->getPosition().y + (m_shape->getSize() / 2);
        float y_shapeTop = m_shape->getPosition().y - (m_shape->getSize() / 2);

        return((x_mouse >= x_shapeLeft) &&
            (x_mouse <= x_shapeRight) && 
            (y_mouse >= y_shapeTop) &&
            (y_mouse <= y_shapeBottom));       
    }
};
