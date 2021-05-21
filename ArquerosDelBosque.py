from dataclasses import dataclass
from enum import Enum
import random
import os
from typing import Final

# ------------------------------ CONSTANTS
possibleDirectionLetters: Final = ['S','N','E','O']
possibleActionLetters: Final = ['T','M']
shootRange:Final = 6 #5 sin contar la casilla desde donde se dispara
numberOfTrees: Final = 10
# ------------------------------ CONSTANTS

# ------------------------------ ENUMS
class EntityType(Enum):
    ARBOL = 1
    ARQUERO = 2

class Direction(Enum):
    S = 1 #SUR
    N = 2 #NORTE
    E = 3 #ESTE
    O = 4 #OESTE

class Action(Enum):
    T = 1 #SHOOT
    M = 2 #MOVE
# ------------------------------ ENUMS

# ------------------------------ UTILS
def askDirection() -> Direction:
    letter = ''
    error = False
    while not (letter in possibleDirectionLetters):
        if error:
            print("Entrada incorrecta, vuelva a ingresar:")
        print('Dirección: (S)ur, (N)orte, (E)ste, u (O)este?:')
        _input = input()
        if len(_input) > 0:
            letter = _input[0].upper()
            error = True
    return Direction[letter]

def askAction(playerChar:str):
    letter = ''
    error = False
    while not (letter in possibleActionLetters):
        if error:
            print("Entrada incorrecta, vuelva a ingresar:")
        print("Jugador {}: (M)overse o (T)irar flecha?:".format(playerChar))
        _input = input()
        if len(_input) > 0:
                letter = _input[0].upper()
                error = True
    return Action[letter]
# ------------------------------ UTILS

# ------------------------------ ENTITIES
@dataclass
class Entity:
    x: int = 0
    y: int = 0
    _type: EntityType = None
    char: str = None
    
class Arbol(Entity):
    _type = EntityType.ARBOL #readonly
    char = "0"

    def __init__(self,x,y):
        self.x = x
        self.y = y

class Arquero(Entity):
    _type: EntityType = EntityType.ARQUERO #readonly

    def __init__(self,char,x,y):
        self.char = char
        self.x = x
        self.y = y

    def move(self, direction:Direction):
        # 0 is the highest position, and 9 the lowest.
        if direction == Direction.S:
            if (self.x + 1 < 10):
                self.x += 1
        elif direction == Direction.N:
            if (self.x - 1 > -1):
                self.x -=1
        elif direction == Direction.E:
            if (self.y + 1 < 10):
                self.y += 1
        elif direction == Direction.O:
            if (self.y - 1 > -1):
                self.y -= 1
# ------------------------------ ENTITIES

# GAME SCREEN
class Grid:
    gridSize: int = 10 # 10 x 10
    trees: list[Arbol] = []
    players: list[Arquero] = []
    positionsTaken = [] #save which positions have been taken already

    def __init__(self,players:list[Arquero]):
        self.players = players

    def spawnTrees(self):
        for i in range(0,numberOfTrees):
            taken = True
            while taken:
                col = random.randint(1,self.gridSize - 2)
                row = random.randint(1,self.gridSize - 2)
                pos = [col,row]
                if pos not in self.positionsTaken:
                    self.trees.append(Arbol(col,row))
                    self.positionsTaken.append(pos)
                    taken = False

    def drawGrid(self):
        os.system('cls||clear') # clear console
        if len(self.trees) < 10: # if the trees weren't spawned yet
            self.spawnTrees()

        blank = '|' + "   " # where there is no player or tree

        for x in range(0,self.gridSize):
            row = ''
            picked = False
            for y in range(0,self.gridSize):
                for tree in self.trees:
                    if tree.x == x and tree.y == y:
                        row = row + '|' + " " + tree.char + " "
                        picked = True
                for player in self.players:
                    if player.x == x and player.y == y:
                        row = row + '|' + " " + player.char + " "
                        picked = True

                if not picked:
                    row = row + blank
                picked = False
                
            print('-' * (len(row)+1))
            print(row + '|')


