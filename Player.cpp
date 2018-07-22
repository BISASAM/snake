#pragma once
#include "Player.h"
#include "Game.h"
#include "eV.h"

sf::Texture Player::arrowtxt;


Player::Player()
{}

Player::Player(sf::Color col, sf::Vector2<int> pos, sf::Keyboard::Key K1, sf::Keyboard::Key K2)
{
	circle.setRadius(4);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setPosition(pos.x,pos.y);
	circle.setFillColor(col);

	Pos.x=pos.x;
	Pos.y = pos.y;
	
	arrowtxt.loadFromFile("arrow.png");
	arrow.setTexture(arrowtxt);
	arrow.setOrigin(0, 10);
	arrow.setPosition(circle.getPosition());
	arrow.setColor(col);

	vertices.setPrimitiveType(sf::TriangleStrip);
	vertices.append(sf::Vertex(circle.getPosition(), col));

	pixels.resize(1 * 1 * 3);
	pixelsSide1.resize(1 * 1 * 3);
	pixelsSide2.resize(1 * 1 * 3);
	
	Col = col;
	
	Key1 = K1;
	Key2 = K2;

	speed = 0.115;
	turnspeed = 0.004;
	alpha = 0;
	R = { 1.0f,0.0f };
	holetimer = 0;
	traceN = 0;
	randomN = 1000000;
	allPPowerUp.first = -1; 
	allPPowerUp.second = 1;
	drawBorder = true;

}

void Player::create(sf::Color col, sf::Vector2<int> pos, sf::Keyboard::Key K1, sf::Keyboard::Key K2)
{
	circle.setRadius(4);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setPosition(pos.x, pos.y);
	circle.setFillColor(col);

	Pos.x = pos.x;
	Pos.y = pos.y;

	arrowtxt.loadFromFile("arrow.png");
	arrow.setTexture(arrowtxt);
	arrow.setOrigin(0, 10);
	arrow.setPosition(circle.getPosition());
	arrow.setColor(col);

	vertices.setPrimitiveType(sf::TriangleStrip);
	vertices.append(sf::Vertex(circle.getPosition(), col));

	Col = col;

	Key1 = K1;
	Key2 = K2;

	speed = 0.115;
	turnspeed = 0.004;
	alpha = 0;
	R = { 1.0f,0.0f };
	holetimer = 0;
	traceN = 0;
	randomN = 1000000;
	allPPowerUp.first = -1;
	allPPowerUp.second = 1;
	drawBorder = true;
}

void Player::changeKeys()
{
	KeyTemp = Key1;
	Key1 = Key2;
	Key2 = KeyTemp;
}

float Player::norm(sf::Vector2f r)
{
	int l= sqrtf(r.x*r.x + r.y*r.y);
	return l;
}

void Player::Update(float &elapsedTime)
{
	eT = elapsedTime;
	
	if (gameoverB == false) {
		if (sf::Keyboard::isKeyPressed(Key1))
		{
			R += sf::Vector2f(-R.y, R.x)*elapsedTime/1000.0f* turnspeed;
			R /= norm(R);
		}
		if (sf::Keyboard::isKeyPressed(Key2))
		{
			R -= sf::Vector2f(-R.y, R.x)*elapsedTime / 1000.0f* turnspeed;
			R /= norm(R);
		}

		if (startphase == false) {
			
			Collision();
			Pos += R*elapsedTime / 1000.0f*speed;
			circle.setPosition(Pos);
		}
		
		if(startphase==true)
		{
			alpha = std::atan(R.y / R.x) * 180 / M_PI;
			if (R.x < 0) { alpha += 180; }
			arrow.setRotation(alpha);
		}

	}
}

void Player::PchangeSpeed(float s)
{
	speed = speed*s;
}

void Player::PchangeThickness(int d)
{
	circle.setRadius(circle.getRadius() +d);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	radius = circle.getRadius();
}

void Player::Timerdesolve() //Liste der PowerUp-Timer abarbeiten und PowerUps rueckgaengig machen
{
	if (TimersandType.size() > 0)
	{
		for (int i = 0; i < TimersandType.size(); i++)
		{
			if (TimersandType[i].first.TimerCheck() == true)
			{
				switch (TimersandType[i].second)
				{
				case 0://sich selber langsam rückgängig
					PchangeSpeed(1 / 0.7);
					TimersandType.erase(TimersandType.begin() + i);
					break;
				case 1://andere langsam rückgängig
					allPPowerUp.first = 1; 
					allPPowerUp.second = 1 / 0.7;
					PchangeSpeed(0.7);
					TimersandType.erase(TimersandType.begin() + i);
					break;
				case 2://sich selber schnell rückgängig
					PchangeSpeed(1 / 1.7);
					TimersandType.erase(TimersandType.begin() + i);
					break;
				case 3://andere schnell rückgängig
					allPPowerUp.first = 3; 
					allPPowerUp.second = 1 / 1.7;
					PchangeSpeed(1.7);
					TimersandType.erase(TimersandType.begin() + i);
					break;
				case 4://sich selber duenn rückgängig
					PchangeThickness(3);
					TimersandType.erase(TimersandType.begin() + i);
					break;
				case 5: //andere dick rückgängig
					allPPowerUp.first = 5; 
					allPPowerUp.second = -3;
					PchangeThickness(3);
					TimersandType.erase(TimersandType.begin() + i);
					break;
				case 6://andere Controls verdrehen rückgängig
					allPPowerUp.first = 6;
					allPPowerUp.second = 1;
					changeKeys();
					TimersandType.erase(TimersandType.begin() + i);
					break;
				case 7://Spuren löschen	rückgängig
					break;
				case 8://Rand öffnen/schließen rückgängig
					break;
				}
			}
		}
	}
}

