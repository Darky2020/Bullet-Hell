import os

flags = ["-lGL", "-lSDL2", "-lSDL2_image", "-lSDL2_mixer", "-lSDL2_ttf", "-lmpg123", "-std=gnu++1z"]

command = "g++ `sdl2-config --cflags` src/*.cpp src/imgui/*.cpp `sdl2-config --libs` "

for flag in flags:
	command += flag + " "

if(os.path.isfile('BulletHell')):
	os.system("rm BulletHell")

os.system(command[:-1])
os.system("mv a.out BulletHell")