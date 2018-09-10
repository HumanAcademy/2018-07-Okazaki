#include "XLibrary11.hpp"
using namespace XLibrary;

enum Mode
{
	Title,
	Game,
	Clear,
	Over,
};

Camera camera;
Sprite bulletSprite(L"bullet.png");
Sprite bullet2Sprite(L"bullet2.png");
Sprite bullet3Sprite(L"bullet3.png");
Sprite laserSprite(L"laser.png");
Sprite laser2Sprite(L"enemylaser.png");
Sprite playerSprite(L"player.png");
Sprite playerBreakSprite(L"player_miss.png");
Sprite optionSprite(L"option.png");
Sprite enemySprite(L"enemy.png");
Sprite enemy2Sprite(L"enemy2.png");
Sprite enemy3Sprite(L"enemy3.png");
Sprite enemy4Sprite(L"enemy4.png");
Sprite enemyBreakSprite(L"enemy_break.png");
Sprite enemyBreakSprite2(L"enemy_break.png");
Sprite enemyBreakSprite3(L"enemy_break.png");
Sprite enemyBreakSprite4(L"enemy_break.png");
Sprite BossSprite(L"boss.png");
Sprite BossSprite2(L"boss3.png");
Sprite bossOptionA(L"boss2.png");
Sprite bossOptionB(L"boss2.png");
Sprite BossBreakSprite(L"boss_break.png");
Sprite bossOptionABreak(L"boss_break.png");
Sprite bossOptionBBreak(L"boss_break.png");
Sprite ItemSprite1(L"緑バッテリー - 2D_S.png");
Sprite ItemSprite2(L"緑バッテリー - 2D_M.png");
Sprite ItemSprite3_1(L"緑バッテリー - 2D_L.png");
Sprite ItemSprite3_2(L"緑バッテリー - 2D_L.png");

Sprite batterySprite000(L"battery000.png");
Sprite batterySprite005(L"battery005.png");
Sprite batterySprite010(L"battery010.png");
Sprite batterySprite015(L"battery015.png");
Sprite batterySprite020(L"battery020.png");
Sprite batterySprite025(L"battery025.png");
Sprite batterySprite030(L"battery030.png");
Sprite batterySprite035(L"battery035.png");
Sprite batterySprite040(L"battery040.png");
Sprite batterySprite045(L"battery045.png");
Sprite batterySprite050(L"battery050.png");
Sprite batterySprite055(L"battery055.png");
Sprite batterySprite060(L"battery060.png");
Sprite batterySprite065(L"battery065.png");
Sprite batterySprite070(L"battery070.png");
Sprite batterySprite075(L"battery075.png");
Sprite batterySprite080(L"battery080.png");
Sprite batterySprite085(L"battery085.png");
Sprite batterySprite090(L"battery090.png");
Sprite batterySprite095(L"battery095.png");
Sprite batterySprite100(L"battery100.png");

Sprite bossLife000(L"battery000 - コピー.png");
Sprite bossLife005(L"battery005 - コピー.png");
Sprite bossLife010(L"battery010 - コピー.png");
Sprite bossLife015(L"battery015 - コピー.png");
Sprite bossLife020(L"battery020 - コピー.png");
Sprite bossLife025(L"battery025 - コピー.png");
Sprite bossLife030(L"battery030 - コピー.png");
Sprite bossLife035(L"battery035 - コピー.png");
Sprite bossLife040(L"battery040 - コピー.png");
Sprite bossLife045(L"battery045 - コピー.png");
Sprite bossLife050(L"battery050 - コピー.png");
Sprite bossLife055(L"battery055 - コピー.png");
Sprite bossLife060(L"battery060 - コピー.png");
Sprite bossLife065(L"battery065 - コピー.png");
Sprite bossLife070(L"battery070 - コピー.png");
Sprite bossLife075(L"battery075 - コピー.png");
Sprite bossLife080(L"battery080 - コピー.png");
Sprite bossLife085(L"battery085 - コピー.png");
Sprite bossLife090(L"battery090 - コピー.png");
Sprite bossLife095(L"battery095 - コピー.png");
Sprite bossLife100(L"battery100 - コピー.png");

float velocity = 0.0f;
float velocity2 = 0.0f;
float velocity3 = 0.0f;
float velocity4 = 0.0f;
float velocity5_1 = 0.0f;
float velocity5_2 = 0.0f;

int counter = 0;
int counter2 = 0;

int playerLife = 100;
int enemyLife = 30;
int enemy2Life = 10;
int enemy3Life = 15;
int enemy4Life = 5;
int bossLife = 1000;
int BossOptionALife = 100;
int BossOptionBLife = 100;

int enemyKill = 0;
int enemy2Kill = 0;
int enemy3Kill = 0;
int enemy4Kill = 0;
int BossOptionAKill = 0;
int BossOptionBKill = 0;
int totalKill = 0;

int playerBreak = 0;
int enemyBreak = 0;
int enemy2Break = 0;
int enemy3Break = 0;
int enemy4Break = 0;
int bossBreak = 0;
int bossOptionBreakA = 0;
int bossOptionBreakB = 0;

bool DropFlag1 = true;
bool DropFlag2 = true;
bool DropFlag3_1 = true;
bool DropFlag3_2 = true;

class Bullet
{
public:
	Float3 position;

	// 初期化（コンストラクタ）
	Bullet()
	{
		position = Float3(0.0f, 0.0f, 0.0f);
	}
	void Update()
	{
		position.y += 8.0f;

		bulletSprite.position = position;
		bulletSprite.Draw();
	}
};

class Laser
{
public:
	Float3 position;

	// 初期化（コンストラクタ）
	Laser()
	{
		position = Float3(0.0f, 0.0f, 0.0f);
	}
	void Update()
	{
		position.y -= 12.0f;

		laser2Sprite.position = position;
		laser2Sprite.scale = 2.0f;
		laser2Sprite.Draw();
	}
};

class Player
{
public:
	Float3 position;
	std::vector<Bullet> bullets;
	int bulletInterval = 0;
	int playerPower = 0;

