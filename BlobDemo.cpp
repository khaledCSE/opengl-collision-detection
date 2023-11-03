/*
 * The Blob demo.
 *
 */
#include <GL/glut.h>
#include "app.h"
#include "coreMath.h"
#include "pcontacts.h"
#include "pworld.h"
#include <stdio.h>
#include <cassert>

#define BLOB_COUNT 6
#define PLATFORM_COUNT 6
#define NUMBER_OF_PLATFORMS 6
#define BOX_MARGIN 5
#define NUMBER_OF_BLOBS 3

const Vector2 Vector2::GRAVITY = Vector2(0, -9.81);

/**
 * Platforms are two dimensional: lines on which the
 * particles can rest. Platforms are also contact generators for the physics.
 */

class Platform : public ParticleContactGenerator
{
public:
    Vector2 start;
    Vector2 end;
    /**
     * Holds a pointer to the particles we're checking for collisions with.
     */
    Particle *particle;

    virtual unsigned addContact(
        ParticleContact *contact,
        unsigned limit) const;
};

unsigned Platform::addContact(ParticleContact *contact,
                              unsigned limit) const
{

    // const static float restitution = 0.8f;
    // const static float restitution = 1.0f;
    unsigned used = 0;
    for (int i = 0; i < BLOB_COUNT; i++)
    {
        // Check for penetration
        Vector2 toParticle = particle[i].getPosition() - start;
        Vector2 lineDirection = end - start;

        float projected = toParticle * lineDirection;
        float platformSqLength = lineDirection.squareMagnitude();
        float squareRadius = particle[i].getRadius() * particle[i].getRadius();
        ;

        if (projected <= 0)
        {

            // The blob is nearest to the start point
            if (toParticle.squareMagnitude() < squareRadius)
            {
                // We have a collision
                contact->contactNormal = toParticle.unit();
                contact->restitution = coeff_of_restitution;
                contact->particle[0] = particle + i;
                contact->particle[1] = 0;
                contact->penetration = particle[i].getRadius() - toParticle.magnitude();
                used++;
                contact++;
            }
        }
        else if (projected >= platformSqLength)
        {
            // The blob is nearest to the end point
            toParticle = particle[i].getPosition() - end;
            if (toParticle.squareMagnitude() < squareRadius)
            {
                // We have a collision
                contact->contactNormal = toParticle.unit();
                contact->restitution = coeff_of_restitution;
                contact->particle[0] = particle + i;
                contact->particle[1] = 0;
                contact->penetration = particle[i].getRadius() - toParticle.magnitude();
                used++;
                contact++;
            }
        }
        else
        {
            // the blob is nearest to the middle.
            float distanceToPlatform = toParticle.squareMagnitude() - projected * projected / platformSqLength;
            if (distanceToPlatform < squareRadius)
            {
                // We have a collision
                Vector2 closestPoint = start + lineDirection * (projected / platformSqLength);

                contact->contactNormal = (particle[i].getPosition() - closestPoint).unit();
                contact->restitution = coeff_of_restitution;
                contact->particle[0] = particle + i;
                contact->particle[1] = 0;
                contact->penetration = particle[i].getRadius() - sqrt(distanceToPlatform);
                used++;
                contact++;
            }
        }
    }
    return used;
}

class BlobDemo : public Application
{
    Particle *blobs;

    Platform *platform;

    ParticleWorld world;

public:
    /** Creates a new demo object. */
    BlobDemo();
    virtual ~BlobDemo();

    /** Returns the window title for the demo. */
    virtual const char *getTitle();

    /** Display the particles. */
    virtual void display();

    /** Update the particle positions. */
    virtual void update();
    Platform *buildPlatform();
};

