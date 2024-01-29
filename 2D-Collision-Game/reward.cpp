#include "Reward.h"
#include <QRandomGenerator>
#include <QCoreApplication>
#include <QPointF>
#include <QLineF>

Reward::Reward(QObject *parent)
    : QObject(parent)
    , m_radius(20)
{
    // Initialize random starting position
    initializeRandomPosition();

    // MOVEMENT
    //Triggers movement after a 5 sec interval
    QTimer::singleShot(5000, this, [this](){
        connect(&m_movementTimer, &QTimer::timeout, this, &Reward::moveReward);
        m_movementTimer.setInterval(16); //60 FPS
        m_movementTimer.start(); // Start the movement timer
    });

    //Timer to reset position after 5 sec of hitting an edge
    connect(&m_resetTimer, &QTimer::timeout, this, &Reward::resetRewardPosition);
    m_resetTimer.setInterval(5000);

    //Timer to reset position after collision
    connect(&m_collisionTimer, &QTimer::timeout, this, &Reward::resetRewardPositionOnCollision);
    m_collisionTimer.setInterval(5000);
}

// Getters and setters
int Reward::getRadius() const
{
    return m_radius;
}
void Reward::setPosition(const QPointF &position)
{
    if (m_position != position) {
        m_position = position;
        emit positionChanged();
    }
}
QPointF Reward::getPosition() const
{
    return m_position;
}


// Initial position
void Reward::initializeRandomPosition()
{
    int minXY = -100;
    int maxX = 800-(m_radius*2);
    int maxY = 600-(m_radius*2);

    int edge = std::rand() % 4; //try using other source of random numbers, might solve the spawning issue

    switch (edge) {
    case 0: // Left edge
        m_position = QPointF(minXY, std::rand() % maxY);
        m_initialDirection = QPointF(1,0);
        //qDebug() << "The reward is on the left";
        break;

    case 1: // Right edge
        m_position = QPointF(800, std::rand() % maxY);
        m_initialDirection = QPointF(-1,0);
        //qDebug() << "The reward is on the right";
        break;

    case 2: // Top edge
        m_position = QPointF(std::rand() % maxX, minXY);
        m_initialDirection = QPointF(0,1);
        //qDebug() << "The reward is on the top";
        break;

    case 3: // Bottom edge
        m_position = QPointF(std::rand() % maxX, 600);
        m_initialDirection = QPointF(0,-1);
        //qDebug() << "The reward is on the bottom";
        break;
    }

    //qDebug() << __FUNCTION__ << "called";
    emit positionChanged();
}

// Movement+Update position
void Reward::moveReward()
{
    int minXY = -100;
    int maxX = 800;
    int maxY = 600;
    int speed = 3;

    m_position = m_position + m_initialDirection * speed;
    //qDebug() << "Updated position is" << m_position;

    // Stop and reset position when reaching an edge
    if (m_position.x() <= minXY || m_position.x() >= maxX || m_position.y() <= minXY || m_position.y() >= maxY) {
        m_movementTimer.stop();
        m_resetTimer.start();
        //qDebug() << "Hit an edge! Reset timer started: 5, 4, 3, 2, 1...";
    }

    //qDebug() << __FUNCTION__ << "called";
    emit positionChanged();
}

// Reset position
// When hitting an edge
void Reward::resetRewardPosition()
{
    initializeRandomPosition();
    m_movementTimer.start();
    //qDebug() << __FUNCTION__ << "called";
}

// To be used in Hero collision
void Reward::resetRewardPositionOnCollision()
{
    m_movementTimer.start();
    //qDebug() << __FUNCTION__ << "called";
}

// Limit the distance between 2 reward objects
void Reward::limitDistance(const QPointF &otherRewardPosition)
{
    // Calculate the distance between this reward and another reward
    qreal distance = QLineF(m_position, otherRewardPosition).length();

    // Calculate the minimum distance required (diameter of the rewards)
    qreal minDistance = 2 * m_radius;

    if (distance < minDistance) {
        // If the distance is less than the minimum, adjust the position
        adjustPositionForMinimumDistance(otherRewardPosition);
        //qDebug() << "Enforcing distance between rewards";
    }
}

void Reward::adjustPositionForMinimumDistance(const QPointF &otherPosition)
{
    // Calculate the direction vector between this reward and another reward
    QPointF direction = otherPosition - m_position;
    direction /= QLineF(m_position, otherPosition).length(); // Normalize the direction vector

    // Calculate the new position that ensures the minimum distance
    QPointF newPosition = m_position + direction * m_radius;

    // Set the new position
    setPosition(newPosition);
}
