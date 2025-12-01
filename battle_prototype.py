"""
A Prototype of the Pokemon Battle.
"""
import sys

class Pokemon:
    def __init__(self, name:str, health:int, attack:int):
        self.name = name
        self.health = 15
        self.attack = attack

class Player:
    def __init__(self, name, pokemon:Pokemon):
        self.name = name
        self.pokemon = pokemon
        self.max_health = pokemon.health
        self.health = pokemon.health
        self.attack = pokemon.attack
        self.items = ["Potion", "Pokeball"]

    def use_item(self, item_name:str):
        if self.items == []:
            print("No Items Left")
        if item_name == "Potion":
            if self.health == self.max_health:
                print("Already at max health.")
                return False
            else:
                print("Using Potion.")
                health = self.health + 4
                if health > self.max_health:
                    self.health = self.max_health
                else:
                    self.health = health
                self.items.remove("Potion")
                print(f"{self.pokemon.name}'s health replenished to {self.health}")
                return True
        if item_name == "Pokeball":
            print("Throwing Pokeball.")
            self.items.remove("Pokeball")
            return True
        
    def take_damage(self, attack_damage):
        result = self.health - attack_damage
        if result < 0:
            self.health = 0
            return False
        else:
            self.health = result
            return True
    
def attack(attacker:Player, attackee:Player):
    print(f"{attacker.name} attacks {attackee.name}.")
    attackee.take_damage(attacker.attack)
    print(f"{attackee.name} took {attacker.attack} damage.")

def turn(player:Player, opp:Player):
    print(f"{player.name}, will you (1) attack or (2) use an item?")
    isValid = False
    while not isValid:
        try:
            sys.stdout.flush()
            choice = int(input())
            if choice == 1 or choice == 2:
                isValid = True
        except Exception:
            print("Will you (1) attack or (2) use an item?")
    if choice == 1:
        attack(player,opp)
        return True
    if choice == 2:
        if player.items == []:
            print("Your bag is empty.")
            return True
        if len(player.items) == 1:
            print(f"Use {player.items[0]}? (1) yes or (2) no")
            isValid = False
            while not isValid:
                try:
                    sys.stdout.flush()
                    choice = int(input())
                    if choice == 1 or choice == 2:
                        isValid = True
                except Exception:
                    print(f"Use {player.items[0]}?")
            if choice == 1:
                player.use_item(f"{player.items[0]}") 
            return True
        else:
            print(f"will you use (1) {player.items[0]} or (2) {player.items[1]}")
            isValid = False
            while not isValid:
                try:
                    sys.stdout.flush()
                    choice = int(input())
                    if choice == 1 or choice == 2:
                        isValid = True
                except Exception:
                    print("Will you (1) attack or (2) use an item?")
            if choice == 1:
                player.use_item(f"{player.items[0]}")
            if choice == 2:
                player.use_item(f"{player.items[1]}")
        return True


def main():
    # attack1 = {1: }
    pikachu = Pokemon("Pikachu", 10, 2)
    squirtle = Pokemon("Squirtle", 10, 1)
    p1 = Player("Player1", pikachu)
    p2 = Player("Player2", squirtle)

    game_end = False
    while (game_end == False):
        turn(p1,p2)
        print(f"Player 1 health: {p1.health}\nPlayer 2 health: {p2.health}")
        if p1.health == 0 or p2.health == 0:
            game_end = True
        turn(p2,p1)
        print(f"Player 1 health: {p1.health}\nPlayer 2 health: {p2.health}")
        if p1.health == 0 or p2.health == 0:
            game_end = True

    if p1.health == 0:
        print(f"{p1.name} wins!")
    if p2.health == 0:
        print(f"{p2.name} wins!")

main()