sf::Vector2f Player::getHead()
{
	return sf::Vector2f(circle.getPosition());
}

void Player::Collision()
{	//Collisions-Erkennung in jedem Frame

	LP =  sf::Vector2f(1.732*R.x-0.5*R.y , 0.5*R.x+1.732*R.y); //30° nach links
	RP = sf::Vector2f(1.732*R.x + 0.5*R.y , 1.732*R.y-0.5*R.x); //30°nach rechts

	glReadBuffer(GL_FRONT); //pixel auslesen
	glReadPixels(Pos.x + (R.x* (1.0 * radius+1)), height - Pos.y - (R.y*(1.0*radius+1)), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixels[0]); //Pixel Pos vorm kopf
	glReadPixels(Pos.x + (LP.x* (1.0 * radius+1)), height - Pos.y - (LP.y*(1.0*radius+1)), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixelsSide1[0]);//Pixel seitlich 30°
	glReadPixels(Pos.x + (RP.x* (1.0 * radius+1)), height - Pos.y - (RP.y*(1.0*radius+1)), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixelsSide2[0]);//pixel andere Seite -30°
	//std::cout << std::to_string(pixels[0]) << " " << std::to_string(pixels[1]) << " " << std::to_string(pixels[2]) << std::endl;

	if (pixels[0] == 0 && pixels[1] == 0 && pixels[2] == 0 && pixelsSide1[0] == 0 && pixelsSide1[1] == 0 && pixelsSide1[2] == 0 && pixelsSide2[0] == 0 && pixelsSide2[1] == 0 && pixelsSide2[2] == 0)
	{//wenn schwarz passiert nichts
	}
	else if (powerups.size() > 0)
	{//sonst Überprüfung ob Powerup gegessen
		for (int i = 0; i < powerups.size(); i++)
		{ // wenn ja wende powerup an
			int m = powerups[i].Eaten(Pos,radius);
			if (m == 0)//sich selber langsam
			{
				PchangeSpeed(0.7);
				Timer T(7000000);
				std::pair<Timer, int> Pair(T, 0);
				TimersandType.push_back(Pair);//Timer mit Wirkungsdauer und Typ in die Liste stecken
				powerups.erase(powerups.begin() + i);
				Peaten = true;
				break;
			}
			else if (m == 1)//andere langsam
			{
				allPPowerUp.first = 1;
				allPPowerUp.second = 0.7;
				PchangeSpeed(1 / 0.7);
				Timer T(7000000);
				std::pair<Timer, int> Pair(T, 1);
				TimersandType.push_back(Pair);
				powerups.erase(powerups.begin() + i);
				Peaten = true;
				break;
			}
			else if (m == 2) //sich selber schnell
			{
				PchangeSpeed(1.7);
				Timer T(4000000);
				std::pair<Timer, int> Pair(T, 2);
				TimersandType.push_back(Pair);
				powerups.erase(powerups.begin() + i);
				Peaten = true;
				break;
			}
			else if (m == 3) //andere schnell
			{
				allPPowerUp.first = 3;
				allPPowerUp.second = 1.7;
				PchangeSpeed(1 / 1.7);
				Timer T(4000000);
				std::pair<Timer, int> Pair(T, 3);
				TimersandType.push_back(Pair);
				powerups.erase(powerups.begin() + i);
				Peaten = true;
				break;
			}
			else if (m == 4) //sich selber duenn
			{
				if (radius > 3) {
					PchangeThickness(-3);
					Timer T(7000000);
					std::pair<Timer, int> Pair(T, 4);
					TimersandType.push_back(Pair);
				}
				powerups.erase(powerups.begin() + i);
				Peaten = true;
				break;
			}
			else if (m == 5) //andere dick
			{
				allPPowerUp.first = 5;
				allPPowerUp.second = 3;
				PchangeThickness(-3);
				Timer T(7000000);
				std::pair<Timer, int> Pair(T, 5);
				TimersandType.push_back(Pair);
				powerups.erase(powerups.begin() + i);
				Peaten = true;
				break;
			}
			else if (m == 6) //andere Controls verdrehen
			{
				allPPowerUp.first = 6;
				allPPowerUp.second = 1;
				changeKeys();
				Timer T(7000000);
				std::pair<Timer, int> Pair(T, 6);
				TimersandType.push_back(Pair);
				powerups.erase(powerups.begin() + i);
				Peaten = true;
				break;
			}
			else if (m == 7) //Alle Spuren löschen
			{
				allPPowerUp.first = 7;
				allPPowerUp.second = 1;
				powerups.erase(powerups.begin() + i);
				Peaten = true;
				break;
			}
			else if (m == 8) //Rand öffnen/schließen
			{
				allPPowerUp.first = 8;
				allPPowerUp.second = 1;
				powerups.erase(powerups.begin() + i);
				Peaten = true;
				break;
			}
		}
		if (Peaten == false)
		{
			if (startphase == false) 
			{
				//std::cout << "gameover" << std::endl;
				R = { 0,0 };
				gameoverB = true;
			}
		}
		if (Peaten == true)
		{
			Peaten = false;
		}
	}
	else
	{
		if (startphase == false) 
		{
			//std::cout << "gameover" << std::endl;
			R = { 0,0 };				
			gameoverB = true;
		}
	}	
}

