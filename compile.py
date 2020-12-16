import os

flags = ["-lSDL2", "-lSDL2_image", "-lSDL2_ttf"]
files = ["Sprite.cpp", "SDL_Setup.cpp", "main.cpp", "Main.cpp", "Bullet.cpp", "Pattern.cpp", "Player.cpp", "Text.cpp", "GameStats.cpp"]

command = "g++ "
for file in files:
	command += "src/" + file + " "

for flag in flags:
	command += flag + " "

if(os.path.isfile('BulletHell')):
	os.system("rm BulletHell")

os.system(command[:-1])
os.system("mv a.out BulletHell")