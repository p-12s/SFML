#include "gamescene.h"
#include <cassert>

static void updateGameOverLabel(sf::Text &label, const std::string &text)
{
    label.setString(text);
    utils::centerizeTextOrigin(label);
}

void initializeGameScene(GameScene &scene, const sf::Vector2f &sceneSize)
{
    bool succeed = scene.arial.loadFromFile("res/arialn.ttf");
    if (!succeed)
    {
        assert(false);
        exit(1);
    }

    initializeTank(scene.tank);
    initializeBombs(scene.bombs);

    scene.gameState = GameState::Playing;
    scene.gameOverBackground.setFillColor(TRANSPARENT_GRAY);
    scene.gameOverBackground.setSize(sceneSize);
    scene.gameOverLabel.setFont(scene.arial);
    scene.gameOverLabel.setFillColor(sf::Color::Black);
    scene.gameOverLabel.setPosition(0.5f * sceneSize);
}

void updateGameScene(GameScene &scene, float elapsedTime, sf::Clock &rechargeClock, sf::Vector2f &mousePosition)
{
    if (scene.gameState == GameState::Playing)
    {
        updateTank(scene.tank, elapsedTime, mousePosition);

        const float recharge = rechargeClock.getElapsedTime().asSeconds();
        if (recharge >= RECHARGE_TIME_IN_SECOND)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                Bullet bullet = createBullet(scene.tank, mousePosition);
                scene.bullets.push_back(bullet);
                rechargeClock.restart();
            }
        }

        for (auto &bullet : scene.bullets)
        {
            updateBullet(bullet, elapsedTime);
        }

        // Проверяем условие попадания пуль в бомбу

        for (auto &bullet : scene.bullets)
        {
            const sf::FloatRect bulletBounds = getBulletBounds(bullet);
            for (auto &bomb : scene.bombs)
            {
                if (getBombBounds(bomb).intersects(bulletBounds))
                {
                    injureBomb(bomb);
                    // удалить израсходованный bullet
                    continue;
                    //updateGameOverLabel(scene.gameOverLabel, "Game Over! You lose.");
                    //scene.gameState = GameState::PlayerLosed;
                }
            }
        }

        // Проверяем условие поражения - столкновение пакмана и призрака.
        /*const sf::FloatRect packmanBounds = getPackmanBounds(scene.packman);
        for (const auto &pair : scene.ghosts)
        {
            if (getGhostBounds(pair.second).intersects(packmanBounds))
            {
                updateGameOverLabel(scene.gameOverLabel, "Game Over! You lose.");
                scene.gameState = GameState::PlayerLosed;
            }
        }

        // Проверяем условие победы - всё печенье съедено.
        if (getRemainingCookies(scene) == 0)
        {
            updateGameOverLabel(scene.gameOverLabel, "Congratulations, you won!");
            scene.gameState = GameState::PlayerWon;
        }
        */
    }
}

/*std::string getGameSceneWindowTitle(const GameScene &scene)
{
    std::string title;
    switch (scene.gameState)
    {
    case GameState::Playing:
    {
        unsigned cookiesLeft = getRemainingCookies(scene);
        title = "Packman: " + std::to_string(cookiesLeft) + " Cookies Left";
    }
    break;
    case GameState::PlayerWon:
        title = "Packman: Congratulations, You Won!";
        break;
    case GameState::PlayerLosed:
        title = "Packman: Unfortunately, You Lose";
        break;
    }

    return title;
}*/

void drawGameScene(sf::RenderWindow &window, const GameScene &scene)
{
    //drawField(window, scene.field);

    // Персонажи рисуются после поля.
    drawTank(window, scene.tank);

    for (const auto &bomb : scene.bombs)
    {
        drawBomb(window, bomb);
    }

    for (const auto &bullet : scene.bullets)
    {
        drawBullet(window, bullet);
    }

    if ((scene.gameState == GameState::PlayerLosed) || (scene.gameState == GameState::PlayerWon))
    {
        window.draw(scene.gameOverBackground);
        window.draw(scene.gameOverLabel);
    }
}

void destroyGameScene(GameScene &scene)
{
    //destroyField(scene.field);
}