	Player()
	{
		position = Float3(0.0f, -Window::GetSize().y / 2.0f + 100.0f, 0.0f);
	}
	void Update()
	{
		if (playerBreak == 0)
		{
			playerSprite.position = position;
			playerSprite.scale = 1.5f;

			if (bossBreak == 0)
			{
				if (Input::GetKey(VK_LEFT))
				{
					position.x -= 3.0f;
				}
				if (Input::GetKey(VK_RIGHT))
				{
					position.x += 3.0f;
				}
				if (Input::GetKey(VK_UP))
				{
					position.y += 3.0f;
				}
				if (Input::GetKey(VK_DOWN))
				{
					position.y -= 3.0f;
				}
			}
			
			if (position.x < -Window::GetSize().x / 2.0f + 12.0f)
			{
				position.x = -Window::GetSize().x / 2.0f + 12.0f;
			}
			if (position.x > Window::GetSize().x / 2.0f - 12.0f)
			{
				position.x = Window::GetSize().x / 2.0f - 12.0f;
			}
			if (position.y < -Window::GetSize().y / 2.0f + 12.0f)
			{
				position.y = -Window::GetSize().y / 2.0f + 12.0f;
			}
			if (position.y > Window::GetSize().y / 2.0f - 12.0f)
			{
				position.y = Window::GetSize().y / 2.0f - 12.0f;
			}

			Bullet bullet;

			for (int i = 0; i < bullets.size(); i++)
			{
				bullets[i].Update();

				if (bullets[i].position.x < -Window::GetSize().x / 2.0f ||
					bullets[i].position.x > Window::GetSize().x / 2.0f ||
					bullets[i].position.y < -Window::GetSize().y / 2.0f ||
					bullets[i].position.y > Window::GetSize().y / 2.0f)
				{
					bullets.erase(bullets.begin() + i);
					i--;
				}
			}

			if (bossBreak == 0)
			{
				if (bulletInterval == 0)
				{
					bullet.position = position;
					bullets.push_back(bullet);
				}
				bulletInterval++;
				if (bulletInterval == 6)
				{
					bulletInterval = 0;
				}
			}

			playerSprite.Draw();
		}
		else
		{
			playerBreakSprite.position = position;
			playerBreakSprite.scale = 1.5f;

			if (playerBreak > 0 && playerBreak <= 40)
			{
				if (playerBreak > 0 && playerBreak <= 10)
				{
					playerBreakSprite.color.w = 1.0f;
				}
				else if (playerBreak > 10 && playerBreak <= 20)
				{
					playerBreakSprite.color.w = 0.75f;
				}
				else if (playerBreak > 20 && playerBreak <= 30)
				{
					playerBreakSprite.color.w = 0.5f;
				}
				else if (playerBreak > 30 && playerBreak <= 40)
				{
					playerBreakSprite.color.w = 0.25f;
				}
				playerBreakSprite.Draw();
			}
		}
	}
	bool CheckHit(Float3 position)
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			if (std::hypotf(bullets[i].position.x - position.x, bullets[i].position.y - position.y) < 16.0f)
			{
				bullets[i].position.y = 3000.0f;
				return true;
			}
		}
		return false;
	}
};

class EnemyBullet
{
public:
	Float3 position;
	float angle;

	// 初期化（コンストラクタ）
	EnemyBullet()
	{
		position = Float3(0.0f, 0.0f, 0.0f);
		angle = 0.0f;
	}
	void Update()
	{
		position.x += cosf(XMConvertToRadians(angle));
		position.y += sinf(XMConvertToRadians(angle));

		bullet2Sprite.position = position;
		bullet2Sprite.Draw();
	}
};

class Enemy2Bullet
{
public:
	Float3 position;
	float angle;

	// 初期化（コンストラクタ）
	Enemy2Bullet()
	{
		position = Float3(0.0f, 0.0f, 0.0f);
		angle = 270.0f;
	}
	void Update()
	{
		position.y -= 3.0f;

		bullet2Sprite.position = position;
		bullet2Sprite.Draw();
	}
};

class Enemy3Bullet
{
public:
	Float3 position;
	float angle;

	// 初期化（コンストラクタ）
	Enemy3Bullet()
	{
		position = Float3(0.0f, 0.0f, 0.0f);
		angle = 270.0f;
	}
	void Update()
	{
		position.y -= 5.0f;

		bullet2Sprite.position = position;
		bullet2Sprite.Draw();
	}
};

class BossBullet
{
public:
	Float3 position;
	float angle;

	// 初期化（コンストラクタ）
	BossBullet()
	{
		position = Float3(0.0f, 0.0f, 0.0f);
		angle = 0.0f;
	}
	void Update()
	{
		position.x += cosf(XMConvertToRadians(angle));
		position.y += sinf(XMConvertToRadians(angle));

		bullet3Sprite.position = position;
		bullet3Sprite.scale = 2.0f;
		bullet3Sprite.Draw();
	}
};

class EnemyLaser
{
public:
	Float3 position;

	// 初期化（コンストラクタ）
	EnemyLaser()
	{
		position = Float3(0.0f, 0.0f, 0.0f);
	}
	void Update()
	{
		position.y -= 12.0f;

		laser2Sprite.position = position;
		laser2Sprite.scale = 3.0f;
		laser2Sprite.Draw();
	}
};

class Enemy
{
public:
	Float3 position;
	float angle;
	std::vector<EnemyBullet> enemyBullets;
	int enemyBulletInterval = 0;
	int enemyCount = 0;

	// 初期化（コンストラクタ）
	Enemy()
	{
		position = Float3(0.0f, Window::GetSize().y / 2.0f + 100.0f, 0.0f);
	}
	void Update()
	{
		for (int i = 0; i < enemyBullets.size(); i++)
		{
			enemyBullets[i].Update();

			if (enemyBullets[i].position.x < -Window::GetSize().x / 2.0f ||
				enemyBullets[i].position.x > Window::GetSize().x / 2.0f ||
				enemyBullets[i].position.y < -Window::GetSize().y / 2.0f ||
				enemyBullets[i].position.y > Window::GetSize().y / 2.0f)
			{
				enemyBullets.erase(enemyBullets.begin() + i);
				i--;
			}
		}

		if (enemyBreak == 0)
		{
			if (position.y <= Window::GetSize().y / 3.0f)
			{
				enemyCount++;
				velocity3 += 0.1f;
			}
			else
			{
				enemyCount = 0;
				velocity3 = 0.0f;
			}

			if (velocity3 >= 3.0f)
			{
				velocity3 = 3.0f;
			}

			position.y -= -velocity3 + 3.0f;
			angle += 5.0f;
			EnemyBullet enemyBullet;
			enemyBulletInterval++;

			if (enemyCount > 30)
			{
				if (enemyBulletInterval == 1)
				{
					enemyBullet.position = position;
					enemyBullet.angle = angle;
					enemyBullets.push_back(enemyBullet);
				}
			}

			if (enemyBulletInterval >= 2)
			{
				enemyBulletInterval = 0;
			}

			if (enemyLife <= 0)
			{
				enemyBreak++;
				enemyKill++;
				playerLife += 20;
			}

			enemy4Sprite.position = position;
			enemy4Sprite.scale = 2.0f;
			enemy4Sprite.Draw();
		}
		else
		{
			enemyBreak++;
			enemyBreakSprite.position = position;
			enemyBreakSprite.scale = 2.0f;

			if (enemyBreak > 0 && enemyBreak <= 20)
			{
				if (enemyBreak > 0 && enemyBreak <= 4)
				{
					enemyBreakSprite.color.w = 1.0f;
				}
				else if (enemyBreak > 4 && enemyBreak <= 8)
				{
					enemyBreakSprite.color.w = 0.75f;
				}
				else if (enemyBreak > 8 && enemyBreak <= 12)
				{
					enemyBreakSprite.color.w = 0.5f;
				}
				else if (enemyBreak > 12 && enemyBreak <= 16)
				{
					enemyBreakSprite.color.w = 0.25f;
				}
				else
				{
					enemyBreakSprite.color.w = 0.0f;
				}
				enemyBreakSprite.Draw();
			}
			else
			{
				if (enemyKill >= 5)
				{
					position = Float3(0.0f, -Window::GetSize().y / 2.0f - 100.0f, 0.0f);
				}
				else
				{
					position = Float3(0.0f, Window::GetSize().y * 3.0f, 0.0f);
				}
				enemyLife = 30 + enemyKill * 10;
				enemyBreak = 0;
			}
		}
	}
	bool CheckHit(Float3 position)
	{
		for (int i = 0; i < enemyBullets.size(); i++)
		{
			if (std::hypotf(enemyBullets[i].position.x - position.x, enemyBullets[i].position.y - position.y) < 6.0f)
			{
				enemyBullets[i].position.y = -3000.0f;
				return true;
			}
		}

		return false;
	}
};

