#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "ResourceIdentifiers.h"
#include "Enemy.h"
#include <map>
#include <vector>

enum Scenes
{
    Entrance,
    Ruins
};

struct SceneManifest
{
    TextureIdentifier sceneBG;
    using EnemySwarm = std::vector<std::pair<Enemy::Type, int>>;
    std::vector<EnemySwarm> waves;
    float spawnXBeg, spawnXEnd;
};

class SceneManager
{
public:
    SceneManager();
    const SceneManifest& getScene();
    SceneManifest::EnemySwarm getWave();
    std::size_t getWaveNumber();
    std::size_t getSceneNumber();
    void restart();
    bool nextScene();
    bool nextWave();
private:
    std::map<Scenes, SceneManifest>::iterator m_currentScene;
    std::size_t m_currentWave;
    std::map<Scenes, SceneManifest> m_scenes;
};

#endif // SCENEMANAGER_H
