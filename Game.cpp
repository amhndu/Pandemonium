#include <iostream>
#include <cstdlib>
#include "Game.h"
#include "ResourceManager.h"
#include "Constants.h"
#include "Player.h"
#include "Button.h"
#include "Enemy.h"
#include "HUD.h"
#include "Smoke.h"

template<>
std::unique_ptr<TextureManager> TextureManager::m_instance = nullptr;
template<>
std::unique_ptr<FontManager> FontManager::m_instance = nullptr;

Game::Game() :
    m_window(sf::VideoMode::getDesktopMode(), "Game Jam Entry", sf::Style::Fullscreen),
    m_waveTimer(3.f),
    m_particleSystem(ParticleSystem::getInstance())
{
    FontManager::load(DefaultFont, "assets/font.ttf");

    TextureManager::load(StartScreenBackground, "assets/startscreen.png");
    TextureManager::load(GameOverWinBackground, "assets/gameover.png");
    TextureManager::load(GameOverLoseBackground, "assets/gameover.png");

    TextureManager::load(EntranceSceneBG, "assets/gamebackground.png");
    TextureManager::load(RuinSceneBG, "assets/gamebackground.png");
    TextureManager::load(PauseIcon, "assets/pause.png");

    TextureManager::load(PlayerSprite, "assets/playersprite.png");
    TextureManager::load(Bot1Sprite, "assets/bot1sprite.png");
    TextureManager::load(Bot2Sprite, "assets/bot2sprite.png");
    TextureManager::load(Bot3Sprite, "assets/bot3sprite.png");
    TextureManager::load(SmokeParticle, "assets/particle.png");
    TextureManager::get(SmokeParticle).setSmooth(true);

    TextureManager::load(ArrowTexture, "assets/arrow.png");
    TextureManager::load(BulletTexture, "assets/bullet.png");

    m_particleSystem.setTexture(&TextureManager::get(SmokeParticle));

    m_window.setVerticalSyncEnabled(true);

    srand(std::time(nullptr));

    overlay.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0x50505050));
    m_pauseIcon.setTexture(TextureManager::get(PauseIcon));
    m_pauseIcon.setOrigin(m_pauseIcon.getGlobalBounds().width / 2.f, m_pauseIcon.getGlobalBounds().height / 2.f);
    m_pauseIcon.setPosition(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f);
//    newGame();
     setState(StartScreen);
}

void Game::setState(GameState state)
{
    m_state = state;
    switch (m_state)
    {
        case StartScreen:
        {
            m_startButtons.clear();

            auto &startBtn = *static_cast<Button*>(m_startButtons.insert("start", new Button()));
            startBtn.setText("Start Game");
            startBtn.setPosition(20, 80);
            startBtn.setTextColor(sf::Color::White);
            startBtn.setBackgroundColor(sf::Color(0x25000Aff));
            startBtn.setHoverColor(sf::Color::Black);
            startBtn.setCallback([&](){ newGame(); });

            auto &exitBtn = *static_cast<Button*>(m_startButtons.insert("exit", new Button()));
            exitBtn.setText("Exit");
            exitBtn.setPosition(20, 180);
            exitBtn.setTextColor(sf::Color::White);
            exitBtn.setBackgroundColor(sf::Color(0x25000Aff));
            exitBtn.setHoverColor(sf::Color::Black);
            exitBtn.setCallback([&](){ setState(Exit); });

            m_background.setTexture(TextureManager::get(StartScreenBackground));
            m_activeObjects = &m_startButtons;
            
            m_bgMusic.openFromFile("assets/light_music.wav");

            break;
        }
        case Cutscene:
            m_background.setTexture(TextureManager::get(Cutscene1));
            m_activeObjects = nullptr;
            m_bgMusic.openFromFile("assets/cutscene.wav");

            break;
        case Playing:
            m_timer.restart();
            if(m_scene.getSceneNumber() < 5)
                m_bgMusic.openFromFile("assets/wave5-.wav");
            else
                m_bgMusic.openFromFile("assets/wave5+ music.wav");
            m_activeObjects = &m_gameObjects;
            break;
        case Pause:
        {
            m_pauseButtons.clear();

            auto &startBtn = *static_cast<Button*>(m_pauseButtons.insert("start", new Button()));
            startBtn.setText("Resume");
            startBtn.setPosition(20, 150);
            startBtn.setTextColor(sf::Color::White);
            startBtn.setBackgroundColor(sf::Color::Transparent);
            startBtn.setHoverColor(sf::Color::Black);
            startBtn.setCallback([&](){ setState(Playing); });

            auto &exitBtn = *static_cast<Button*>(m_pauseButtons.insert("exit", new Button()));
            exitBtn.setText("Exit");
            exitBtn.setPosition(20, 250);
            exitBtn.setTextColor(sf::Color::White);
            exitBtn.setBackgroundColor(sf::Color::Transparent);
            exitBtn.setHoverColor(sf::Color::Black);
            exitBtn.setCallback([&](){ setState(Exit); });

            m_activeObjects = &m_pauseButtons;
            m_bgMusic.openFromFile("assets/pause.wav");

            break;
        }
        case GameOverWin:
        {
            m_endButtons.clear();

            auto &startBtn = *static_cast<Button*>(m_endButtons.insert("start", new Button()));
            startBtn.setText("Play Again");
            startBtn.setPosition(20, 80);
            startBtn.setTextColor(sf::Color::White);
            startBtn.setBackgroundColor(sf::Color(0x25000Aff));
            startBtn.setHoverColor(sf::Color::Black);
            startBtn.setCallback([&](){ newGame(); });

            auto &exitBtn = *static_cast<Button*>(m_endButtons.insert("exit", new Button()));
            exitBtn.setText("Exit");
            exitBtn.setPosition(20, 180);
            exitBtn.setTextColor(sf::Color::White);
            exitBtn.setBackgroundColor(sf::Color(0x25000Aff));
            exitBtn.setHoverColor(sf::Color::Black);
            exitBtn.setCallback([&](){ setState(Exit); });

            m_background.setTexture(TextureManager::get(GameOverWinBackground));
            m_activeObjects = &m_endButtons;
            break;
        }
        case GameOverLose:
        {
            m_endButtons.clear();

            auto &startBtn = *static_cast<Button*>(m_endButtons.insert("start", new Button()));
            startBtn.setText("Restart");
            startBtn.setPosition(20, 80);
            startBtn.setTextColor(sf::Color::White);
            startBtn.setBackgroundColor(sf::Color(0x25000Aff));
            startBtn.setHoverColor(sf::Color::Black);
            startBtn.setCallback([&](){ newGame(); });

            auto &exitBtn = *static_cast<Button*>(m_endButtons.insert("exit", new Button()));
            exitBtn.setText("Exit");
            exitBtn.setPosition(20, 180);
            exitBtn.setTextColor(sf::Color::White);
            exitBtn.setBackgroundColor(sf::Color(0x25000Aff));
            exitBtn.setHoverColor(sf::Color::Black);
            exitBtn.setCallback([&](){ setState(Exit); });

            m_background.setTexture(TextureManager::get(GameOverLoseBackground));
            m_activeObjects = &m_endButtons;
            break;
        }
    }
    m_bgMusic.setLoop(true);
    m_bgMusic.play();
}

