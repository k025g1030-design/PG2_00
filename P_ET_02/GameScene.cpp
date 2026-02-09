#include "GameScene.hpp"
#include "Input.hpp"
#include "SceneTypes.hpp"

int FastRandInt(int min, int max) {
    static uint64_t x = 0x123456789ABCDEF;
    x ^= x << 7;
    x ^= x >> 9;
    uint64_t r = x * 2685821657736338717ULL;
    return min + (r % (max - min + 1));
}

bool ResolveBallBall(Actors::Ball& a, Actors::Ball& b) {
    Math::Vector2 n = b.position - a.position;
    float dist = n.Len();
    float penetration = (a.radius + b.radius) - dist;
    if (penetration > 0.0f) {
        n = n.Normalize();
        // 衝突直後の速度
        Math::Vector2 va = a.velocity;
        Math::Vector2 vb = b.velocity;
        // 反発係数
        float e = 0.8f;
        // 衝突直後の速度計算
        Math::Vector2 vaAfter = va.Reflect(n, e);
        Math::Vector2 vbAfter = vb.Reflect(n * -1.0f, e);
        a.velocity = vaAfter;
        b.velocity = vbAfter;
        // 食い込み修正
        float totalMass = a.mass + b.mass;
        float aMoveRatio = b.mass / totalMass;
        float bMoveRatio = a.mass / totalMass;
        a.position = a.position - n * penetration * aMoveRatio;
        b.position = b.position + n * penetration * bMoveRatio;
        return true;
    }
    return false;

}

void GameScene::OnEnter() {
    escButton_ = Component::Button({ 50, 30 }, { 40,  40 }, "ESC");
    frameCounter_ = 0;

    // プレイヤーの初期化処理
    Actors::Box box = Actors::Box(
        { kWindowWidth / 2.0f, kWindowHeight / 2.0f },
        { 50.0f, 50.0f },
        0x3e3e42ff
    );
    Actors::Ball ball = Actors::Ball(
        box.position,
        { 0.0f, 0.0f },
        box.size.x / 2.0f,
        1.0f,
        0x1e1e1eff,
        0
    );
    std::vector<Actors::BulletShot> result = {};
    for (int i = 0; i < kMaxMagazine; ++i) {
        Actors::BulletShot bs{
            Actors::Ball(
                { -100.0f, -100.0f }, // position
                { 0.0f, 0.0f },       // velocity
                6.0f,                 // radius
                1.0f,                 // mass
                RED,                  // color
                kMaxBulletLeftTime    // leftTime
            ),
            false // isActive
        };
        result.push_back(bs);
    }
    player_ = new Actors::Tank(box, ball, {0,0}, false, 0, 0);
    player_->bulletShots = result;


    

    for (int i = 0; i < kEnemySpawnCountMax; ++i) {
        Actors::EnemyBall eb = {
            Actors::Ball(
                { (float)FastRandInt(20, kWindowWidth), (float)FastRandInt(20, kWindowHeight) }, // position
                { 0.0f, 0.0f },       // velocity
                (float)FastRandInt(9, 20),                 // radius
                1.0f,                 // mass
                BLUE,                  // color
                kMaxBulletLeftTime    // leftTime
            ), false
        };
        enemyBalls_.push_back(eb);
    }
}

void GameScene::OnExit() {
}

void GameScene::Render() const {
    player_->Draw();
    for (const auto& bs : player_->bulletShots) {
        if (bs.isActive) {
            bs.Draw();
        }
    }

    for (auto& eb : enemyBalls_) {
        if (eb.isActive) {
            eb.Draw();
        }
    }

    escButton_.Render();
}

