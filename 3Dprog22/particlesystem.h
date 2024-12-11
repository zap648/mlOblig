#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <cstdlib>
const int maxParticles = 5000;

class ParticleSystem
{
public:    
    float x[maxParticles], y[maxParticles], z[maxParticles]; // Position
    float vx[maxParticles], vy[maxParticles], vz[maxParticles]; // Velocity
    float lifetime[maxParticles]; // Lifetime in seconds
    int size = 0;

    void create(float px, float py, float pz) {
        if (size < maxParticles) {
            float speed = -5;   // speed
            x[size] = px; y[size] = py; z[size] = pz; // Position
            vx[size] = 0.0f; vy[size] = speed; vz[size] = 0.0f;  // Velocity
            lifetime[size] = 4.0f; // Lifetime
            size++;
        }
    }

    void update(float dt) {
        for (int i = 0; i < size; i++) {
            x[i] += vx[i] * dt;
            y[i] += vy[i] * dt;
            z[i] += vz[i] * dt;
            lifetime[i] -= dt;

            if (y[i] < 0.0f) // When raindrops reach the "floor"
            {
                y[i] = 0.0f; vy[i] = 0.0f;
            }

            // Remove dead particles by swapping with the last particle
            if (lifetime[i] <= 0) {
                destroy(i);
            }
        }
    }

    void destroy(int i)
    {
        --size;
        if (i != size) { // Only swap if this isn't the last particle
            x[i] = x[size];
            y[i] = y[size];
            z[i] = z[size];
            vx[i] = vx[size];
            vy[i] = vy[size];
            vz[i] = vz[size];
            lifetime[i] = lifetime[size];
        }
    }
};

#endif // PARTICLESYSTEM_H
