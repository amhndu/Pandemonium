#include <iostream>
#include <cstdlib>
#include "Game.h"
#include "ResourceManager.h"
#include "Constants.h"
#include "Player.h"
#include "Button.h"
#include "Enemy.h"

template<>
std::unique_ptr<TextureManager> TextureManager::m_instance = nullptr;
template<>
std::unique_ptr<FontManager> FontManager::m_instance = nullptr;

Game::Game() :
    m_window(sf::VideoMode::getDesktopMode(), "Game Jam Entry"/*, sf::Style::Fullscreen*/)
{
    FontManager::load(DefaultFont, "assets/font.ttf");

    TextureManager::load(StartScreenBackground, "assets/startscreen.png");
    TextureManager::load(GameOverBackground, "assets/gameover.png");
    TextureManager::load(EntranceSceneBG, "assets/gamebackground.png");

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

    srand(std::time(nullptr));

    setState(Playing);
    newGame();
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
        case Cutscene:
            m_background.setTexture(TextureManager::get(Cutscene1));
            m_activeObjects = nullptr;
            break;
        case Playing:
            m_activeObjects = &m_gameObjects;
            break;
        case Pause:
            break;
        case GameOver:
            m_background.setTexture(TextureManager::get(GameOverBackground));
            m_activeObjects = &m_endButtons;
            break;
    }
}

void Game::newGame()
{
    m_cutscene = 0;
    m_gameObjects.clear();
    m_scene.restart();
    sceneSetup();
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

            if (m_activeObjects)
            {
                if (event.type == sf::Event::LostFocus)
                    m_activeObjects->setActive(false);
                else if (event.type == sf::Event::GainedFocus)
                    m_activeObjects->setActive(true);
                m_activeObjects->handleEvent(event);
            }

            if (m_state == Cutscene && event.type == sf::Event::KeyReleased)
            {
                if (++m_cutscene < m_totalCutscenes)
                    m_background.setTexture(TextureManager::get(static_cast<TextureIdentifier>(Cutscene1 + m_cutscene)));
                else
                    newGame();
            }
        }

        m_window.clear(sf::Color::White);
        m_window.draw(m_background);

        // Update/Draw
        if (m_activeObjects)
        {
            m_activeObjects->update(m_timer.restart().asSeconds());
            m_activeObjects->render(m_window);
        }

        m_window.display();
    }
}

void Game::sceneSetup()
{
    m_state = Playing;
    auto &player = *static_cast<Player*>(m_gameObjects.insert("player", new Player()));
    player.setPosition(100, m_window.getSize().y - LAND_APP_HEIGHT);
    player.setZ(5);

    m_background.setTexture(TextureManager::get(m_scene.getScene().sceneBG));

    waveSetup(player);
}

void Game::waveSetup(Player& player)
{
    m_enemies = 0;
    for (const SceneManifest::EnemySwarm& swarm : m_scene.getScene().waves)
    {
        for (const auto& i : swarm)
        {
            for (int j = 0; j < i.second; ++j)
            {
                ++m_enemies;
                auto &bot = *static_cast<Enemy*>(m_gameObjects.insert("bot" + std::to_string(m_enemies), new Enemy(i.first, player)));
                bot.setPosition(m_scene.getScene().spawnXBeg +
                                   (rand() / (float)RAND_MAX)  * (m_scene.getScene().spawnXEnd - m_scene.getScene().spawnXBeg),
                                m_window.getSize().y - LAND_APP_HEIGHT);
                bot.setZ(rand() % 10);
            }
        }
    }
}

void Game::enemyDeathCallback()
{
    --m_enemies;

    if (m_enemies <= 0)
    {
        if (!m_scene.nextWave())
        {
            if (m_scene.nextScene())
                sceneSetup();
            else
                m_state = GameOver;
        }
        else
            waveSetup(static_cast<Player&>(*m_gameObjects.get("player")));
    }
}

