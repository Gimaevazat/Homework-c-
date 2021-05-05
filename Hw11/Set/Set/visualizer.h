#pragma once

#include <iomanip>
#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "calculator.h"
#include "view.h"

class Visualizer
{
public:

    Visualizer() :
        m_window(sf::VideoMode(1000U, 1000U), "MANDELBROT VISUALIZER", sf::Style::Close),
        m_calculator(m_window.getSize().x, m_window.getSize().y, 100U), m_need_redraw(true),
        m_view(sf::Vector2f(0.0f, 0.0f), 6.0f, 6.0f / (m_calculator.width() / m_calculator.height()))
    {
        initialize();
    }

    ~Visualizer() noexcept = default;

private:

    void initialize();

public:

    void save(std::string);

public:
    void screenshot(float c_1, float c_2);

public:

    void run(float c_1, float c_2);

private:

    void review();
    void update(float c_1, float c_2);
    void render();

private:

    void handle_key_pressed(sf::Keyboard::Key code);

public:
    sf::RenderWindow m_window;

private:

    
    sf::Image        m_image;
    sf::Sprite       m_sprite;
    sf::Texture      m_texture;
    sf::Font         m_font;
    sf::Text         m_text;

    Calculator m_calculator;

    bool m_need_redraw;

    View m_view;

    std::vector < sf::Color > m_colors;
};
