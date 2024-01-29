#include "enemy.h"
#include <QDebug>
#include <QPointF>

// Construct initialization
Enemy::Enemy(QObject *parent)
    : QObject(parent)
    , m_radius(25)
{

    // Initialize at random Position
    //QTimer::singleShot(std::rand() % 10000, this, &Enemy::initializeRandomPosition); //5 sec delay between each position initialization (for when creating more than 1 obj at the same time)
    initializeRandomPosition(); //you could also initialize it in the qml 1 by 1 since it's a slot

    // Connecting signals and slots
    // Movement
    m_movementTimer.setInterval(16); // 16 seconds -> corresponds to 60 FPS
    connect(&m_movementTimer, //sender
            &QTimer::timeout, //signal
            this, //receiver
            &Enemy::updateEnemyPosition); //slot
    m_movementTimer.start();
}

// Getters and setters
int Enemy::getRadius() const
{
    return m_radius;
}

QPointF Enemy::getPosition() const
{
    return m_position;
}

void Enemy::setPosition(const QPointF &position)
{
    if (m_position != position) {
        m_position = position;
        emit positionChanged();
    }
}

// Initializing at random position
void Enemy::initializeRandomPosition()
{
    int minXY = -100;
    int maxX = 800;
    int maxY = 600;

    int edge = std::rand() % 4; //[0-3]
    //qDebug() << "The edge value is" << edge;

    switch (edge) {
    case 0: // Left edge
        m_position = QPointF(minXY, std::rand() % maxY);
        m_initialDirection = QPointF(std::cos(qDegreesToRadians(std::rand() % 180)), std::sin(qDegreesToRadians(std::rand() % 180))); //creates a 2D vector
        //qDebug() << "The enemy is on the left";
        break;

    case 1: // Right edge
        m_position = QPointF(800, std::rand() % maxY);
        m_initialDirection = QPointF(std::cos(qDegreesToRadians(180 + std::rand() % 180)), std::sin(qDegreesToRadians(180 + std::rand() % 180)));
        //qDebug() << "The enemy is on the right";
        break;

    case 2: // Top edge
        m_position = QPointF(std::rand() % maxX, minXY);
        m_initialDirection = QPointF(std::cos(qDegreesToRadians(90 + std::rand() % 180)), std::sin(qDegreesToRadians(90 + std::rand() % 180)));
        //qDebug() << "The enemy is on the top";
        break;

    case 3: // Bottom edge
        m_position = QPointF(std::rand() % maxX, 600);
        m_initialDirection = QPointF(std::cos(qDegreesToRadians(270 + std::rand() % 180)), std::sin(qDegreesToRadians(270 + std::rand() % 180)));
        //qDebug() << "The enemy is on the bottom";
        break;
    }

    //qDebug() << "Random initial position:" << m_position;
    //qDebug() << "Random initial direction:" << m_initialDirection;
}


// Updating the object position
void Enemy::updateEnemyPosition()
{
    double speed = 2;

    m_position = m_position + m_initialDirection * speed;

    int minXY = -100;
    int maxX = 800;
    int maxY = 600;

    if (m_position.x() <= minXY || m_position.x() >= maxX || m_position.y() <= minXY || m_position.y() >= maxY) {

        int newAngle;
        if (m_position.x() <= minXY) {
            //Hit the left edge
            newAngle = std::rand() % 180;
            m_position.setX(minXY + 2); //forces to move away from the edge
        } else if (m_position.x() >= maxX) {
            //Hit the right edge
            newAngle = 180 + std::rand() % 180;
            m_position.setX(maxX - 2);
        } else if (m_position.y() <= minXY) {
            // Hit the top edge
            newAngle = 90 + std::rand() % 180;
            m_position.setY(minXY + 2);
        } else {
            // Hit the bottom edge
            newAngle = 270 + std::rand() % 180;
            m_position.setY(maxY - 2);
        }

        // Update direction with the new random angle
        m_initialDirection = QPointF(std::cos(qDegreesToRadians(newAngle)), std::sin(qDegreesToRadians(newAngle)));
    }

    emit positionChanged();
    //qDebug() << "Updated position is (" << m_position.x() << "," << m_position.y() << ")";
    //qDebug() << "Updated direction: (" << m_initialDirection.x() << "," << m_initialDirection.y() << ")";
}
