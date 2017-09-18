:beg
g++ Main.cpp Globals.cpp Material.cpp Objects.cpp Lights.cpp RayTracer.cpp EasyBMP/EasyBMP.cpp  -g -o Main.exe -lfreeglut -lopengl32 -lglu32
pause
cls
goto beg