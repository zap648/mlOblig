#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <cstdlib>
const int maxParticles = 1000;

class ParticleSystem
{
public:    
    float x[maxParticles], y[maxParticles], z[maxParticles]; // Position
    float vx[maxParticles], vy[maxParticles], vz[maxParticles]; // Velocity
    float lifetime[maxParticles]; // Lifetime in seconds
    int size = 0;

    void create(float px, float py, float pz) {
        if (size < maxParticles) {
            float speed = static_cast<float>(rand() % 50 + 50) / 10.0f;
            x[size] = px; y[size] = py; x[size] = pz; // Position
            vx[size] = speed; vy[size] = speed; vz[size] = speed;  // Velocity
            lifetime[size] = 10.0f; // Lifetime
            size++;
        }
    }

    void update(float dt) {
        for (int i = 0; i < size; i++) {
            x[i] += vx[i] * dt;
            y[i] += vy[i] * dt;
            y[i] += vz[i] * dt;
            lifetime[i] -= dt;

            // Remove dead particles by swapping with the last particle
            if (lifetime[i] <= 0) {
                --size;
                if (i != size) { // Only swap if not the last particle
                    x[i] = x[size];
                    y[i] = y[size];
                    z[i] = y[size];
                    vx[i] = vx[size];
                    vy[i] = vy[size];
                    vz[i] = vz[size];
                    lifetime[i] = lifetime[size];
                }
            }
        }
    }
};

#endif // PARTICLESYSTEM_H
