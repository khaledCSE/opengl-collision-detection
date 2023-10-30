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
    const static float restitution = 1.0f;
    unsigned used = 0;

    // Check for penetration
    Vector2 toParticle = particle->getPosition() - start;
    Vector2 lineDirection = end - start;

    float projected = toParticle * lineDirection;
    float platformSqLength = lineDirection.squareMagnitude();
    float squareRadius = particle->getRadius() * particle->getRadius();
    ;

    if (projected <= 0)
    {

        // The blob is nearest to the start point
        if (toParticle.squareMagnitude() < squareRadius)
        {
            // We have a collision
            contact->contactNormal = toParticle.unit();
            contact->restitution = restitution;
            contact->particle[0] = particle;
            contact->particle[1] = 0;
            contact->penetration = particle->getRadius() - toParticle.magnitude();
            used++;
            contact++;
        }
    }
    else if (projected >= platformSqLength)
    {
        // The blob is nearest to the end point
        toParticle = particle->getPosition() - end;
        if (toParticle.squareMagnitude() < squareRadius)
        {
            // We have a collision
            contact->contactNormal = toParticle.unit();
            contact->restitution = restitution;
            contact->particle[0] = particle;
            contact->particle[1] = 0;
            contact->penetration = particle->getRadius() - toParticle.magnitude();
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

            contact->contactNormal = (particle->getPosition() - closestPoint).unit();
            contact->restitution = restitution;
            contact->particle[0] = particle;
            contact->particle[1] = 0;
            contact->penetration = particle->getRadius() - sqrt(distanceToPlatform);
            used++;
            contact++;
        }
    }

    return used;
}

class BlobDemo : public Application
{
    Particle *blob;

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
};

// Method definitions
BlobDemo::BlobDemo() : world(2, 1)
{
    width = 400;
    height = 400;
    nRange = 100.0;

    // Create the blob storage
    blob = new Particle;

    // Create the platform
    platform = new Platform[7];

    int margin = 5;

    platform[0].start = Vector2(0.0, 0.0);
    platform[0].end = Vector2(50.0, -10.0);

    platform[1].start = Vector2(-80.0, -30.0);
    platform[1].end = Vector2(-10.0, -70.0);

    platform[2].start = Vector2(0.0, -65.0);
    platform[2].end = Vector2(80.0, -30.0);

    // * Creating a box
    int box_edge_point = nRange - margin;
    platform[3].start = Vector2(-box_edge_point, -box_edge_point);
    platform[3].end = Vector2(-box_edge_point, box_edge_point);

    platform[4].start = Vector2(-box_edge_point, box_edge_point);
    platform[4].end = Vector2(box_edge_point, box_edge_point);

    platform[5].start = Vector2(box_edge_point, box_edge_point);
    platform[5].end = Vector2(box_edge_point, -box_edge_point);

    platform[6].start = Vector2(-box_edge_point, -box_edge_point);
    platform[6].end = Vector2(box_edge_point, -box_edge_point);

    // Make sure the platform knows which particle it should collide with.
    platform->particle = blob;

    world.getContactGenerators().push_back(platform);

    // Create the blob
    blob->setPosition(0.0, 90.0);
    blob->setRadius(5);
    blob->setVelocity(0, 0);
    // blob->setDamping(0.9);
    blob->setDamping(1.0);
    blob->setAcceleration(Vector2::GRAVITY * 20.0f);

    blob->setMass(30.0f);
    blob->clearAccumulator();
    world.getParticles().push_back(blob);
}

BlobDemo::~BlobDemo()
{
    delete blob;
}

void BlobDemo::display()
{
    Application::display();

    const Vector2 &p0 = platform[0].start;
    const Vector2 &p1 = platform[0].end;

    // * Box
    const Vector2 &p2 = platform[3].start;
    const Vector2 &p3 = platform[3].end;

    const Vector2 &p4 = platform[4].start;
    const Vector2 &p5 = platform[4].end;

    const Vector2 &p6 = platform[5].start;
    const Vector2 &p7 = platform[5].end;

    const Vector2 &p8 = platform[6].start;
    const Vector2 &p9 = platform[6].end;

    const Vector2 &p10 = platform[1].start;
    const Vector2 &p11 = platform[1].end;

    const Vector2 &p12 = platform[2].start;
    const Vector2 &p13 = platform[2].end;

    glBegin(GL_LINES);
    glColor3f(0, 1, 1);
    glVertex2f(p0.x, p0.y);
    glVertex2f(p1.x, p1.y);

    glVertex2f(p2.x, p2.y);
    glVertex2f(p3.x, p3.y);

    glVertex2f(p4.x, p4.y);
    glVertex2f(p5.x, p5.y);

    glVertex2f(p6.x, p6.y);
    glVertex2f(p7.x, p7.y);

    glVertex2f(p8.x, p8.y);
    glVertex2f(p9.x, p9.y);

    glVertex2f(p10.x, p10.y);
    glVertex2f(p11.x, p11.y);

    glVertex2f(p12.x, p12.y);
    glVertex2f(p13.x, p13.y);

    glEnd();

    glColor3f(1, 0, 0);

    const Vector2 &p = blob->getPosition();
    glPushMatrix();
    glTranslatef(p.x, p.y, 0);
    glutSolidSphere(blob->getRadius(), 12, 12);
    glPopMatrix();

    glutSwapBuffers();
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