class Enemy2
{
public:
	Float3 position;
	float angle;
	std::vector<Enemy2Bullet> enemy2Bullets;
	int enemy2BulletInterval = 0;

	// 初期化（コンストラクタ）
	Enemy2()
	{
		position = Float3(240.0f, Window::GetSize().y / 2.0f + 100.0f, 0.0f);
	}
	void Update()
	{
		for (int i = 0; i < enemy2Bullets.size(); i++)
		{
			enemy2Bullets[i].Update();

			if (enemy2Bullets[i].position.x < -Window::GetSize().x / 2.0f ||
				enemy2Bullets[i].position.x > Window::GetSize().x / 2.0f ||
				enemy2Bullets[i].position.y < -Window::GetSize().y / 2.0f ||
				enemy2Bullets[i].position.y > Window::GetSize().y / 2.0f)
			{
				enemy2Bullets.erase(enemy2Bullets.begin() + i);
				i--;
			}
		}
		
		if (enemy2Break == 0)
		{
			position.y -= 0.5f;
			if (position.y <= 180.0f)
			{
				position.x -= 2.0f;
			}

			Enemy2Bullet enemy2Bullet;
			enemy2BulletInterval++;

			if (enemy2BulletInterval == 1)
			{
				enemy2Bullet.position = position;
				enemy2Bullet.angle = angle;
				enemy2Bullets.push_back(enemy2Bullet);
			}
			if (enemy2BulletInterval == 20)
			{
				enemy2BulletInterval = 0;
			}

			if (enemy2Life == 0)
			{
				enemy2Kill++;
				enemy2Break++;
			}
			if (position.x <= -Window::GetSize().x)
			{
				if (enemy2Kill >= 10)
				{
					position = Float3(-240.0f, Window::GetSize().y / 2.0f, 0.0f);
				}
				else
				{
					position = Float3(240.0f, Window::GetSize().y / 2.0f, 0.0f);
				}
				enemy2Life = 5;
			}
			enemy2Sprite.position = position;
			enemy2Sprite.scale = 2.0f;
			enemy2Sprite.Draw();
		}
		else
		{
			enemy2Break++;
			enemyBreakSprite2.position = position;
			enemyBreakSprite2.scale = 2.0f;

			if (enemy2Break > 0 && enemy2Break <= 20)
			{
				if (enemy2Break > 0 && enemy2Break <= 4)
				{
					enemyBreakSprite2.color.w = 1.0f;
				}
				else if (enemy2Break > 4 && enemy2Break <= 8)
				{
					enemyBreakSprite2.color.w = 0.75f;
				}
				else if (enemy2Break > 8 && enemy2Break <= 12)
				{
					enemyBreakSprite2.color.w = 0.5f;
				}
				else if (enemy2Break > 12 && enemy2Break <= 16)
				{
					enemyBreakSprite2.color.w = 0.25f;
				}
				else
				{
					enemyBreakSprite2.color.w = 0.0f;
				}
				enemyBreakSprite2.Draw();
			}
			else
			{
				if (enemy2Kill >= 10)
				{
					position = Float3(-240.0f, Window::GetSize().y / 2.0f, 0.0f);
				}
				else
				{
					position = Float3(240.0f, Window::GetSize().y / 2.0f, 0.0f);
				}
				enemy2Life = 5;
				enemy2Break = 0;
			}
		}
	}
	bool CheckHit(Float3 position)
	{
		for (int i = 0; i < enemy2Bullets.size(); i++)
		{
			if (std::hypotf(enemy2Bullets[i].position.x - position.x, enemy2Bullets[i].position.y - position.y) < 6.0f)
			{
				enemy2Bullets[i].position.y = -3000.0f;
				return true;
			}
		}
		return false;
	}
};

class Enemy3
{
public:
	Float3 position;
	float angle;
	std::vector<Enemy3Bullet> enemy3Bullets;
	int enemy3BulletInterval = 0;

