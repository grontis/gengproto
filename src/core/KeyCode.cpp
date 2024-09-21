#include <iostream>
#include <map>

#include <SDL2/SDL.h>


class KeyCodes
{
public:
    //TODO functino to get SDL code by keyCode value
private:
    static std::map<KeyCode, SDL_Scancode> keyMap;
};

typedef enum
{
    //TODO define corresponding codes that can be mapped with SDL scan codes
} KeyCode;