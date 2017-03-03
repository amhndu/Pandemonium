#include <iostream>
#include "Game.h"
#include "ResourceManager.h"
#include "Constants.h"
#include "Player.h"
#include "Button.h"
#include"Enemy.h"

template<>
std::unique_ptr<TextureManager> TextureManager::m_instance = nullptr;
template<>
std::unique_ptr<FontManager> FontManager::m_instance = nullptr;

Game::Game() :
    m_window(sf::VideoMode::getDesktopMode(), "Game Jam Entry", sf::Style::Fullscreen)
{
    FontManager::load(DefaultFont, "assets/font.ttf");

    TextureManager::load(StartScreenBackground, "assets/startscreen.png");
    TextureManager::load(GameOverBackground, "assets/gameover.png");
    TextureManager::load(GameBackground, "assets/gamebackground.png");

    //TODO
    //Load Cutscenes
    TextureManager::load(PlayerSprite, "assets/playersprite.png");
    TextureManager::load(Bot1Sprite, "assets/enemy.png");

    m_window.setVerticalSyncEnabled(true);

    auto &startBtn = *static_cast<Button*>(m_startButtons.insert("start", new Button()));
    startBtn.setText("Start Game");
    startBtn.setPosition(20, 80);
    startBtn.setCallback([&](){ setState(Playing); });

    auto &exitBtn = *static_cast<Button*>(m_startButtons.insert("exit", new Button()));
    exitBtn.setText("Exit");
    exitBtn.setPosition(20, 150);
    exitBtn.setCallback([&](){ setState(Exit); });

    auto &player = *static_cast<Player*>(m_gameObjects.insert("player", new Player()));
    player.setPosition(0, m_window.getSize().y - 300.f - 200);


    auto &bot1 = *static_cast<Enemy*>(m_gameObjects.insert("bot1", new Enemy(player)));
    bot1.setPosition(WINDOW_WIDTH - 100.f, m_window.getSize().y - 300.f);

    setState(Playing);
//     setState(StartScreen);
}

void Game::setState(GameState state)
{
    m_state = state;
    switch (m_state)
    {
        case StartScreen:
            m_background.setTexture(TextureManager::get(StartScreenBackground));
            m_activeObjects = &m_startButtons;
            break;
        case Playing:
            m_background.setTexture(TextureManager::get(GameBackground));
            m_activeObjects = &m_gameObjects;
            break;
        case GameOver:
            m_background.setTexture(TextureManager::get(GameOverBackground));
            m_activeObjects = &m_endButtons;
            break;
    }
}

void Game::run()
{
    sf::Event event;
    sf::Clock m_timer;
    while (m_state != Exit && m_window.isOpen())
    {
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape))
                m_window.close();

            if (event.type == sf::Event::LostFocus)
                m_activeObjects->setActive(false);
            else if (event.type == sf::Event::GainedFocus)
                m_activeObjects->setActive(true);

            m_activeObjects->handleEvent(event);

            if (m_state == Cutscene && event.type == sf::Event::KeyReleased)
            {
                if (++m_cutscene < m_totalCutscenes)
                {
                    m_background.setTexture(TextureManager::get(static_cast<TextureIdentifier>(Cutscene1 + m_cutscene)));
                }
                else
                {
                    m_cutscene = 0;
                    setState(Playing);
                    //TODO restart game
                }
            }

        }

        m_window.clear(sf::Color::White);
        m_window.draw(m_background);

        // Update/Draw
        m_activeObjects->update(m_timer.restart().asSeconds());
        m_activeObjects->render(m_window);

        m_window.display();
    }
}

void Game::newGame()
{
    m_state = Playing;
}