	// 初期化（コンストラクタ）
	Enemy3()
	{
		position = Float3(-320.0f, Window::GetSize().y / 2.0f * 2, 0.0f);
	}
	void Update()
	{
		for (int i = 0; i < enemy3Bullets.size(); i++)
		{
			enemy3Bullets[i].Update();

			if (enemy3Bullets[i].position.x < -Window::GetSize().x / 2.0f ||
				enemy3Bullets[i].position.x > Window::GetSize().x / 2.0f ||
				enemy3Bullets[i].position.y < -Window::GetSize().y / 2.0f ||
				enemy3Bullets[i].position.y > Window::GetSize().y / 2.0f)
			{
				enemy3Bullets.erase(enemy3Bullets.begin() + i);
				i--;
			}
		}
		
		if (enemy3Break == 0)
		{
			if (position.y <= 230.0f && position.y >= 164.0f)
			{
				velocity += 0.05f;
			}
			else
			{
				velocity -= 0.05f;
			}

			if (velocity > 4.0f)
			{
				velocity = 4.0f;
			}
			if (velocity < 0.0f)
			{
				velocity = 0.0f;
			}

			if (position.y >= Window::GetSize().y / 2.0f)
			{
				position.x += 0.0f;
				velocity = 0.0f;
			}

			position.x += -velocity + 2.0f;
			position.y -= 0.3f;
			Enemy3Bullet enemy3Bullet;

			enemy3BulletInterval++;

			if (enemy3BulletInterval == 1)
			{
				enemy3Bullet.position = position;
				enemy3Bullet.angle = angle;
				enemy3Bullets.push_back(enemy3Bullet);
			}
			if (enemy3BulletInterval == 30)
			{
				enemy3BulletInterval = 0;
			}

			if (enemy3Life == 0)
			{
				playerLife += 10;
				enemy3Kill++;
				enemy3Break++;
			}
			if (position.y <= 80.0f)
			{
				if (enemy3Kill >= 5)
				{
					position = Float3(320.0f, 80.0f, 0.0f);
				}
				else
				{
					position = Float3(-320.0f, Window::GetSize().y / 2.0f, 0.0f);
				}
				enemy3Life = 15;
			}
			enemy3Sprite.position = position;
			enemy3Sprite.scale = 2.0f;
			enemy3Sprite.Draw();
		}
		else
		{
			enemy3Break++;
			enemyBreakSprite3.position = position;
			enemyBreakSprite3.scale = 2.0f;

			if (enemy3Break > 0 && enemy3Break <= 20)
			{
				if (enemy3Break > 0 && enemy3Break <= 4)
				{
					enemyBreakSprite3.color.w = 1.0f;
				}
				else if (enemy3Break > 4 && enemy3Break <= 8)
				{
					enemyBreakSprite3.color.w = 0.75f;
				}
				else if (enemy3Break > 8 && enemy3Break <= 12)
				{
					enemyBreakSprite3.color.w = 0.5f;
				}
				else if (enemy3Break > 12 && enemy3Break <= 16)
				{
					enemyBreakSprite3.color.w = 0.25f;
				}
				else
				{
					enemyBreakSprite3.color.w = 0.0f;
				}
				enemyBreakSprite3.Draw();
			}
			else
			{
				if (enemy3Kill >= 5)
				{
					position = Float3(320.0f, 80.0f, 0.0f);
				}
				else
				{
					position = Float3(-320.0f, Window::GetSize().y / 2.0f, 0.0f);
				}
				enemy3Life = 15;
				enemy3Break = 0;
			}
		}
	}
	bool CheckHit(Float3 position)
	{
		for (int i = 0; i < enemy3Bullets.size(); i++)
		{
			if (std::hypotf(enemy3Bullets[i].position.x - position.x, enemy3Bullets[i].position.y - position.y) < 6.0f)
			{
				enemy3Bullets[i].position.y = -3000.0f;
				return true;
			}
		}

		return false;
	}
};

class Enemy4
{
public:
	Float3 position;
	float angle;
	std::vector<Enemy2Bullet> enemy2Bullets;
	int enemy2BulletInterval = 0;
	int enemy4Count = 0;

	// 初期化（コンストラクタ）
	Enemy4()
	{
		position = Float3(-270.0f, Window::GetSize().y / 2.0f + 150.0f, 0.0f);
	}
	void Update()
	{
		for (int i = 0; i < enemy2Bullets.size(); i++)
		{
			enemy2Bullets[i].Update();

			if (enemy2Bullets[i].position.x < -Window::GetSize().x / 2.0f ||
				enemy2Bullets[i].position.x > Window::GetSize().x / 2.0f ||
				enemy2Bullets[i].position.y < -Window::GetSize().y / 2.0f ||
				enemy2Bullets[i].position.y > Window::GetSize().y / 2.0f)
			{
				enemy2Bullets.erase(enemy2Bullets.begin() + i);
				i--;
			}
		}

		if (enemy4Break == 0)
		{
			if (position.y <= Window::GetSize().y / 2.0f + 16.0f)
			{
				enemy4Count++;
			}
			else
			{
				enemy4Count = 0;
			}

			if (enemy4Count >= 180)
			{
				velocity2 += 0.08f;
			}
			else
			{
				velocity2 = 0.0f;
			}

			if (velocity2 > 4.0f)
			{
				velocity2 = 4.0f;
			}

			position.x += velocity2 / 2.0f + 1.0f;
			position.y -= -velocity2 + 2.0f;
			
			Enemy2Bullet enemy2Bullet;
			enemy2BulletInterval++;

			if (enemy2BulletInterval == 20)
			{
				enemy2Bullet.position = position;
				enemy2Bullet.angle = angle;
				enemy2Bullets.push_back(enemy2Bullet);
			}
			if (enemy2BulletInterval == 40)
			{
				enemy2BulletInterval = 0;
			}

			if (enemy4Life == 0)
			{
				enemy4Break++;
				enemy4Kill++;
			}
			if (position.x >= Window::GetSize().x / 2.0f + 16.0f)
			{
				if (enemy4Kill >= 20)
				{
					position = Float3(Window::GetSize().x / 2.0f + 16.0f, Window::GetSize().y / 2.0f + 150.0f, 0.0f);
				}
				else
				{
					position = Float3(-270.0f, Window::GetSize().y / 2.0f + 150.0f, 0.0f);
				}
				enemy4Life = 5;
			}
			
			enemySprite.position = position;
			enemySprite.scale = 2.0f;
			enemySprite.Draw();
		}
		else
		{
			enemy4Break++;
			enemyBreakSprite4.position = position;
			enemyBreakSprite4.scale = 2.0f;

			if (enemy4Break > 0 && enemy4Break <= 20)
			{
				if (enemy4Break > 0 && enemy4Break <= 4)
				{
					enemyBreakSprite4.color.w = 1.0f;
				}
				else if (enemy4Break > 4 && enemy4Break <= 8)
				{
					enemyBreakSprite4.color.w = 0.75f;
				}
				else if (enemy4Break > 8 && enemy4Break <= 12)
				{
					enemyBreakSprite4.color.w = 0.5f;
				}
				else if (enemy4Break > 12 && enemy4Break <= 16)
				{
					enemyBreakSprite4.color.w = 0.25f;
				}
				else
				{
					enemyBreakSprite4.color.w = 0.0f;
				}
				enemyBreakSprite4.Draw();
			}
			else
			{
				if (enemy4Kill >= 20)
				{
					position = Float3(Window::GetSize().x / 2.0f + 16.0f, Window::GetSize().y / 2.0f + 150.0f, 0.0f);
				}
				else
				{
					position = Float3(-270.0f, Window::GetSize().y / 2.0f + 150.0f, 0.0f);
				}
				enemy4Life = 5;
				enemy4Break = 0;
			}
		}
	}
	bool CheckHit(Float3 position)
	{
		for (int i = 0; i < enemy2Bullets.size(); i++)
		{
			if (std::hypotf(enemy2Bullets[i].position.x - position.x, enemy2Bullets[i].position.y - position.y) < 6.0f)
			{
				enemy2Bullets[i].position.y = -3000.0f;
				return true;
			}
		}
		return false;
	}
};

class Boss
{
public:
	Float3 position;
	float angle;
	std::vector<BossBullet> bossBullets;
	std::vector<EnemyLaser> enemyLasers;
	int bossBulletInterval = 0;
	int bossCount = 0;

