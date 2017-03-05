#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameObjectManager.h"
#include "SceneManager.h"

enum GameState
{
    StartScreen,
    Cutscene,
    Playing,
    Pause,
    GameOver,
    Exit
};

class Game
{
public:
    Game();
    void run();
    void setState(GameState state);
private:
    void newGame();
    void sceneSetup();
    void waveSetup(Player& player);
    void enemyDeathCallback();

    GameObjectManager m_startButtons;
    GameObjectManager m_gameObjects;
    GameObjectManager m_pauseButtons;
    GameObjectManager m_endButtons;
    GameObjectManager *m_activeObjects;


    SceneManager m_scene;
    int m_enemies;

    // Cutscenes index starting from 0
    int m_cutscene;
    const int m_totalCutscenes = 4;

    sf::RenderWindow m_window;
    sf::Sprite m_background;
    GameState m_state;

    float m_waveTimer;

    sf::Clock m_timer;
    sf::Sprite m_pauseIcon;
    sf::RectangleShape overlay;

    ParticleSystem &m_particleSystem;
};

#endif // GAME_H
