# Btree_Implementation

## Object-Oriented Programming
* 開放擴充 封閉修改
* 寫getter / setter/ printer
* 忽略implementation details，先把流程用cout簡化
* 思考如何驗證functional works
  * 寫test function
  * 找人review code

## Editing Files
### Before editing
- git pull upstream main
### After editing
- cd ./AcBel_project-main
- git add .
- git commit -m "{$message}"
- git push origin main
- On Github: pull requests

## How To Compile
### before build
- cd .\build
- cmake ..
### after build
- cd .\build\
- cmake --build .
- .\Debug\AcBel_Project.exe

## How To Manage Using Git
- git clone https://github.com/danlu008/AcBel_Project.git
- git init
- git config --global user.name {$User Name}
- git config --global user.email {$User Email}
- git remote add origin ${Your Git}
- git remote add upstream https://github.com/danlu008/AcBel_Project.git
- git reset --hard HEAD

### Git Message
- create / modify / move / rename / remove
- function / class / .cpp / .h

## Todo
- [x] Binary tree class
  * constructor / getter / setter
  * setSingleSide /setDoubleSide
  * swap
  * delete node
  * printBinaryTree
- [ ] GA class
  * Crossover
    * leftSubtreeCrossover
    * kPointCrossover
  * Mutation
    * Swap
      * swapNodeMutation
      * swapBranchMutation
      * swapSubtreeMutation
  * Rotate
    * k component rotation strickly
    * k component rotation with probability
  * Shift
    * shiftSubtreeMutation
  * Array Type Modification
    * insert
    * scramble
- [ ] Evaluation class
  * Contour
    * Horizon contour
    * Preplace contour
  * Area
  * PnS
  * WireLength
- [x] File input class
* component
* pin position
  * T501
  * M503