	// 初期化（コンストラクタ）
	Boss()
	{
		position = Float3(0.0f, Window::GetSize().y / 2.0f + 140.0f, 0.0f);
	}
	void Update()
	{
		if (bossBreak == 0)
		{
			if (position.y <= Window::GetSize().y / 4.0f)
			{
				bossCount++;
				velocity4 += 0.05f;
			}
			else
			{
				bossCount = 0;
				velocity4 = 0.0f;
			}

			if (velocity4 >= 1.0f)
			{
				velocity4 = 1.0f;
			}

			position.y -= -velocity4 + 1.0f;
			angle += 4.7f;
			BossBullet bossBullet;
			EnemyLaser enemyLaser;
			bossBulletInterval++;

			if (bossCount > 120 && bossCount <= 540)
			{
				if (bossBulletInterval == 1)
				{
					bossBullet.position = position;
					bossBullet.angle = angle;
					bossBullets.push_back(bossBullet);
				}
			}
			if (bossCount > 840 && bossCount <= 1140)
			{
				enemyLaser.position = position;
				enemyLasers.push_back(enemyLaser);
			}

			if (bossCount >= 1200)
			{
				bossCount = 0;
			}

			if (bossBulletInterval >= 2)
			{
				bossBulletInterval = 0;
			}

			for (int i = 0; i < bossBullets.size(); i++)
			{
				bossBullets[i].Update();

				if (bossBullets[i].position.x < -Window::GetSize().x / 2.0f - 16.0f ||
					bossBullets[i].position.x > Window::GetSize().x / 2.0f + 16.0f ||
					bossBullets[i].position.y < -Window::GetSize().y / 2.0f - 16.0f ||
					bossBullets[i].position.y > Window::GetSize().y / 2.0f + 16.0f)
				{
					bossBullets.erase(bossBullets.begin() + i);
					i--;
				}
			}
			for (int i = 0; i < enemyLasers.size(); i++)
			{
				enemyLasers[i].Update();

				if (enemyLasers[i].position.x < -Window::GetSize().x ||
					enemyLasers[i].position.x > Window::GetSize().x / 2.0f ||
					enemyLasers[i].position.y < -Window::GetSize().y / 2.0f ||
					enemyLasers[i].position.y > Window::GetSize().y / 2.0f)
				{
					enemyLasers.erase(enemyLasers.begin() + i);
					i--;
				}
			}


			if (bossCount > 60 && bossCount <= 70 || bossCount > 80 && bossCount <= 90 || bossCount > 100 && bossCount <= 110 ||
				bossCount > 780 && bossCount <= 790 || bossCount > 800 && bossCount <= 810 || bossCount > 820 && bossCount <= 830)
			{
				BossSprite2.position = position;
				BossSprite2.scale = 8.0f;
				BossSprite2.Draw();
			}
			else
			{
				BossSprite.position = position;
				BossSprite.scale = 8.0f;
				BossSprite.Draw();
			}
		}
		else
		{
			BossBreakSprite.position = position;
			BossBreakSprite.scale = 8.0f;
			
			if (bossBreak > 0 && bossBreak <= 40)
			{
				if (bossBreak > 0 && bossBreak <= 10)
				{
					BossBreakSprite.color.w = 1.0f;
				}
				else if (bossBreak > 10 && bossBreak <= 20)
				{
					BossBreakSprite.color.w = 0.75f;
				}
				else if (bossBreak > 20 && bossBreak <= 30)
				{
					BossBreakSprite.color.w = 0.5f;
				}
				else if (bossBreak > 30 && bossBreak <= 40)
				{
					BossBreakSprite.color.w = 0.25f;
				}
				BossBreakSprite.Draw();
			}
		}

	}
	bool CheckHit(Float3 position)
	{
		for (int i = 0; i < bossBullets.size(); i++)
		{
			if (std::hypotf(bossBullets[i].position.x - position.x, bossBullets[i].position.y - position.y) < 12.0f)
			{
				bossBullets[i].position.y = -3000.0f;
				return true;
			}
		}
		for (int i = 0; i < enemyLasers.size(); i++)
		{
			if (std::hypotf(enemyLasers[i].position.x - position.x, enemyLasers[i].position.y - position.y) < 100.0f)
			{
				return true;
			}
		}

		return false;
	}
};

class BossOptionA
{
public:
	Float3 position;
	float angle;
	std::vector<EnemyBullet> enemyBullets;
	int OptionABulletInterval = 0;
	int bossOptionACount = 0;

	// 初期化（コンストラクタ）
	BossOptionA()
	{
		position = Float3(-150.0f, Window::GetSize().y / 2.0f + 140.0f, 0.0f);
	}
	void Update()
	{
		for (int i = 0; i < enemyBullets.size(); i++)
		{
			enemyBullets[i].Update();

			if (enemyBullets[i].position.x < -Window::GetSize().x / 2.0f ||
				enemyBullets[i].position.x > Window::GetSize().x / 2.0f ||
				enemyBullets[i].position.y < -Window::GetSize().y / 2.0f ||
				enemyBullets[i].position.y > Window::GetSize().y / 2.0f)
			{
				enemyBullets.erase(enemyBullets.begin() + i);
				i--;
			}
		}

		if (bossOptionBreakA == 0)
		{
			if (position.y <= Window::GetSize().y / 4.0f)
			{
				bossOptionACount++;
				velocity5_1 += 0.05f;
			}
			else
			{
				bossOptionACount = 0;
				velocity5_1 = 0.0f;
			}

			if (velocity5_1 >= 1.0f)
			{
				velocity5_1 = 1.0f;
			}
			position.y -= -velocity5_1 + 1.0f;

			angle -= 6.5f;
			EnemyBullet enemyBullet;
			OptionABulletInterval++;

			if (bossOptionACount > 30)
			{
				if (OptionABulletInterval == 1)
				{
					enemyBullet.position = position;
					enemyBullet.angle = angle;
					enemyBullets.push_back(enemyBullet);
				}
			}

			if (OptionABulletInterval >= 3)
			{
				OptionABulletInterval = 0;
			}

			if (BossOptionALife == 0)
			{
				playerLife += 30;
				BossOptionAKill++;
				bossOptionBreakA++;
			}

			bossOptionA.position = position;
			bossOptionA.scale = 1.5f;
			bossOptionA.Draw();
		}
		else
		{
			bossOptionBreakA++;
			bossOptionABreak.position = position;
			bossOptionABreak.scale = 1.5f;

			if (bossOptionBreakA > 0 && bossOptionBreakA <= 20)
			{
				if (bossOptionBreakA > 0 && bossOptionBreakA <= 4)
				{
					bossOptionABreak.color.w = 1.0f;
				}
				else if (bossOptionBreakA > 4 && bossOptionBreakA <= 8)
				{
					bossOptionABreak.color.w = 0.75f;
				}
				else if (bossOptionBreakA > 8 && bossOptionBreakA <= 12)
				{
					bossOptionABreak.color.w = 0.5f;
				}
				else if (bossOptionBreakA > 12 && bossOptionBreakA <= 16)
				{
					bossOptionABreak.color.w = 0.25f;
				}
				else
				{
					bossOptionABreak.color.w = 0.0f;
				}
				bossOptionABreak.Draw();
			}
			else
			{
				position = Float3(-150.0f, Window::GetSize().y * 2.0f, 0.0f);
				BossOptionALife = 50 + BossOptionAKill * 10;
				bossOptionBreakA = 0;
			}
		}
	}
	bool CheckHit(Float3 position)
	{
		for (int i = 0; i < enemyBullets.size(); i++)
		{
			if (std::hypotf(enemyBullets[i].position.x - position.x, enemyBullets[i].position.y - position.y) < 6.0f)
			{
				enemyBullets[i].position.y = -3000.0f;
				return true;
			}
		}

		return false;
	}
};

