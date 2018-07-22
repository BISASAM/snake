#pragma once
#include "CoLanPlayer.h"
#include "Game.h"
#include "eV.h"

sf::Texture CoLanPlayer::arrowtxt;

CoLanPlayer::CoLanPlayer()
{}

CoLanPlayer::CoLanPlayer(sf::Color col, sf::Vector2<int> pos)
{
	circle.setRadius(4);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setPosition(pos.x, pos.y);
	circle.setFillColor(col);

	Pos.x = pos.x;
	Pos.y = pos.y;

	oldPos = Pos;

	arrowtxt.loadFromFile("arrow.png");
	arrow.setTexture(arrowtxt);
	arrow.setOrigin(0, 10);
	arrow.setPosition(circle.getPosition());
	arrow.setColor(col);

	vertices.setPrimitiveType(sf::TriangleStrip);
	vertices.append(sf::Vertex(circle.getPosition(), col));

	Col = col;
	Col2 = col;

	alpha = 0;
	R = { 1.0f,0.0f };
	holetimer = 0;
	traceN = 0;
	randomN = 1000000;
	clock.restart().asMicroseconds();
}

float CoLanPlayer::norm(sf::Vector2f r)
{
	int l= sqrtf(r.x*r.x + r.y*r.y);
	return l;
}

void CoLanPlayer::Update(sf::Vector2f(r))
{
	if (gameoverB == false) 
	{
		Pos = r;
		circle.setPosition(r);
		

		/*if(startphase==true) //StartPfeil der Co-player anzeigen
		{
			alpha = std::atan(R.y / R.x) * 180 / M_PI;
			if (R.x < 0) { alpha += 180; }
			arrow.setRotation(alpha);
		}*/

	}
}

void CoLanPlayer::PchangeThickness(int d)
{
	circle.setRadius(circle.getRadius() +d);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	radius = circle.getRadius();
}

void CoLanPlayer::Timerdesolve() //Liste der PowerUp-Timer abarbeiten und PowerUps rueckgaengig machen
{
	//if (TimersandType.size() > 0)
	//{
	//	for (int i = 0; i < TimersandType.size(); i++)
	//	{
	//		if (TimersandType[i].first.TimerCheck() == true)
	//		{
	//			switch (TimersandType[i].second)
	//			{
	//			case 0://sich selber langsam rückgängig
	//				
	//				TimersandType.erase(TimersandType.begin() + i);
	//				break;
	//			case 1://andere langsam rückgängig

	//				TimersandType.erase(TimersandType.begin() + i);
	//				break;
	//			case 2://sich selber schnell rückgängig
	//				
	//				TimersandType.erase(TimersandType.begin() + i);
	//				break;
	//			case 3://andere schnell rückgängig
	//			
	//				TimersandType.erase(TimersandType.begin() + i);
	//				break;
	//			case 4://sich selber duenn rückgängig
	//				PchangeThickness(3);
	//				TimersandType.erase(TimersandType.begin() + i);
	//				break;
	//			case 5: //andere dick rückgängig
	//	
	//				PchangeThickness(3);
	//				TimersandType.erase(TimersandType.begin() + i);
	//				break;
	//			case 6://andere Controls verdrehen rückgängig
	//			
	//				TimersandType.erase(TimersandType.begin() + i);
	//				break;
	//			case 7://Spuren löschen	rückgängig
	//				break;
	//			case 8://Rand öffnen/schließen rückgängig
	//				break;
	//			}
	//		}
	//	}
	//}
} 
//server

sf::Vector2f CoLanPlayer::getHead()
{
	return sf::Vector2f(circle.getPosition());
}

void CoLanPlayer::Draw(Game& game)
{
	traceN += clock.restart().asMicroseconds();
	
	if (traceN > 40000)//Spur zeichnen in 0,04s Schritten
	{
		traceN = 0;

		radius = circle.getRadius();
		R = Pos - oldPos;
		R /= norm(R);
		N = sf::Vector2f(-R.y, R.x);
		
		if (hole == true)
		{
			Col = sf::Color::Transparent;
			vertices.append(sf::Vertex(Pos + N*float(radius), Col));
			vertices.append(sf::Vertex(Pos + -N*float(radius), Col));
		}

		if (hole == false) //Loch zeichnung
		{
				vertices.append(sf::Vertex(Pos + N*float(radius), Col));
				vertices.append(sf::Vertex(Pos + -N*float(radius), Col));
				Col = Col2;
		}
		
		vertices.append(sf::Vertex(Pos + N*float(radius), Col));
		vertices.append(sf::Vertex(Pos + -N*float(radius), Col));
		oldPos = Pos;
	}

	//Timerdesolve();
	game.window.draw(vertices);
	game.window.draw(circle);

	/*if (startphase == true)
	{
		game.window.draw(arrow); 
	}*/
}