#include "SceneManager.h"
#include "Constants.h"

SceneManager::SceneManager()
{
    // Scene 1: Entrance
    decltype(SceneManifest::waves) waves;
    SceneManifest::EnemySwarm wave;
    wave.emplace_back(Enemy::Easy, 2);
    waves.push_back(wave);
    m_scenes.emplace(Entrance, SceneManifest{
                    EntranceSceneBG,
                    std::move(waves),
                    sf::Vector2f{WINDOW_WIDTH - 180, WINDOW_HEIGHT - LAND_APP_HEIGHT - 200}
                });

    // Scene 2: Ruin
    waves.clear();
    // Wave 1
    wave.clear();
    wave.emplace_back(Enemy::Easy, 5);
    waves.push_back(wave);
    // Wave 2
    wave.clear();
    wave.emplace_back(Enemy::Easy, 3);
    wave.emplace_back(Enemy::Medium, 3);
    waves.push_back(wave);
    // Wave 3
    wave.clear();
    wave.emplace_back(Enemy::Easy, 5);
    wave.emplace_back(Enemy::Medium, 5);
    waves.push_back(wave);
    // Wave 4
    wave.clear();
    wave.emplace_back(Enemy::Boss, 1);
    waves.push_back(wave);
    m_scenes.emplace(Ruins, SceneManifest{
                    RuinSceneBG,
                    std::move(waves),
                    sf::Vector2f{WINDOW_WIDTH - 60, WINDOW_HEIGHT - LAND_APP_HEIGHT}
                });
    restart();
}

const SceneManifest& SceneManager::getScene()
{
    return m_currentScene->second;
}

bool SceneManager::nextScene()
{
    ++m_currentScene;
    m_currentWave = 0;
    return m_currentScene != m_scenes.end();
}

bool SceneManager::nextWave()
{
    ++m_currentWave;
    return m_currentWave < m_currentScene->second.waves.size();
}


void SceneManager::restart()
{
    m_currentScene = m_scenes.begin();
    m_currentWave = 0;
}

std::size_t SceneManager::getWave()
{
    return m_currentWave;
}