class BossOptionB
{
public:
	Float3 position;
	float angle;
	std::vector<EnemyBullet> enemyBullets;
	int OptionBBulletInterval = 0;
	int bossOptionBCount = 0;

	// 初期化（コンストラクタ）
	BossOptionB()
	{
		position = Float3(150.0f, Window::GetSize().y / 2.0f + 140.0f, 0.0f);
	}
	void Update()
	{
		for (int i = 0; i < enemyBullets.size(); i++)
		{
			enemyBullets[i].Update();

			if (enemyBullets[i].position.x < -Window::GetSize().x / 2.0f ||
				enemyBullets[i].position.x > Window::GetSize().x / 2.0f ||
				enemyBullets[i].position.y < -Window::GetSize().y / 2.0f ||
				enemyBullets[i].position.y > Window::GetSize().y / 2.0f)
			{
				enemyBullets.erase(enemyBullets.begin() + i);
				i--;
			}
		}

		if (bossOptionBreakB == 0)
		{
			if (position.y <= Window::GetSize().y / 4.0f)
			{
				bossOptionBCount++;
				velocity5_2 += 0.05f;
			}
			else
			{
				bossOptionBCount = 0;
				velocity5_2 = 0.0f;
			}

			if (velocity5_2 >= 1.0f)
			{
				velocity5_2 = 1.0f;
			}
			position.y -= -velocity5_2 + 1.0f;

			angle += 6.5f;
			EnemyBullet enemyBullet;
			OptionBBulletInterval++;

			if (bossOptionBCount > 30)
			{
				if (OptionBBulletInterval == 2)
				{
					enemyBullet.position = position;
					enemyBullet.angle = angle;
					enemyBullets.push_back(enemyBullet);
				}
			}

			if (OptionBBulletInterval >= 4)
			{
				OptionBBulletInterval = 0;
			}

			if (BossOptionBLife == 0)
			{
				playerLife += 30;
				BossOptionBKill++;
				bossOptionBreakB++;
			}

			bossOptionB.position = position;
			bossOptionB.scale = 1.5f;
			bossOptionB.Draw();
		}
		else
		{
			bossOptionBreakB++;
			bossOptionBBreak.position = position;
			bossOptionBBreak.scale = 1.5f;

			if (bossOptionBreakB > 0 && bossOptionBreakB <= 20)
			{
				if (bossOptionBreakB > 0 && bossOptionBreakB <= 4)
				{
					bossOptionBBreak.color.w = 1.0f;
				}
				else if (bossOptionBreakB > 4 && bossOptionBreakB <= 8)
				{
					bossOptionBBreak.color.w = 0.75f;
				}
				else if (bossOptionBreakB > 8 && bossOptionBreakB <= 12)
				{
					bossOptionBBreak.color.w = 0.5f;
				}
				else if (bossOptionBreakB > 12 && bossOptionBreakB <= 16)
				{
					bossOptionBBreak.color.w = 0.25f;
				}
				else
				{
					bossOptionBBreak.color.w = 0.0f;
				}
				bossOptionBBreak.Draw();
			}
			else
			{
				position = Float3(150.0f, Window::GetSize().y * 2.0f, 0.0f);
				BossOptionBLife = 50 + BossOptionBKill * 10;
				bossOptionBreakB = 0;
			}
		}
	}
	bool CheckHit(Float3 position)
	{
		for (int i = 0; i < enemyBullets.size(); i++)
		{
			if (std::hypotf(enemyBullets[i].position.x - position.x, enemyBullets[i].position.y - position.y) < 6.0f)
			{
				enemyBullets[i].position.y = -3000.0f;
				return true;
			}
		}

		return false;
	}
};

class Item1
{
public:
	Float3 position;
	std::vector<Item1> items;

	Item1()
	{
		position = Float3(0.0f, 0.0f, 0.0f);
	}

	void Update()
	{
		position.y -= 1.0f;

		ItemSprite1.position = position;
		ItemSprite1.Draw();
	}

	bool CheckHit(Float3 position)
	{
		for (int i = 0; i < items.size(); i++)
		{
			if (std::hypotf(items[i].position.x - position.x, items[i].position.y - position.y) < 12.0f)
			{
				DropFlag1 = true;
				return true;
			}
		}
		return false;
	}
};

class Item2
{
public:
	Float3 position;
	std::vector<Item2> item2s;

	Item2()
	{
		position = Float3(0.0f, -Window::GetSize().y, 0.0f);
	}

	void Update()
	{
		position.y -= 1.0f;

		ItemSprite2.position = position;
		ItemSprite2.Draw();
	}

	bool CheckHit(Float3 position)
	{
		for (int i = 0; i < item2s.size(); i++)
		{
			if (std::hypotf(item2s[i].position.x - position.x, item2s[i].position.y - position.y) < 18.0f)
			{
				item2s[i].position.y = -3000.0f;
				return true;
			}
		}
		return false;
	}
};

class Item3_1
{
public:
	Float3 position;
	std::vector<Item3_1> item3_1s;

	Item3_1()
	{
		position = Float3(0.0f, -Window::GetSize().y, 0.0f);
	}

	void Update()
	{
		position.x -= 1.0f;

		ItemSprite3_1.position = position;
		ItemSprite3_1.Draw();
	}

	bool CheckHit(Float3 position)
	{
		for (int i = 0; i < item3_1s.size(); i++)
		{
			if (std::hypotf(item3_1s[i].position.x - position.x, item3_1s[i].position.y - position.y) < 18.0f)
			{
				item3_1s[i].position.y = -3000.0f;
				return true;
			}
		}
		return false;
	}
};

class Item3_2
{
public:
	Float3 position;
	std::vector<Item3_2> item3_2s;

	Item3_2()
	{
		position = Float3(0.0f, -Window::GetSize().y, 0.0f);
	}

	void Update()
	{
		position.x -= 1.0f;

		ItemSprite3_2.position = position;
		ItemSprite3_2.Draw();
	}

