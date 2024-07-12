<img src=/img/icon.png width=64>
<h1>Game 2048 </h1>
Game 2048 written in C++ using the SFML library

# Installing the game
## Windows
The installer for Windows can be downloaded [here](/setup/)

## Linux
> Under development
* Build for Ubontu/Debian
```
sudo apt update
```
```
sudo apt install git build-essential libsfml-dev
```
```
git clone https://github.com/AbobaCorp/2048.git
cd 2048
g++ -c *.cpp
g++ *.o -o game2048 -lsfml-graphics -lsfml-window -lsfml-system
mkdir -p obj && mv *.o obj
./game2048
```

# Preview
> ![](/img/1.png)
> 
> screenshot of the game

> ![](/img/2.png)
> 
> screenshot of the game, with FPS monitoring

