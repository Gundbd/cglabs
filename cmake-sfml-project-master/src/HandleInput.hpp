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


    int getCornerIndex(){
        float x_mouse = sf::Mouse::getPosition(*m_window).x;
        float y_mouse = sf::Mouse::getPosition(*m_window).y;

        std::vector<sf::Vector2f> corners = m_shape->getCornerCoords();

        for(int i = 0; i < corners.size(); ++i){
            if(std::abs(x_mouse - corners[i].x) <= 30 &&
                std::abs(y_mouse - corners[i].y) <= 30) 
                return i;
        }
        
        return -1;

    }


    bool isUpperCorner() {
        int cornerIndex = getCornerIndex();
        if(cornerIndex == -1) return false;

        std::vector<sf::Vector2f> corners = m_shape->getCornerCoords();

        float y_mouse = sf::Mouse::getPosition(*m_window).y;

        return y_mouse > corners[cornerIndex].y;

    }


    bool isOnCorner(){
        std::vector<sf::Vector2f> corners = m_shape->getCornerCoords();

        float x_mouse = sf::Mouse::getPosition(*m_window).x;
        float y_mouse = sf::Mouse::getPosition(*m_window).y;
        
        for(const auto& corner : corners){
            if(std::abs(x_mouse - corner.x) <= 30 && std::abs(y_mouse - corner.y) <= 30){
                return true; 
            }    
        }

        return false;

    }
};