void Player::Draw(Game& game)
{
	radius = circle.getRadius();
	holetimer += eT;

	traceN += eT;
	if (traceN > 40000)//Spur zeichnen in 0,04s Schritten
	{
		traceN = 0;

		//Loch erzeugung nach random zeit
		if (holetimer>randomN)
		{
			hole = true;
			holeStart = Pos;
			oldCol = Col;
			Col = sf::Color::Transparent;
			holedis = (rand() % 30) + 15;
			vertices.append(sf::Vertex(Pos + N*float(radius), Col));
			vertices.append(sf::Vertex(Pos + -N*float(radius), Col));
		}

		if (hole == true) //Loch zeichnung
		{
			holetimer = 0;
			dis = sqrt((Pos.x - holeStart.x)*(Pos.x - holeStart.x) + (Pos.y - holeStart.y)*(Pos.y - holeStart.y));
			if (dis>holedis)
			{
				vertices.append(sf::Vertex(Pos + N*float(radius), Col));
				vertices.append(sf::Vertex(Pos + -N*float(radius), Col));
				Col = oldCol;
				hole = false;
				dis = 0;
				randomN = (rand() % 4) * 1000000 + 500000;
			}
		}

		N = sf::Vector2f(-R.y, R.x);
		vertices.append(sf::Vertex(Pos + N*float(radius), Col));
		vertices.append(sf::Vertex(Pos + -N*float(radius), Col));
	}

	//Randbedingungen prüfen in jedem Frame;
	if (drawBorder == false) {
		if (Pos.x + 2 * radius > width - 205)
		{

			vertices.append(sf::Vertex(sf::Vector2f(width - 200, Pos.y), sf::Color::Transparent));
			vertices.append(sf::Vertex(sf::Vector2f(width - 200, Pos.y), sf::Color::Transparent));
			vertices.append(sf::Vertex(sf::Vector2f(0, Pos.y), sf::Color::Transparent));
			vertices.append(sf::Vertex(sf::Vector2f(0, Pos.y), sf::Color::Transparent));
			Pos.x = 0 + 2 * radius;
		}
		if (Pos.x - 2 * radius < 0)
		{
			vertices.append(sf::Vertex(sf::Vector2f(0, Pos.y), sf::Color::Transparent));
			vertices.append(sf::Vertex(sf::Vector2f(0, Pos.y), sf::Color::Transparent));
			vertices.append(sf::Vertex(sf::Vector2f(width - 200, Pos.y), sf::Color::Transparent));
			vertices.append(sf::Vertex(sf::Vector2f(width - 200, Pos.y), sf::Color::Transparent));
			Pos.x = width - 205 - 2 * radius;
		}
		if (Pos.y + 2 * radius > height)
		{
			vertices.append(sf::Vertex(sf::Vector2f(Pos.x, height), sf::Color::Transparent));
			vertices.append(sf::Vertex(sf::Vector2f(Pos.x + 1, height), sf::Color::Transparent));
			vertices.append(sf::Vertex(sf::Vector2f(Pos.x, 0), sf::Color::Transparent));
			vertices.append(sf::Vertex(sf::Vector2f(Pos.x + 1, 0), sf::Color::Transparent));
			Pos.y = 2 * radius;
		}
		if (Pos.y - 2 * radius < 0)
		{
			vertices.append(sf::Vertex(sf::Vector2f(Pos.x, 0), sf::Color::Transparent));
			vertices.append(sf::Vertex(sf::Vector2f(Pos.x, 0), sf::Color::Transparent));
			vertices.append(sf::Vertex(sf::Vector2f(Pos.x, height), sf::Color::Transparent));
			vertices.append(sf::Vertex(sf::Vector2f(Pos.x, height), sf::Color::Transparent));
			Pos.y = height - 2 * radius;
		}
	}

	Timerdesolve();
	game.window.draw(vertices);
	game.window.draw(circle);
	if (startphase == true)
	{
		game.window.draw(arrow); 
	}
}