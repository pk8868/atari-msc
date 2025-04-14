# atari-msc
ATARI Logo Interpreter
Interpreter na motorola science cup
![grafika](https://user-images.githubusercontent.com/87194023/157021840-30df2b21-6e2e-4cc4-818c-283700c2858f.png)


## Budowanie
Do projektu są dołączone pliki CMake. Można wygenerować projekt np. do Visual Studio za pomocą polecenia:
```bat
cmake -G "Visual Studio 16"
```
i skompliować projekt w wybranym IDE


lub zbudować cały projekt korzystając z Make i CMake:

```sh
mkdir build
cd build
cmake -B . -S ..
make
cd ..
```
(projekt się buduje ale nie działa na systemie Linux)