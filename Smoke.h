#ifndef SMOKE_H
#define SMOKE_H
#include "ParticleSystem.h"
#include "GameObject.h"

class SmokeEmitter : public ParticleSystem::Emitter, public GameObject
{
public:
    SmokeEmitter();
    void onParticleUpdated(ParticleSystem::Particle& particle, float dt) const override;
    void update(float dt) override;
    void handleEvent(const sf::Event& event);
    void setPosition(float x, float y) override;
    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition() override;
    void setActive(bool active) override;
    void handleCollision(GameObject& other) override;
    void setDie(bool die);
    bool toDestroy();
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    bool m_die;
    float m_timer;
};

#endif //SMOKE_H
