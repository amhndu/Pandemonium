#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics/Color.hpp>

#define WINDOW_WIDTH        1366
#define WINDOW_HEIGHT       768
#define FG_TEXT_COLOR       sf::Color::Black
#define BUTTON_TEXT_COLOR   sf::Color::White
#define BUTTON_BG_COLOR     sf::Color(0x96002Dff)
#define BUTTON_HOVER_COLOR  sf::Color(0x2A000Eff)
#define Z_SPEED             10
#define PLAYER_VELOCITY     60
#define ENEMY_VELOCITY      40
#define LAND_APP_HEIGHT     300      /* Apparent height */
#define LAND_SLOPE          200.f / 300.f

#endif //CONSTANTS_H