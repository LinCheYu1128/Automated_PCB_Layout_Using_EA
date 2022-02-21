# Btree_Implementation

## Object-Oriented Programming
* 開放擴充 封閉修改
* 寫getter / setter/ printer
* 忽略implementation details，先把流程用cout簡化
* 思考如何驗證functional works
  * 寫test function
  * 找人review code

## Todo
- [ ] Binary tree class
  * constructor
  * plot tree
- [x] File input class
  * component
  * pin position
    * T501
    * M503
- [ ] GA class
  * Crossover
  * Mutation
- [ ] Evaluation class
  * Contour
    * Horizon contour
    * Preplace contour
  * Area
  * PnS
  * WireLength

## How To Manage Using Git
- git clone https://github.com/danlu008/AcBel_Project.git
- git init
- git config --global user.name {$User Name}
- git config --global user.email {$User Email}
- git remote add origin ${Your Git}
- git remote add upstream https://github.com/danlu008/AcBel_Project.git
- git reset --hard HEAD

## Before editing files
- git pull upstream main

## After editing files
- cd ./AcBel_project-main
- git add .
- git commit -m "{$message}"
- git push origin main
- On Github: pull requests

## Git Message
- create / modify / move / rename / remove
- function / class / .cpp / .h

## How To Compile
- cd .\build\
- cmake --build .
- .\Debug\AcBel_Project.exe
