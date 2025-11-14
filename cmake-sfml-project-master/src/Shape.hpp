#include <SFML\Graphics.hpp>
#include <vector>
#include <string>
#include <cmath>
#include <iostream>

const float DEFAULT_SIZE = 40;
const float WIN_WIDTH = 800; 
const float WIN_HEIGHT = 600;
const sf::Angle DEFAULT_ANGLE = sf::degrees(0);
const float PI = acos(-1.0);

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

    sf::Angle getAngle() {
        return m_angle;
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
    virtual void move(const sf::Vector2f& position) = 0; 
    virtual void rotate(const sf::Angle& angle) = 0;
    virtual void draw(sf::RenderTarget& target) const = 0;
    virtual std::vector<sf::Vector2f> getCornerCoords() = 0;
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

    void move(const sf::Vector2f& position) override {
        m_position.x = position.x; 
        m_position.y = position.y; 
        update();
    }

    void rotate(const sf::Angle& angle) override {
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

    // func calculate corner coords after rotation
    std::vector<sf::Vector2f> getCornerCoords() override {
        std::vector<sf::Vector2f> transCoords;
        sf::Vector2f center = m_outRectangle.getPosition();
        
        float cos_alpha = cos(m_angle.asRadians());
        float sin_alpha = sin(m_angle.asRadians());
        
        std::vector<sf::Vector2f> localCorners = {
            {center.x - m_size, center.y + m_size},
            {center.x + m_size, center.y + m_size},
            {center.x + m_size, center.y - m_size},
            {center.x - m_size, center.y - m_size}
        };

        for(const sf::Vector2f& corner : localCorners){
            float dx = (corner.x - center.x) * cos_alpha - (corner.y - center.y) * sin_alpha;
            float dy = (corner.x - center.x) * sin_alpha + (corner.y - center.y) * cos_alpha;\
            transCoords.push_back({dx, dy});
        }

        return transCoords;

    }

}; 

class PolygonalShape : public Shape {
private: 

    sf::ConvexShape m_convex; 

    void update() {
        //local points coords
        std::vector<sf::Vector2f> localPoints {
            {0, 0},
            {m_size, 0},
            {m_size / 2, 4 * (m_size / 5)}, 
            {m_size, m_size},
            {0, m_size},
            {m_size / 2, m_size / 5}
        };

        // find local center
        sf::Vector2f localCenter = {0, 0};
        for(const auto& point : localPoints){
            localCenter.x += point.x;
            localCenter.y += point.y;
        }
        localCenter.x /= localPoints.size();
        localCenter.y /= localPoints.size();

    
        m_convex.setPointCount(localPoints.size());

        // rotate every point if needed
        if(std::abs(m_angle.asRadians()) < 1e-5){
            for(int i = 0; i < localPoints.size(); ++i){
                m_convex.setPoint(i, {
                    m_position.x + localPoints[i].x,
                    m_position.y + localPoints[i].y
                });
            }
        }
        else{
            float cosA = std::cos(m_angle.asRadians());
            float sinA = std::sin(m_angle.asRadians());

            for(int i = 0; i < localPoints.size(); ++i){

                float dx = localPoints[i].x - localCenter.x;
                float dy = localPoints[i].y - localCenter.y;

                float rotated_x = localCenter.x + dx * cosA - dy * sinA;
                float rotated_y = localCenter.y + dx * sinA + dy * cosA;

                m_convex.setPoint(i, {
                    m_position.x + rotated_x,
                    m_position.y + rotated_y
                });
            } 
        }
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

    void move(const sf::Vector2f& position) override {
        m_position.x = position.x; 
        m_position.y = position.y; 
        update();
    }

    void rotate(const sf::Angle& angle) override {
        m_angle = angle;
        update();
    }  


    std::vector<sf::Vector2f> getCornerCoords() override {
        std::vector<sf::Vector2f> corners;

        corners.push_back(m_convex.getPoint(0));
        corners.push_back(m_convex.getPoint(1));
        corners.push_back(m_convex.getPoint(3));
        corners.push_back(m_convex.getPoint(4)); 

        return corners;
    }

    void draw(sf::RenderTarget& target) const override {
        target.draw(m_convex); 
    }

};