void GameScene::Update(EventBus& bus) {
    // プレイヤーの移動処理
    bus;
    Math::Vector2 playerInput = ReadCommand();
    if (playerInput.x != 0.0f || playerInput.y != 0.0f) {
        double angle = std::atan2f(playerInput.y, playerInput.x);
        playerInput.x = (cos((float)angle)) * moveSpeed;
        playerInput.y = (sin((float)angle)) * moveSpeed;
    }
    int moX = 0;
    int moY = 0;
    Novice::GetMousePosition(&moX, &moY);
    bool mouseDown = Novice::IsPressMouse(0);
    // メニューシーンの更新処理をここに追加
    if (escButton_.HandleMouse(moX, moY, mouseDown, prevMouseDown_)) {
        bus.Publish(SceneChangeEvent{ SceneID::Title });
        return;
    }
    prevMouseDown_ = mouseDown;

    player_->Move(playerInput, { static_cast<float>(moX), static_cast<float>(moY) });

    // プレイヤーの射撃処理
    if (mouseDown) {
        if (player_->shotCooldown == 0) {
            for (auto& bs : player_->bulletShots) {
                if (!bs.isActive) {
                    bs.isActive = true;
                    bs.ball.position = { player_->box.position.x  , player_->box.position.y  };
                    bs.ball.velocity = (player_->sight - player_->ball.position).Normalize() * 10.0f;
                    player_->isShooting = true;
                    player_->shotCooldown = kMaxShotCooldown;
                    break;
                }
            }
        }
    }
    if (player_->shotCooldown > 0) {
        player_->shotCooldown--;
    } else {
        player_->isShooting = false;
        player_->shotCooldown = 0;
    }

    // 弾の更新処理
    for (auto& bs : player_->bulletShots) {
        if (bs.isActive) {
            bs.ball.position = bs.ball.position + bs.ball.velocity;
            bs.ball.leftTime--;
            if (bs.ball.leftTime <= 0) {
                bs = {
                    Actors::Ball(
                        { -100.0f, -100.0f }, // position
                        { 0.0f, 0.0f },       // velocity
                        6.0f,                 // radius
                        1.0f,                 // mass
                        RED,                  // color
                        kMaxBulletLeftTime    // leftTime
                    ),
                    false // isActive
                };
            }
        }
    }

    // 敵の更新処理
    for (auto& eb : enemyBalls_) {
        if (eb.isActive) {
            eb.EnemyChasePlayer(player_->box.position, 10, 1/60.0f, 0.0f);
            eb.ball.leftTime--;
            if (eb.ball.leftTime <= 0) {
                eb = {
                    Actors::Ball(
                        { (float)FastRandInt(20, kWindowWidth), (float)FastRandInt(20, kWindowHeight) }, // position
                        { 0.0f, 0.0f },       // velocity
                        (float)FastRandInt(9, 20),                 // radius
                        1.0f,                 // mass
                        BLUE,                  // color
                        kMaxBulletLeftTime    // leftTime
                    ), false
                };
            }
        } 
    }


    // 敵の出現処理
    if (frameCounter_ % kEnemySpawnTime == 0) {
        for (auto& eb : enemyBalls_) {
            if (!eb.isActive) {
                eb.isActive = true;
                break;
            }
        }
    }
    if (frameCounter_ > INT_MAX) {
        frameCounter_ = 0;
    }
    frameCounter_++;



    // 弾と敵の当たり判定処理
    const int n = (int)enemyBalls_.size();
    const int b = (int)player_->bulletShots.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < b; ++j) {
            if (player_->bulletShots[j].isActive && enemyBalls_[i].isActive) {
                if (ResolveBallBall(enemyBalls_[i].ball, player_->bulletShots[j].ball)) {
                    // Deactivate bullet
                    player_->bulletShots[j].isActive = false;
                    // Reset enemy ball
                    enemyBalls_[i].isActive = false;

                }
            }
        }
        if (enemyBalls_[i].isActive) {
            if (ResolveBallBall(enemyBalls_[i].ball, player_->ball)) {
                // プレイヤーがダメージを受けた処理
                enemyBalls_[i].isActive = false;
                player_->health--;
                if (player_->health <= 0) {
                    bus.Publish(SceneChangeEvent{ SceneID::Title });
                }
            }
        }
    }

    
    
    /*const char c = ReadCommand();
    if (c == 'c') {
        bus.Publish(SceneChangeEvent{ SceneID::Result });
    } else if (c == 't') {
        bus.Publish(SceneChangeEvent{ SceneID::Title });
    } else if (c == 'q') {
        bus.Publish(SceneChangeEvent{ SceneID::Exit });
    } else {
        std::cout << "  (unknown command)\n";
    }*/
}

const char* GameScene::Name() const {
    return "GameScene";
}
