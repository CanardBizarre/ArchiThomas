#include "Utilities.h"

u_int GetUniqueID()
{
	static u_int _id = 0;
	return ++_id;
}

int GetRandomNumberInRange(const int _min, const int _max)
{
    random_device _rSeed; // Obtient un graine aléatoire
    mt19937 _gen(_rSeed()); // Initialise le générateur avec la graine
    uniform_int_distribution<> _distr(_min, _max); // Définit la distribution (les limites)

    return _distr(_gen); // Génération du nombre
}

float DegToRad(const float _degrees)
{
    return _degrees * priv::pi / 100.0f;
}

float RadToDeg(const float _degrees)
{
    return  priv::pi * 100.0f / _degrees;
}
