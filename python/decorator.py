
class Coffee (object):
    def cost (self):
        return 1

class Milk (Coffee):
    def __init__ (self, decorated):
        self.decorated = decorated

    def cost (self):
        return 0.5 + self.decorated.cost ()

class Soy (Coffee):
    def __init__ (self, decorated):
        self.decorated = decorated

    def cost (self):
        return 0.7 + self.decorated.cost ()

soy_milk_coffee = Soy(Milk(Coffee ()))
print soy_milk_coffee.cost ()
