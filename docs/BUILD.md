# Linux
Clone The Github Repository (git clone https://github.com/GRATHRRAM/PacketHunter) </br>
Download Raylib (Any c++ Compiler) CMake Make build-essential </br>
Now Create A Folder Calld Build</br>
Go To That Folder And Type cmake ..</br>
If CMake Do what it have to to type make</br>
If make Compiles every thing now you can type ./ph to run PacketHunter</br>

### Step By Step Comands:
git clone https://github.com/GRATHRRAM/PacketHunter</br>
cd PacketHunter</br>
mkdir Build</br>
cd Build</br>
cmake ..</br>
make </br>
./ph</br>

# CMake Options
-D(Option)=(Value)</br>
static if =true will compile program and link libs staticly</br>
debug  if =true will compile program with debug symbols else will compile with -O2 flag</br>
all_libs if =true links all libs that the program uses else links only math and raylib (usefull only if you link staticly) 
