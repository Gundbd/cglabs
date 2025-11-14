#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>

const int DEFAULT_SEGMENT_SIZE = 100;

class BezierCurve  {
private:
    int m_segmentSize;
    sf::Color m_color;
    std::vector<sf::Vector2f> m_controlPoints; 


    long long binomialCoefficient(int n, int k){
        if(k < 0 || k > n ) { return 0; }
        if( k == 0 || k == n) { return 1; }
        
        long long result = 1;
        
        for(int i = 1; i < std::min(k, n - k) + 1; ++i){
            result = result * (n - i + 1) / i;
        }
        std::cout << result << std::endl;
        return result;
    }


    double bernsteinePolynomial(int n, int i, double t){
        return binomialCoefficient(n, i) * std::pow(t,i) * std::pow(1 - t, n - i);
    }
    
public: 
    BezierCurve() : m_segmentSize(100), m_color(sf::Color::Green),
        m_controlPoints(std::vector<sf::Vector2f>{{150, 150},{400,200},{300, 300}}) {};
    
    BezierCurve(int segment, sf::Color color, std::vector<sf::Vector2f> controlPoints) {
        m_segmentSize = segment;
        m_color = color; 
        m_controlPoints = controlPoints;
    }  

    std::vector<sf::Vector2f> getCoords() {
        std::vector<sf::Vector2f> coords;

        if(m_controlPoints.size() < 2) { return coords; }
        
        int n = m_controlPoints.size() - 1;

        for(int segment = 0; segment <= m_segmentSize; ++segment){
            double t = static_cast<double>(segment) / m_segmentSize;

            sf::Vector2f point(0, 0);

            for(int i = 0; i <= n; i++) {
                double bern = bernsteinePolynomial(n, i , t);
                point.x += m_controlPoints[i].x * bern; 
                point.y += m_controlPoints[i].y * bern;
            }

            coords.push_back(point);
        }
        return coords;
    }

    void draw(sf::RenderTarget& target) {
        std::vector<sf::Vector2f> points = getCoords();

        if(points.size() < 2) return;

        sf::VertexArray curve(sf::PrimitiveType::LineStrip, points.size());
        for(int i = 0; i < points.size(); ++i){
            curve[i].position = points[i];
            curve[i].color = m_color;
        }
        target.draw(curve);

        for (const auto& cp : m_controlPoints){
            sf::CircleShape circle(3);
            circle.setFillColor(sf::Color::Red);
            circle.setPosition({cp.x - 3, cp.y - 3});
            target.draw(circle);
        }

    }


    void setControlPoints(const std::vector<sf::Vector2f>& points){
        m_controlPoints = points;
    }

    void addControlPoint(const sf::Vector2f& point) {
        m_controlPoints.push_back(point);
    }

    void setSegment(int segment) {
        m_segmentSize = segment;
    }

};