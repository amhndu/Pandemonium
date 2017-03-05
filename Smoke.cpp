#include "Smoke.h"

SmokeEmitter::SmokeEmitter() :
    GameObject(GameObject::ParticleEmitter),
    m_die(false)
{};

void SmokeEmitter::onParticleUpdated(ParticleSystem::Particle& particle, float dt) const
{
    particle.position.y -= 50.f * dt;
    particle.position.x += 10.f * dt;
}

void SmokeEmitter::update(float dt)
{
    if (m_die)
        m_timer -= dt;
};

void SmokeEmitter::handleEvent(const sf::Event& event){};

void SmokeEmitter::setPosition(float x, float y)
{
    setPosition({x, y});
};

void SmokeEmitter::setPosition(sf::Vector2f pos)
{
    ParticleSystem::Emitter::setPosition(pos);
};

sf::Vector2f SmokeEmitter::getPosition()
{
    return ParticleSystem::Emitter::getPosition();
};

void SmokeEmitter::setActive(bool active){};

void SmokeEmitter::handleCollision(GameObject& other) {};

void SmokeEmitter::setDie(bool die)
{
    if (die)
    {
        m_timer = 0.5f;
        setLooping(false);
    }
};

bool SmokeEmitter::toDestroy()
{
    return m_die && m_timer <= 0;
}

void SmokeEmitter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}
