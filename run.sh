#!/bin/bash
clear
SFML_PATH=SFML-2.5.1/
export LD_LIBRARY_PATH=$SFML_PATH/lib/
g++ main.cpp Entity.cpp Player.cpp State.cpp Game.cpp GameState.cpp MainMenuState.cpp CredentialsState.cpp Button.cpp Weapon.cpp Pistol.cpp Bullet.cpp -I $SFML_PATH/include/ -o \
Guls_Latem.exe -L $SFML_PATH/lib/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio && \
./Guls_Latem.exe && rm -f *.out *.gch *.o 
