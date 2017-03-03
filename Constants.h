#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics/Color.hpp>

#define WINDOW_WIDTH        1366
#define WINDOW_HEIGHT       768
#define FG_TEXT_COLOR       sf::Color::Black
#define BUTTON_TEXT_COLOR   sf::Color::White
#define BUTTON_BG_COLOR     sf::Color(0x96002Dff)
#define BUTTON_HOVER_COLOR  sf::Color(0x2A000Eff)
#define Z_VELOCITY          5.f
#define PLAYER_HEIGHT       200.f
#define PLAYER_WIDTH        92.f
#define PLAYER_VELOCITY     100.f
#define ENEMY_VELOCITY      40.f
#define LAND_APP_HEIGHT     300.f      /* Apparent height */
#define LAND_SLOPE          -200.f / 300.f
#define ANIM_FRAME_TIME     0.3f
#define MAX_HEALTH          100
#endif //CONSTANTS_H