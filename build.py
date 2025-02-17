import os
import platform

# common configuration options (change as needed) 
COMPILER="g++ -g -std=c++17"   
SOURCE="./src/*.cpp"    
EXECUTABLE="prog"       

# platform specific configurations - change as needed
ARGUMENTS=""            # arguments needed
INCLUDE_DIR=""          # directories to include.
LIBRARIES=""            # libraries to include

if platform.system()=="Linux":
    ARGUMENTS="-D LINUX" # -D is a #define sent to preprocessor
    INCLUDE_DIR="-I ./include/ -I ./../common/thirdparty/glm/"
    LIBRARIES="-lSDL2 -ldl"
elif platform.system()=="Darwin":
    ARGUMENTS="-D MAC" # -D is a #define sent to the preprocessor
    INCLUDE_DIR="-I ./include/ -I/opt/homebrew/Cellar/sdl2/2.30.10/include/SDL2 -I./../common/thirdparty/old/glm"
    LIBRARIES="-L/opt/homebrew/Cellar/sdl2/2.30.10/lib -lSDL2 -ldl"
elif platform.system()=="Windows":
    ARGUMENTS="-D MINGW -static-libgcc -static-libstdc++" 
    INCLUDE_DIR="-I./include/ -I./../common/thirdparty/old/glm/"
    EXECUTABLE="prog.exe"
    LIBRARIES="-lmingw32 -lSDL2main -lSDL2 -mwindows"

# executable compiled into a single string 
compileString=COMPILER+" "+ARGUMENTS+" "+SOURCE+" -o "+EXECUTABLE+" "+" "+INCLUDE_DIR+" "+LIBRARIES
exit_code = os.system(compileString)
exit(0 if exit_code==0 else 1)

