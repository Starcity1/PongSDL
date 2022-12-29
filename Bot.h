#ifndef BOT_H
#define BOT_H

class Bot {
public:

Bot() {}

bool withBot;

int x, y;

void InitBot(int initX, int initY, bool useBot);
void MoveBot(int ballY);
void PlayerLoses();

};
#endif