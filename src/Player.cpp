#include "Player.h"

Player::Player(int s) : Entity(s)
{
	loadTextures("resources/player.png");
	velocity = std::make_pair(0, 0);
	body.setOrigin(15, 15);
	body.setPosition(sf::Vector2f(0, 0));
	tail = new Tail(this);
}

void Player::drop(Map* map, int XY)
{
	if (map->getTileState(XY) == 0) map->changeTileState(XY, -1);
	if (map->getTileState(XY - Map::MAP_WIDTH) == 0) drop(map, XY - Map::MAP_WIDTH);
	if (map->getTileState(XY + Map::MAP_WIDTH) == 0) drop(map, XY + Map::MAP_WIDTH);
	if (map->getTileState(XY - 1) == 0) drop(map, XY - 1);
	if (map->getTileState(XY + 1) == 0) drop(map, XY + 1);
}


void Player::revivePlayer()
{
	velocity = std::make_pair(0, 0);
	body.setPosition(sf::Vector2f(0, 0));
	body.setRotation(0);
	tail = new Tail(this);
}

void Player::move(Map* map)
{
	sf::Vector2f oldPos = body.getPosition();

	if (nM.inQueue && ((int)oldPos.x - ENTITY_RADIUS) % Map::TILE_SIZE == 0
		&& ((int)oldPos.y - ENTITY_RADIUS) % Map::TILE_SIZE == 0)
	{
		nM.inQueue = false;
		changeVelocity(nM.nextVelocity.first, nM.nextVelocity.second);
		rotate(nM.nextRotation);
	}

	if (((int)oldPos.x - ENTITY_RADIUS) % Map::TILE_SIZE == 0 && ((int)oldPos.y - ENTITY_RADIUS) % Map::TILE_SIZE == 0)
	{
		std::pair<int, int> tileInfo = checkTileBellow(map);

		if (tileInfo.second == Map::EMPTY_TILE)
			map->changeTileState(tileInfo.first, Map::TAIL_TILE);
		conquestPossible = tail->checkPlayerState(tileInfo.second);
	}


	body.setPosition(sf::Vector2f(oldPos.x + (speed * velocity.first), oldPos.y + (speed * velocity.second)));

	checkCollisons(body.getPosition());
}

void Player::planNextTurn(int x, int y, float degree)
{
	nM.inQueue = true;
	nM.nextRotation = degree;
	nM.nextVelocity = std::make_pair(x, y);
}

int Player::checkCollisons(sf::Vector2f pos)
{
	if (pos.x < 15) body.setPosition(15, pos.y);
	else if (pos.x > 1620 - 15) body.setPosition(1620 - 15, pos.y);
	else if (pos.y < 15) body.setPosition(pos.x, 15);
	else if (pos.y > 900 - 15) body.setPosition(pos.x, 900 - 15);

	return 0;


}

std::pair<int, int> Player::checkTileBellow(Map* map)
{
	int X = ((int)body.getPosition().x - 3) / Map::TILE_SIZE; //int used deliberately
	int Y = ((int)body.getPosition().y - 3) / Map::TILE_SIZE; //int used deliberately

	int indexXY = (int)(X + (Y * Map::MAP_WIDTH));
	int tileType = map->getTileState(indexXY);

	return std::make_pair(indexXY, tileType);
}

void Player::changeVelocity(float x, float y)
{
	velocity.first = x;
	velocity.second = y;
}

void Player::rotate(float angle)
{
	body.setRotation(0);
	body.setRotation(angle);
}

bool Player::getConquestState() { return conquestPossible; }

void Player::conquer(Map* map, std::vector<int> positions)
{
	for (auto a : positions)
		drop(map, a);

	map->fillEmptySpace();

	conquestPossible = false;
}

std::pair<int, int> Player::getPositionPx()
{
	int x = body.getPosition().x;
	int y = body.getPosition().y;
	return std::make_pair(x, y);
}



Player::~Player() { delete tail; }
