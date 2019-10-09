#!/bin/bash
clear
SFML_PATH=SFML-2.5.1
export LD_LIBRARY_PATH=$SFML_PATH/lib/
g++ main.cpp Game.cpp State.cpp GameState.cpp MainMenuState.cpp CredentialsState.cpp Button.cpp \
Entity.cpp Character.cpp Player.cpp  Weapon.cpp Pistol.cpp Bullet.cpp -I $SFML_PATH/include/ -o \
Guls_Latem.exe -L $SFML_PATH/lib/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio && \
./Guls_Latem.exe && rm -f *.out *.gch *.o 
