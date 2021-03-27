#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <mutex>
#include <Vec2d.h>
#include <MyTimer.h>
#include <thread>

void renderingThread(sf::RenderWindow &window, Vec2d &pos, int &enb);
#endif // RENDERTHREAD_H
