#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>

#include "collision.hpp"
#include "platform.hpp"
#include "animation.hpp"
#include "read_map.hpp"
#include "Turtix.hpp"

using namespace std;
using namespace sf;

enum Direction
{
    RIGHT,
    LEFT,
    IDLE,
    UP,
};

static const float VIEW_HIEGHT = 800.0f;

void resize_view(RenderWindow &window, View &view){
    float aspect_retio = float (window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HIEGHT*aspect_retio ,VIEW_HIEGHT);
}