	bool CheckHit(Float3 position)
	{
		for (int i = 0; i < item3_2s.size(); i++)
		{
			if (std::hypotf(item3_2s[i].position.x - position.x, item3_2s[i].position.y - position.y) < 18.0f)
			{
				item3_2s[i].position.y = -3000.0f;
				return true;
			}
		}
		return false;
	}
};

class Battery
{
public:
	Float3 position;

	Battery()
	{
		position = Float3(140.0f, -Window::GetSize().y / 2.0f + 36.0f, 0.0f);
	}

	void Update()
	{
		if (playerLife <= 0)
		{
			batterySprite000.position = position;
			batterySprite000.Draw();
		}
		else if (playerLife > 95)
		{
			batterySprite100.position = position;
			batterySprite100.Draw();
		}
		else if (playerLife > 90)
		{
			batterySprite095.position = position;
			batterySprite095.Draw();
		}
		else if (playerLife > 85)
		{
			batterySprite090.position = position;
			batterySprite090.Draw();
		}
		else if (playerLife > 80)
		{
			batterySprite085.position = position;
			batterySprite085.Draw();
		}
		else if (playerLife > 75)
		{
			batterySprite080.position = position;
			batterySprite080.Draw();
		}
		else if (playerLife > 70)
		{
			batterySprite075.position = position;
			batterySprite075.Draw();
		}
		else if (playerLife > 65)
		{
			batterySprite070.position = position;
			batterySprite070.Draw();
		}
		else if (playerLife > 60)
		{
			batterySprite065.position = position;
			batterySprite065.Draw();
		}
		else if (playerLife > 55)
		{
			batterySprite060.position = position;
			batterySprite060.Draw();
		}
		else if (playerLife > 50)
		{
			batterySprite055.position = position;
			batterySprite055.Draw();
		}
		else if (playerLife > 45)
		{
			batterySprite050.position = position;
			batterySprite050.Draw();
		}
		else if (playerLife > 40)
		{
			batterySprite045.position = position;
			batterySprite045.Draw();
		}
		else if (playerLife > 35)
		{
			batterySprite040.position = position;
			batterySprite040.Draw();
		}
		else if (playerLife > 30)
		{
			batterySprite035.position = position;
			batterySprite035.Draw();
		}
		else if (playerLife > 25)
		{
			batterySprite030.position = position;
			batterySprite030.Draw();
		}
		else if (playerLife > 20)
		{
			batterySprite025.position = position;
			batterySprite025.Draw();
		}
		else if (playerLife > 15)
		{
			batterySprite020.position = position;
			batterySprite020.Draw();
		}
		else if (playerLife > 10)
		{
			batterySprite015.position = position;
			batterySprite015.Draw();
		}
		else if (playerLife > 5)
		{
			batterySprite010.position = position;
			batterySprite010.Draw();
		}
		else if (playerLife > 0)
		{
			batterySprite005.position = position;
			batterySprite005.Draw();
		}
	}
};

class BossLife
{
public:
	Float3 position;

	BossLife()
	{
		position = Float3(30.0f, Window::GetSize().y / 2.0f - 20.0f, 0.0f);
	}

	void Update()
	{
		if (bossLife <= 0)
		{
			bossLife000.position = position;
			bossLife000.scale = 2.0f;
			bossLife000.Draw();
		}
		else if (bossLife > 950)
		{
			bossLife100.position = position;
			bossLife100.scale = 2.0f;
			bossLife100.Draw();
		}
		else if (bossLife > 900)
		{
			bossLife095.position = position;
			bossLife095.scale = 2.0f;
			bossLife095.Draw();
		}
		else if (bossLife > 850)
		{
			bossLife090.position = position;
			bossLife090.scale = 2.0f;
			bossLife090.Draw();
		}
		else if (bossLife > 800)
		{
			bossLife085.position = position;
			bossLife085.scale = 2.0f;
			bossLife085.Draw();
		}
		else if (bossLife > 750)
		{
			bossLife080.position = position;
			bossLife080.scale = 2.0f;
			bossLife080.Draw();
		}
		else if (bossLife > 700)
		{
			bossLife075.position = position;
			bossLife075.scale = 2.0f;
			bossLife075.Draw();
		}
		else if (bossLife > 650)
		{
			bossLife070.position = position;
			bossLife070.scale = 2.0f;
			bossLife070.Draw();
		}
		else if (bossLife > 600)
		{
			bossLife065.position = position;
			bossLife065.scale = 2.0f;
			bossLife065.Draw();
		}
		else if (bossLife > 550)
		{
			bossLife060.position = position;
			bossLife060.scale = 2.0f;
			bossLife060.Draw();
		}
		else if (bossLife > 500)
		{
			bossLife055.position = position;
			bossLife055.scale = 2.0f;
			bossLife055.Draw();
		}
		else if (bossLife > 450)
		{
			bossLife050.position = position;
			bossLife050.scale = 2.0f;
			bossLife050.Draw();
		}
		else if (bossLife > 400)
		{
			bossLife045.position = position;
			bossLife045.scale = 2.0f;
			bossLife045.Draw();
		}
		else if (bossLife > 350)
		{
			bossLife040.position = position;
			bossLife040.scale = 2.0f;
			bossLife040.Draw();
		}
		else if (bossLife > 300)
		{
			bossLife035.position = position;
			bossLife035.scale = 2.0f;
			bossLife035.Draw();
		}
		else if (bossLife > 250)
		{
			bossLife030.position = position;
			bossLife030.scale = 2.0f;
			bossLife030.Draw();
		}
		else if (bossLife > 200)
		{
			bossLife025.position = position;
			bossLife025.scale = 2.0f;
			bossLife025.Draw();
		}
		else if (bossLife > 150)
		{
			bossLife020.position = position;
			bossLife020.scale = 2.0f;
			bossLife020.Draw();
		}
		else if (bossLife > 100)
		{
			bossLife015.position = position;
			bossLife015.scale = 2.0f;
			bossLife015.Draw();
		}
		else if (bossLife > 50)
		{
			bossLife010.position = position;
			bossLife010.scale = 2.0f;
			bossLife010.Draw();
		}
		else if (bossLife > 0)
		{
			bossLife005.position = position;
			bossLife005.scale = 2.0f;
			bossLife005.Draw();
		}
	}
};

