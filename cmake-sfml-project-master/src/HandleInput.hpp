#include <SFML\Graphics.hpp>

class HandleInput {
private:

    Shape* m_shape;
    sf::RenderWindow* m_window;

public:

    HandleInput(Shape* shape, sf::RenderWindow* window) : m_shape(shape), m_window(window) {}

   

    bool isInside() {
        float x_mouse = sf::Mouse::getPosition(*m_window).x;
        float y_mouse = sf::Mouse::getPosition(*m_window).y;

        std::vector<sf::Vector2f> corners = m_shape->getCornerCoords();

        if(x_mouse >= corners[0].x && x_mouse <= corners[1].x &&
            y_mouse >= corners[0].y && y_mouse <= corners[3].y) {
                return true;
            }
        else return false;
    
    }


    bool isUpperCorner() {
        float x_mouse = sf::Mouse::getPosition(*m_window).x;
        float y_mouse = sf::Mouse::getPosition(*m_window).y;

        std::vector<sf::Vector2f> corners = m_shape->getCornerCoords();

        for(const auto& corner : corners){
            if(isOnCorner() && y_mouse <= corner.y) { return true; }
        }

        return false;

    }


    bool isOnCorner(){
        std::vector<sf::Vector2f> corners = m_shape->getCornerCoords();

        float x_mouse = sf::Mouse::getPosition(*m_window).x;
        float y_mouse = sf::Mouse::getPosition(*m_window).y;
        
        for(const auto& corner : corners){
            if(std::abs(x_mouse - corner.x) <= 10 && std::abs(y_mouse - corner.y) <= 10){
                return true; 
            }    
        }

        return false;

    }
};
