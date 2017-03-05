#include "SceneManager.h"
#include "Constants.h"
#include <iostream>

SceneManager::SceneManager()
{
    // Scene 1: Entrance
    decltype(SceneManifest::waves) waves;
    SceneManifest::EnemySwarm wave;
    wave.emplace_back(Enemy::DamagedEasy, 2);
    waves.push_back(wave);
    m_scenes.emplace(Entrance, SceneManifest{
                    EntranceSceneBG,
                    std::move(waves),
                    WINDOW_WIDTH - 100,
                    WINDOW_WIDTH - 300
                });

    // Scene 2: Ruin
    waves.clear();
    // Wave 1
    wave.clear();
    wave.emplace_back(Enemy::Easy, 3);
    waves.push_back(wave);

    // Wave 2
    wave.clear();
    wave.emplace_back(Enemy::Easy, 5);
    waves.push_back(wave);

    // Wave 3
    wave.clear();
    wave.emplace_back(Enemy::Easy, 3);
    wave.emplace_back(Enemy::Medium, 1);
    waves.push_back(wave);

    // Wave 4
    wave.clear();
    wave.emplace_back(Enemy::Easy, 2);
    wave.emplace_back(Enemy::Medium, 2);
    waves.push_back(wave);

    // Wave 5
    wave.clear();
    wave.emplace_back(Enemy::Medium, 5);
    waves.push_back(wave);

    // Wave 6
    wave.clear();
    wave.emplace_back(Enemy::Easy, 3);
    wave.emplace_back(Enemy::Hard, 1);
    waves.push_back(wave);

    // Wave 7
    wave.clear();
    wave.emplace_back(Enemy::Medium, 2);
    wave.emplace_back(Enemy::Hard, 1);
    waves.push_back(wave);

    // Wave 8
    wave.clear();
    wave.emplace_back(Enemy::Hard, 3);
    waves.push_back(wave);

    m_scenes.emplace(Ruins, SceneManifest{
                    RuinSceneBG,
                    std::move(waves),
                    WINDOW_WIDTH - 100,
                    WINDOW_WIDTH - 200
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

std::size_t SceneManager::getWaveNumber()
{
    return m_currentWave+1;
}

std::size_t SceneManager::getSceneNumber()
{
    return m_currentScene->first+1;
}


SceneManifest::EnemySwarm SceneManager::getWave()
{
    return m_currentScene->second.waves[m_currentWave];
}

