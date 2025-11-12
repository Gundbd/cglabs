#include <SFML\Graphics.hpp>
#include <vector>
#include <string>
#include <cmath>
#include <iostream>

const float DEFAULT_SIZE = 40;
const float WIN_WIDTH = 800; 
const float WIN_HEIGHT = 600;
const sf::Angle DEFAULT_ANGLE = sf::degrees(0);

class Shape {
protected:
    float m_size;
    sf::Angle m_angle;
    sf::Color m_color; 
    sf::Vector2f m_position;
    
public:
    struct Params {
        float size;
        sf::Angle angle; 
        sf::Color color;
        sf::Vector2f position;
    };

    Shape() : m_size(DEFAULT_SIZE), m_angle(DEFAULT_ANGLE), 
        m_color(sf::Color::Green), m_position({10, 10}) {}

    Shape(const Params& params) {
        m_size = params.size;
        m_angle = params.angle;
        m_color = params.color;
        m_position = params.position;
    }
    
    float getSize() const {
        return m_size;
    }

    sf::Color getColor() const {
        return m_color;
    }

    sf::Vector2f getPosition() const {
        return m_position;
    }
    
        
    virtual void fillColor(const sf::Color& color)= 0;
    virtual void resize(float size) = 0; 
    virtual void move(sf::Vector2f position) = 0; 
    virtual void rotate(sf::Angle) = 0;
    virtual void draw(sf::RenderTarget& target) const = 0; 
    virtual ~Shape() = default;
};

class StrangeShape : public Shape {
private:     

    sf::RectangleShape m_outRectangle;
    sf::CircleShape m_circle;
    sf::RectangleShape m_inRectangle;

    void update() {
        float inRectSize = (m_size * static_cast<float>(sqrt(2)) / 2);
        
        m_outRectangle.setSize({m_size, m_size});
        m_circle.setRadius(m_size / 2);
        m_inRectangle.setSize({inRectSize, inRectSize});

        m_outRectangle.setOrigin({m_size / 2, m_size / 2}); 
        m_circle.setOrigin({m_size / 2, m_size / 2});
        m_inRectangle.setOrigin({ inRectSize / 2, inRectSize / 2 });

        m_outRectangle.setFillColor(m_color);
        m_circle.setFillColor(sf::Color::Black);
        m_inRectangle.setFillColor(m_color);
        
        m_circle.setPosition({m_position.x, m_position.y});
        m_outRectangle.setPosition({m_position.x, m_position.y});
        m_inRectangle.setPosition({m_position.x, m_position.y});

        m_outRectangle.setRotation({m_angle});
        m_inRectangle.setRotation({m_angle});

    }

public:
    StrangeShape() : Shape() { update(); }

    StrangeShape(const Params& params) : Shape(params) { update(); }

    void fillColor(const sf::Color& color) override {
        m_color = color;
        update(); 
    }

    void resize(float size) override {
        m_size = size; 
        update();
    }

    void move(sf::Vector2f position) override {
        m_position.x = position.x; 
        m_position.y = position.y; 
        update();
    }

    void rotate(sf::Angle angle) override {
        m_angle = angle;
        m_outRectangle.setRotation(angle);
        m_inRectangle.setRotation(angle);
        update();
    }  

    void draw(sf::RenderTarget& target) const override {
        target.draw(m_outRectangle);
        target.draw(m_circle);
        target.draw(m_inRectangle);
    }

}; 

class PolygonalShape : public Shape {
private: 

    sf::ConvexShape m_convex; 

    void update() {

        m_convex.setPointCount(6);

        m_convex.setPoint(0, {m_position.x, m_position.y});
        m_convex.setPoint(1, {m_position.x + m_size, m_position.y});
        m_convex.setPoint(2, {m_position.x + m_size / 2, m_position.y + 4 * (m_size / 5)});
        m_convex.setPoint(3, {m_position.x + m_size, m_position.y + m_size});
        m_convex.setPoint(4, {m_position.x, m_position.y + m_size});
        m_convex.setPoint(5, {m_position.x + m_size / 2, m_position.y + (m_size / 5)}); 

    }

public:
    PolygonalShape() : Shape() { update(); }

    PolygonalShape(const Params& params) : Shape(params) { update(); }

        void fillColor(const sf::Color& color) override {
        m_color = color;
        update(); 
    }

    void resize(float size) override {
        m_size = size; 
        update();
    }

    void move(sf::Vector2f position) override {
        m_position.x = position.x; 
        m_position.y = position.y; 
        update();
    }

    void rotate(sf::Angle angle) override {
        m_angle = angle;
        update();
    }  


    void draw(sf::RenderTarget& target) const override {
        target.draw(m_convex); 
    }

};