void Game::newGame()
{
    setState(Playing);
    m_cutscene = 0;
    m_gameObjects.clear();
    m_scene.restart();
    sceneSetup();
}

void Game::run()
{
    sf::Event event;
    while (m_state != Exit && m_window.isOpen())
    {
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();

            if (m_state == Playing && event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
                setState(Pause);
            else if (m_state == Pause && event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
                setState(Playing);

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

        if(m_state == Pause)
        {
            m_gameObjects.render(m_window);
            m_window.draw(overlay);
            m_window.draw(m_pauseIcon);
        }
        // Update/Draw
        if (m_activeObjects)
        {
            float dt = m_timer.restart().asSeconds();
            m_activeObjects->update(dt);
            m_activeObjects->render(m_window);
            if (m_state == Playing)
            {
                m_particleSystem.update(dt);
                m_window.draw(m_particleSystem, sf::BlendAlpha);
            }

            if (m_state == Playing && m_enemies <= 0)
            {
                if (m_waveTimer > 0)
                    m_waveTimer -= dt;

                if (m_waveTimer <= 0)
                {
                    if (!m_scene.nextWave())
                    {
                        if (m_scene.nextScene())
                        {
                            sceneSetup();
                        }
                        else
                            setState(GameOverWin);
                    }
                    else
                        waveSetup(static_cast<Player&>(*m_gameObjects.get("player")));
                }
            }
        }


        m_window.display();
    }
}

void Game::sceneSetup()
{
    m_state = Playing;
    m_gameObjects.clear();
    auto &player = *static_cast<Player*>(m_gameObjects.insert("player", new Player(m_gameObjects)));
    player.setPosition(130, m_window.getSize().y - LAND_APP_HEIGHT);
    player.setZ(5);
    player.setDeathCallback([&](){ setState(GameOverLose); });

    m_gameObjects.insert("HUD", new HUD(player));
    m_background.setTexture(TextureManager::get(m_scene.getScene().sceneBG));

    waveSetup(player);
}

void Game::waveSetup(Player& player)
{
    m_waveTimer = 3.f;
    m_enemies = 0;
    const SceneManifest::EnemySwarm& swarm = m_scene.getWave();
    for (const auto& p : swarm)
    {
        for (int j = 0; j < p.second; ++j)
        {
            ++m_enemies;
            auto &smoke = *static_cast<SmokeEmitter*>(m_gameObjects.insert("smoke" + std::to_string(m_enemies), new SmokeEmitter));
            auto &bot = *static_cast<Enemy*>(m_gameObjects.insert("bot" + std::to_string(m_enemies),
                                            new Enemy(p.first, player, smoke)));
            bot.setPosition(m_scene.getScene().spawnXBeg +
                                (rand() / (float)RAND_MAX)  * (m_scene.getScene().spawnXEnd - m_scene.getScene().spawnXBeg),
                            m_window.getSize().y - LAND_APP_HEIGHT);
            float z = (10.f/p.second)*j + rand()%(10/p.second);
            bot.setZ(z);
            bot.setDeathCallback([&](){ enemyDeathCallback(); } );
        }
    }
    auto &hud = *static_cast<HUD*>(m_gameObjects.get("HUD"));
    hud.setSceneNumber(m_scene.getSceneNumber());
    hud.setWaveNumber(m_scene.getWaveNumber());
}

void Game::enemyDeathCallback()
{
    --m_enemies;
}