def main():
    
    winner = ""
    
    #Game Loop
    while True:
        A = Arquero("A",5,9)
        B = Arquero("B",0,9)

        grid = Grid([A,B])

        currentPlayerTurn = random.randint(0,1) #0 for A, 1 for B

        currentPlayer = None
        currentEnemy = None
        disparoNoTieneEfecto = False

        while winner == "":
            grid.drawGrid()

            if disparoNoTieneEfecto:
                print("El disparo no tiene efecto")

            if currentPlayerTurn == 0:
                currentPlayer = grid.players[0]
                currentEnemy = grid.players[1]
            else:
                currentPlayer = grid.players[1]
                currentEnemy = grid.players[0]

            action = askAction(currentPlayer.char)
            direction = askDirection()
            hitTreeFirst = False
            
            if action == Action.M:
                #TODO: Verify if there are trees in that position
                if direction == Direction.S:
                    for tree in grid.trees:
                        if currentPlayer.y == tree.y and tree.x == currentPlayer.x + 1:
                            hitTreeFirst = True
                            break
                        else:
                            hitTreeFirst = False
                elif direction == Direction.N:
                    for tree in grid.trees:
                        if currentPlayer.y == tree.y and tree.x == currentPlayer.x - 1:
                            hitTreeFirst = True
                            break
                        else:
                            hitTreeFirst = False                      
                elif direction == Direction.E:
                    for tree in grid.trees:
                        if currentPlayer.x == tree.x and tree.y == currentPlayer.y + 1:
                            hitTreeFirst = True
                            break
                        else:
                            hitTreeFirst = False
                elif direction == Direction.O:
                    for tree in grid.trees:
                        if currentPlayer.x == tree.x and tree.y == currentPlayer.y - 1:
                            hitTreeFirst = True
                            break
                        else:
                            hitTreeFirst = False

                if not hitTreeFirst:
                    currentPlayer.move(direction)

            else:
                if direction == Direction.S: #hacia abajo, es decir hasta 9 (y++)
                    for i in range(currentPlayer.x,currentPlayer.x + shootRange):

                        for tree in grid.trees:
                            if currentPlayer.y == tree.y and tree.x == i:
                                hitTreeFirst = True

                        if hitTreeFirst == True:
                            break

                        elif currentEnemy.y == currentPlayer.y and currentEnemy.x == i:
                            winner = currentPlayer.char
                        else:
                            disparoNoTieneEfecto = True

                elif direction == Direction.N: #hacia arriba, es decir hasta 0 (y--)
                    for i in range(currentPlayer.x,currentPlayer.x - shootRange, -1):
                        for tree in grid.trees:
                            if currentPlayer.y == tree.y and tree.x == i:
                                hitTreeFirst = True

                        if hitTreeFirst == True:
                            break
                        
                        elif currentEnemy.y == currentPlayer.y and currentEnemy.x == i:
                            winner = currentPlayer.char
                        else:
                            disparoNoTieneEfecto = True

                elif direction == Direction.E: #hacia derecha, es decir hasta 9 (x++)
                    for i in range(currentPlayer.y,currentPlayer.y + shootRange):

                        for tree in grid.trees:
                            if currentPlayer.x == tree.x and tree.y == i:
                                hitTreeFirst = True

                        if hitTreeFirst == True:
                            break

                        elif currentEnemy.x == currentPlayer.x and currentEnemy.y == i:
                            winner = currentPlayer.char
                        else:
                            disparoNoTieneEfecto = True
                
                elif direction == Direction.O: #hacia izquierda, es decir hasta 0 (y--)
                    for i in range(currentPlayer.y, currentPlayer.y - shootRange, -1):

                        for tree in grid.trees:
                            if currentPlayer.x == tree.x and tree.y == i:
                                hitTreeFirst = True

                        if hitTreeFirst == True:
                            break

                        elif currentEnemy.x == currentPlayer.x and currentEnemy.y == i:
                            winner = currentPlayer.char
                        else:
                            disparoNoTieneEfecto = True

            if currentPlayerTurn == 1:
                currentPlayerTurn = 0
            else:
                currentPlayerTurn = 1

        print("Jugador {} gana!!!".format(winner))
        break

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        try:
            exit(0)
        except SystemExit:
            (0)