int MAIN()
{
	Window::SetSize(400, 600);

	Mode mode = Title;

	camera.color = Float4(0.0f, 0.0f, 0.3f, 1.0f);

	Player player;
	
	Enemy enemy;
	Enemy2 enemy2;
	Enemy3 enemy3;
	Enemy4 enemy4;

	Boss boss;
	BossOptionA bossOptionA;
	BossOptionB bossOptionB;

	Battery battery;
	BossLife bossLIFE;

	Text titleText(L"Shooting");
	titleText.scale = 2.0f;
	titleText.position = Float3(0.0f, 16.0f, 0.0f);
	titleText.color = Float4(1.0f, 1.0f, 0.0f, 1.0f);

	Text titleText2(L"ENTER Key GAME START");
	titleText2.color = Float4(1.0f, 1.0f, 0.0f, 1.0f);
	titleText2.position = Float3(0.0f, -Window::GetSize().y / 3.0f, 0.0f);

	Text titleText3(L"(チーム制作)");
	titleText3.scale = 2.0f;
	titleText3.position = Float3(0.0f, -16.0f, 0.0f);
	titleText3.color = Float4(1.0f, 1.0f, 0.0f, 1.0f);

	Text bossText(L"BOSS");
	bossText.scale = 2.0f;
	bossText.color = Float4(1.0f, 1.0f, 1.0f, 1.0f);
	bossText.position = Float3(-120.0f, Window::GetSize().y / 2.0f - 20.0f, 0.0f);

	Text batteryText(L"Battery");
	batteryText.color = Float4(1.0f, 1.0f, 1.0f, 1.0f);
	batteryText.position = Float3(140.0f, -Window::GetSize().y / 2.0f + 56.0f, 0.0f);

	Text danger(L"DANGER");
	danger.color = Float4(1.0f, 0.0f, 0.0f, 1.0f);
	danger.position = Float3(140.0f, -Window::GetSize().y / 2.0f + 16.0f, 0.0f);

	Text clearText(L"GAME CLEAR!");
	clearText.scale = 3.0f;
	clearText.color = Float4(1.0f, 1.0f, 0.0f, 1.0f);

	Text overText(L"GAME OVER");
	overText.scale = 3.0f;
	overText.color = Float4(1.0f, 1.0f, 0.0f, 1.0f);

	Text backText(L"SPACE Key TITLE");
	backText.color = Float4(1.0f, 1.0f, 0.0f, 1.0f);
	backText.position = Float3(0.0f, -Window::GetSize().y / 3.0f, 0.0f);

	while (Refresh())
	{
		switch (mode)
		{
		case Title:

			camera.Update();

			if (Input::GetKeyDown(VK_RETURN))
			{
				player = Player();
				enemy = Enemy();
				enemy2 = Enemy2();
				enemy3 = Enemy3();
				enemy4 = Enemy4();
				boss = Boss();
				bossOptionA = BossOptionA();
				bossOptionB = BossOptionB();
				battery = Battery();
				bossLIFE = BossLife();

				playerLife = 100;
				enemyLife = 30;
				enemy2Life = 10;
				enemy3Life = 15;
				enemy4Life = 5;
				bossLife = 1000;
				BossOptionALife = 50;
				BossOptionBLife = 50;
				enemyKill = 0;
				enemy2Kill = 0;
				enemy3Kill = 0;
				enemy4Kill = 0;
				BossOptionAKill = 0;
				BossOptionBKill = 0;

				playerBreak = 0;
				bossBreak = 0;

				mode = Game;
			}

			titleText.Draw();
			titleText2.Draw();
			titleText3.Draw();

			break;

		case Game:

			camera.Update();

			player.Update();

			totalKill = enemyKill + enemy2Kill + enemy3Kill + enemy4Kill;

			if (totalKill >= 20)
			{
				enemy.Update();
			}

			enemy2.Update();
			enemy3.Update();
			enemy4.Update();

			if (totalKill >= 40)
			{
				boss.Update();
				bossOptionA.Update();
				bossOptionB.Update();
				bossLIFE.Update();
				bossText.Draw();
			}
			
			counter++;

			if (playerLife <= 0)
			{
				mode = Over;
			}

			if (bossLife <= 0)
			{
				mode = Clear;
			}

			if (enemyBreak == 0)
			{
				if (player.CheckHit(enemy.position))
				{
					enemyLife--;
				}
			}
			if (enemy2Break == 0)
			{
				if (player.CheckHit(enemy2.position))
				{
					enemy2Life--;
				}
			}
			if (enemy3Break == 0)
			{
				if (player.CheckHit(enemy3.position))
				{
					enemy3Life--;
				}
			}
			if (enemy4Break == 0)
			{
				if (player.CheckHit(enemy4.position))
				{
					enemy4Life--;
				}
			}
			if (player.CheckHit(boss.position))
			{
				bossLife--;
			}
			if (bossOptionBreakA == 0)
			{
				if (player.CheckHit(bossOptionA.position))
				{
					BossOptionALife--;
				}
			}
			if (bossOptionBreakB == 0)
			{
				if (player.CheckHit(bossOptionB.position))
				{
					BossOptionBLife--;
				}
			}

			battery.Update();

			if (counter == 60)
			{
				playerLife--;
				counter = 0;
			}

			if (playerLife >= 100)
			{
				playerLife = 100;
			}

			if (playerLife <= 20)
			{
				if (playerLife <= 10)
				{
					if (counter < 15 || counter >= 30 && counter < 45)
					{
						danger.Draw();
					}
				}
				else
				{
					if (counter < 30)
					{
						danger.Draw();
					}
				}
			}

			if (enemy.CheckHit(player.position) || enemy2.CheckHit(player.position) ||
				enemy3.CheckHit(player.position) || enemy4.CheckHit(player.position) ||
				bossOptionA.CheckHit(player.position) || bossOptionB.CheckHit(player.position))
			{
				playerLife -= 5;
			}
			if (boss.CheckHit(player.position))
			{
				playerLife -= 10;
			}

			batteryText.Draw();

			break;

		case Clear:

			camera.Update();

			bossBreak++;

			player.Update();

			totalKill = enemyKill + enemy2Kill + enemy3Kill + enemy4Kill;

			if (totalKill >= 40)
			{
				boss.Update();
				bossLIFE.Update();
				bossText.Draw();
			}

			battery.Update();

			if (bossBreak >= 90)
			{
				clearText.Draw();
			}
			if (bossBreak >= 270)
			{
				if (Input::GetKey(VK_SPACE))
				{
					mode = Title;
				}

				backText.Draw();
			}

			batteryText.Draw();

			break;

		case Over:

			camera.Update();

			playerBreak++;

			player.Update();

			totalKill = enemyKill + enemy2Kill + enemy3Kill + enemy4Kill;

			if (totalKill >= 20)
			{
				enemy.Update();
			}

			enemy2.Update();
			enemy3.Update();
			enemy4.Update();

			if (totalKill >= 40)
			{
				boss.Update();
				bossOptionA.Update();
				bossOptionB.Update();
				bossLIFE.Update();
				bossText.Draw();
			}

			battery.Update();

			if (playerBreak >= 90)
			{
				overText.Draw();
			}
			if (playerBreak >= 270)
			{
				if (Input::GetKey(VK_SPACE))
				{
					mode = Title;
				}

				backText.Draw();
			}

			batteryText.Draw();

			break;
		}
	}
	return 0;
}
