#include "PhysicComponent.h"
#include "Actor.h"
#include "TimerManager.h"

PhysicComponent::PhysicComponent(Actor* _owner, const float _mass, const float _restitution,
    const float _friction) : Component(_owner)
{
    canMove = false;
    velocity = Vector2f();
    mass = _mass;
    gravity = 9.81f;
    restitution = _restitution;
    friction = _friction;
}

PhysicComponent::PhysicComponent(Actor* _owner, const PhysicComponent* _other) : Component(_owner)
{
    canMove = _other->canMove;
    velocity = _other->velocity;
    mass = _other->mass;
    gravity = _other->gravity;
    restitution = _other->restitution;
    friction = _other->friction;
}

void PhysicComponent::BeginPlay()
{
    Super::BeginPlay();

    new Timer([&]() { canMove = true; }, seconds(2.0f), true);
}

void PhysicComponent::Tick(const float _deltaTime)
{
    Super::Tick(_deltaTime);

    if (!canMove) return;
    LOG(Warning, velocity);
    // Appliquer la gravité
    velocity.y += gravity * mass * _deltaTime;

    // Calculer le déplacement
    const Vector2f& _displacement = velocity * _deltaTime;

    // Mettre à jour la position
    owner->Move(_displacement);
}

void PhysicComponent::ApplyBounce(const Vector2f& _normal)
{
    owner->Move(_normal * 0.1f);

    // Calculer la projection de la vitesse sur la normale
    float _dotProduct = velocity.x * _normal.x + velocity.y * _normal.y;

    // Appliquer le rebond : inverser la composante normale de la vitesse
    velocity -= 2.0f * _dotProduct * _normal;

    // Réduire la vitesse en fonction du facteur de restitution
    velocity *= restitution;

    // Appliquer la friction à la composante tangentielle
    velocity.x *= friction;

    // Éviter de petites oscillations en annulant de faibles valeurs
    if (abs(velocity.x) < 1.0f)
    {
        velocity.x = 0.0f;
    }

    if (abs(velocity.y) < 1.0f)
    {
        velocity.y = 0.0f;
    }
}

void PhysicComponent::AddForce(const Vector2f& _force)
{
    velocity.x += _force.x;
    velocity.y += _force.y;
}

