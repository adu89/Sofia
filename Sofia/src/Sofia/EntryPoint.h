#pragma once

#include <thread>

extern sf::Application* sf::CreateApplication();

int main(int argc, char** argv)
{
    sf::Log::Init();
    auto app = sf::CreateApplication();
    app->Run();
}