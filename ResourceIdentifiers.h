#ifndef RESOURCEIDENTIFIERS_INCLUDED
#define RESOURCEIDENTIFIERS_INCLUDED
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum TextureIdentifier
{
    StartScreenBackground,
    PauseIcon,
    EntranceSceneBG,
    RuinSceneBG,
    GameOverWinBackground,
    GameOverLoseBackground,
    PlayerSprite,
    Bot1Sprite,
    Bot2Sprite,
    Bot3Sprite,
    Cutscene1,
    Cutscene2,
    Cutscene3,
    SmokeParticle,
    ArrowTexture,
    BulletTexture
};

enum FontIdentifier
{
    DefaultFont
};

enum MusicIdentifier
{
    StartScreenMusic,
    CutsceneMusic,
    PauseMusic,
    SceneMusic1,
    SceneMusic2
};

#endif // RESOURCEIDENTIFIERS_INCLUDED