// Method definitions
BlobDemo::BlobDemo() : world(10, 5)
{

    width = 400;
    height = 400;
    nRange = 100.0;

    blobs = new Particle[BLOB_COUNT];
    platform = buildPlatform();

    for (int i = 0; i < PLATFORM_COUNT; i++)
    {
        platform[i].particle = blobs;
        world.getContactGenerators().push_back(platform + i);
    }

    for (int i = 0; i < BLOB_COUNT; i++)
    {
        blobs[i].setPosition(20.0 + i * 10, 90.0);
        blobs[i].setRadius(5);
        blobs[i].setVelocity(0, 0);
        // * Reducing it will increase the drag, hence a gradual slowing down
        blobs[i].setDamping(1);
        blobs[i].setAcceleration(Vector2::GRAVITY * 5.0f * (i + 1));
        blobs[i].setMass(100.0f);
        blobs[i].clearAccumulator();
        world.getParticles().push_back(blobs + i);

        // * Randomizing the initial directions
        blobs[i].setVelocity(randomFloatInRange(-10, 10), randomFloatInRange(-10, 10));
    }
}

BlobDemo::~BlobDemo()
{
    delete[] blobs;
    delete[] platform;
}

void BlobDemo::display()
{
    Application::display();
    for (int i = 0; i < PLATFORM_COUNT; i++)
    {
        const Vector2 &p0 = platform[i].start;
        const Vector2 &p1 = platform[i].end;

        glBegin(GL_LINES);
        glColor3f(0, 1, 1);
        glVertex2f(p0.x, p0.y);
        glVertex2f(p1.x, p1.y);
        glEnd();

        glColor3f(1, 0, 0);
    }
    for (int i = 0; i < BLOB_COUNT; i++)
    {
        const Vector2 &p = blobs[i].getPosition();
        glPushMatrix();
        glTranslatef(p.x, p.y, 0);
        glutSolidSphere(blobs[i].getRadius(), 12, 12);
        glPopMatrix();
    }
    glutSwapBuffers();
}
Platform *BlobDemo::buildPlatform()
{

    platform = new Platform[PLATFORM_COUNT];

    platform[0].start = Vector2(-50.0, 20.0);
    platform[0].end = Vector2(0, -20.0);
    platform[0].coeff_of_restitution = 1.0f;

    platform[1].start = Vector2(50.0, 20.0);
    platform[1].end = Vector2(0, -20.0);
    platform[1].coeff_of_restitution = 1.0f;

    // * Creating the box
    int box_edge_point = nRange - BOX_MARGIN;
    platform[PLATFORM_COUNT - 4].start = Vector2(-box_edge_point, -box_edge_point);
    platform[PLATFORM_COUNT - 4].end = Vector2(-box_edge_point, box_edge_point);
    platform[PLATFORM_COUNT - 4].coeff_of_restitution = 1.0f;

    platform[PLATFORM_COUNT - 3].start = Vector2(-box_edge_point, box_edge_point);
    platform[PLATFORM_COUNT - 3].end = Vector2(box_edge_point, box_edge_point);
    platform[PLATFORM_COUNT - 3].coeff_of_restitution = 1.0f;

    platform[PLATFORM_COUNT - 2].start = Vector2(box_edge_point, box_edge_point);
    platform[PLATFORM_COUNT - 2].end = Vector2(box_edge_point, -box_edge_point);
    platform[PLATFORM_COUNT - 2].coeff_of_restitution = 1.0f;

    platform[PLATFORM_COUNT - 1].start = Vector2(-box_edge_point, -box_edge_point);
    platform[PLATFORM_COUNT - 1].end = Vector2(box_edge_point, -box_edge_point);
    platform[PLATFORM_COUNT - 1].coeff_of_restitution = 1.0f;

    return platform;
}

void BlobDemo::update()
{
    // Recenter the axes
    float duration = timeinterval / 1000;
    // Run the simulation
    world.runPhysics(duration);

    Application::update();
}

const char *BlobDemo::getTitle()
{
    return "Blob Demo";
}

/**
 * Called by the common demo framework to create an application
 * object (with new) and return a pointer.
 */
Application *getApplication()
{
    return new BlobDemo();
}