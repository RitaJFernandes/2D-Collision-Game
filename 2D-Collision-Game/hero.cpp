#include "hero.h"

#include <QLine>
#include <QDebug>
#include <algorithm>
#include <memory>

Hero::Hero(QObject* parent)
    : QObject(parent)
    , m_position(400, 300)
    , m_radius(30)
    , m_score(0)
    , m_enemyCollisionFlag(false)
    , m_rewardCollisionFlag(false)
    , m_eatCoinFlag(false)
{
}

// Getters
QPointF Hero::getPosition() const
{
    return m_position;
}
void Hero::setPosition(const QPointF &position)
{
    if (m_position != position) {
        m_position = position;
        emit positionChanged();
    }
}
int Hero::getRadius() const
{
    return m_radius;
}
int Hero::getScore() const
{
    return m_score;
}
bool Hero::getEatCoinFlag() const
{
    return m_eatCoinFlag;
}

// Movement and Collision
//ENEMY
bool Hero::getEnemyCollisionFlag() const {
    return m_enemyCollisionFlag;
}
void Hero::setEnemyCollisionFlag(bool flag)
{
    if (m_enemyCollisionFlag != flag) {
        m_enemyCollisionFlag = flag;
        //qDebug() << "Flag value changed";
        emit enemyCollisionFlagChanged();
    }
}
void Hero::checkEnemyCollision(Enemy* enemy) {
     //qDebug() << __FUNCTION__ << "was called";

    if (!enemy) {
        setEnemyCollisionFlag(false);
        qDebug() << "ERROR: Reward object is not valid";
        return;
    }

    // Calculate the distance between hero and enemy centers
    int dx = m_position.x() - enemy->m_position.x();
    int dy = m_position.y() - enemy->m_position.y();
    int distance = std::sqrt(dx * dx + dy * dy);
    //qDebug() << "Enemy position" << enemy->m_position.x() << "," << enemy->m_position.y();
    //qDebug() << "Current distance is:" << distance;


    // Check if the distance is less than the sum of the radii
    if (distance < (m_radius + enemy->getRadius()))
    {
        setEnemyCollisionFlag(true);
        //qDebug() << "Collision with enemy detected. GAME OVER.";
    }
}


// REWARD
bool Hero::getRewardCollisionFlag() const {
    return m_rewardCollisionFlag;
}
void Hero::setRewardCollisionFlag(bool flag)
{
    if (m_rewardCollisionFlag != flag) {
        m_rewardCollisionFlag = flag;
        //qDebug() << "Flag value changed";
        emit rewardCollisionFlagChanged();
    }
}
void Hero::checkRewardCollision(Reward* reward) {
    //qDebug() << __FUNCTION__ << "was called";

    if (!reward) {
        setRewardCollisionFlag(false);
        qDebug() << "ERROR: Reward object is not valid";
        return;
    }

    // Determine the center of Hero and Reward
    QPointF centerHero(m_position.x() + m_radius, m_position.y() + m_radius);
//    qDebug() << "Hero position is" << m_position;
//    qDebug() << "Hero center is (" << (m_position.x() + m_radius) << "," << (m_position.y() + m_radius) << ")";
    QPointF centerReward(reward->m_position.x() + reward->getRadius(), reward->m_position.y() + reward->getRadius());
//    qDebug() << "Reward position is" << reward->getPosition();
//    qDebug() << "Reward center is (" << (reward->m_position.x() + reward->getRadius()) << "," << (reward->m_position.y() + reward->getRadius()) << ")";
//    qDebug() << "========================================";

    // Calculate the distance between hero and reward centers
    QLineF line(centerHero, centerReward);
    int distance = line.length();
    //qDebug() << "Distance vector length between centers is:" << distance;

    int sumRadii = (m_radius + reward->getRadius()) -10;

    // Check if the distance is less than the sum of the radii
    if (distance < sumRadii)
    {
        //setRewardCollisionFlag(true);
        //emit rewardCollisionFlagChanged();
        //qDebug() << "Collision with reward detected";

        reward->m_movementTimer.stop();
        reward->initializeRandomPosition();
        reward->m_collisionTimer.start();

        m_score += 1;
        emit scoreChanged();
        //qDebug() << "Score is now" << m_score;
    }
}


void Hero::setEatCoinFlag(bool flag)
{
    if (m_eatCoinFlag != flag) {
        m_eatCoinFlag = flag;
        emit eatCoinFlagChanged();
        //qDebug() << "Flag value changed";
    }
}
void Hero::eatCoin(Reward* reward) {
    //qDebug() << __FUNCTION__ << "was called";

    QPointF centerHero(m_position.x() + m_radius, m_position.y() + m_radius);
    QPointF centerReward(reward->m_position.x() + reward->getRadius(), reward->m_position.y() + reward->getRadius());

    QLineF line(centerHero, centerReward);
    int distance = line.length();

    qreal sumRadii = m_radius + reward->getRadius()+25;

    if(distance <= sumRadii){
        setEatCoinFlag(true);
        //qDebug() << "Eat coin flag set true";
        //qDebug() << "Reward position is" << reward->getPosition();
    } else {
        setEatCoinFlag(false);
        //qDebug() << "Eat coin flag set false";
    }
}


// HERO
void Hero::move(int direction) {
        qreal step = 20;

    switch (direction) {
        case 0: // Move down
            if (m_position.y() < 600 - m_radius * 2) {
                m_position.setY(m_position.y() + step);
                //qDebug() << "The player moved down";
            }
            break;

        case 1: // Move up
            if (m_position.y() > 0) {
                m_position.setY(m_position.y() - step);
                //qDebug() << "The player moved up";
            }
            break;

        case 2: // Move left
            if (m_position.x() > 0) {
                m_position.setX(m_position.x() - step);
                //qDebug() << "The player moved left";
            }
            break;

        case 3: // Move right
            if (m_position.x() < 800 - m_radius * 2) {
                m_position.setX(m_position.x() + step);
                //qDebug() << "The player moved right";
            }
            break;
    }

    emit positionChanged();
    //qDebug() << "Hero position is" << m_position;
}
