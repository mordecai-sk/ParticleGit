#include "Engine.h"

Engine::Engine()
{
    VideoMode vm(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
    srand(time(0));
    m_Window.create(vm, "Particles", Style::Default);
}

void Engine::run()
{
    Clock localClock;
    Time dt;
    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, {(int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2});
    p.unitTests();
    cout << "Unit tests complete.  Starting engine..." << endl;
    while (m_Window.isOpen())
    {
        dt = localClock.restart();
        input();
        update(dt.asSeconds());
        draw();
    }
}

void Engine::input()
{
    Event event;
    while (m_Window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            m_Window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            m_Window.close();
        }
        if (event.type == Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == Mouse::Left)
            {
                for (int i = 0; i < 5; i++)
                {
                    Vector2i mousePixel(event.mouseButton.x, event.mouseButton.y);
                    Particle p(m_Window, (rand() % 26) + 25, mousePixel);
                    m_particles.push_back(p);
                }
            }
        }
    }
       
}

void Engine::update(float dtAsSeconds)
{
    for (auto it = m_particles.begin(); it != m_particles.end();)
    {
        if (it->getTTL() > 0.0)
        {
            it->update(dtAsSeconds);
            it++;
        }
        else
        {
            it = m_particles.erase(it);
        }
    }
}

void Engine::draw()
{
    m_Window.clear();

    for (Particle p : m_particles)
    {
        m_Window.draw(p);
    }

    m_Window.display();
}
