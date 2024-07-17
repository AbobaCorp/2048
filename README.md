<img src=/img/icon.png width=64>
<h1>Game 2048 </h1>
Game 2048 written in C++ using the SFML library.

Control of the game:

| Button | Assignment |
| ------ | ---------- |
|  W / 🠕 | moves the tiles up |
|  S / 🠗 | moves the tiles down |
|  A / 🠔 | moves the tiles left |
|  D / 🠖 | moves the tiles right |
|    H    | hides/shows the frame per second counter |

The game can save the best score and the playing field to a file. Therefore, if you want to reset your best score, do the following:
* In Windows \
Go to the folder with the game (by default it is stored in C:\Users\\<username\>\AppData\Local\Programs\Game2048 ) and delete the "player.data" file
* In Linux \
Go to the directory with the main executable file of the game and delete the "player.data" file.
(If you did the installation of the game, as in the instructions below, then open the terminal and run the following command)
```sh
cd 2048 && rm player.data
```


# Installing the game
## Windows
The installer for Windows can be downloaded [here](./setup/setup_2048.exe)

## Linux

* ### Build for Ubontu/Debian
```sh
sudo apt update
sudo apt install git build-essential libsfml-dev
```
```sh
git clone https://github.com/AbobaCorp/2048.git
cd 2048
g++ -c *.cpp
g++ *.o -o game2048 -lsfml-graphics -lsfml-window -lsfml-system
mkdir -p obj && mv *.o obj
./game2048
```

* ### Build for other distributions
Install git and g++ packages using the package manager of your distribution.

Download the SFML SDK from the [download page](https://www.sfml-dev.org/files/SFML-2.6.1-linux-gcc-64-bit.tar.gz), unpack it and copy the files to your preferred location: either a separate path in your personal folder (like /home/me/sfml), or a standard path (like /usr/local).

Here, \<sfml-install-path\> is the directory where you copied SFML
```sh
git clone https://github.com/AbobaCorp/2048.git
cd 2048
g++ -c *.cpp -I<sfml-install-path>/include
g++ *.o -o game2048 -L<sfml-install-path>/lib -lsfml-graphics -lsfml-window -lsfml-system
mkdir -p obj && mv *.o obj
export LD_LIBRARY_PATH=<sfml-install-path>/lib
```
That's done, you can start
```sh
./game2048
```

# Preview
> ![](/img/1.png)
> 
> screenshot of the game

> ![](/img/2.png)
> 
> screenshot of the game, with FPS monitoring

