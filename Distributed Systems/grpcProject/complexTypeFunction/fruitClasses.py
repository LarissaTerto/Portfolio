class fruit():
    def __init__(self, name, color, quantity):
        self.name = name
        self.color = color
        self.quantity = quantity
    def __str__(self):
        return f"Name: {self.name}, Color: {self.color}, Quantity: {self.quantity}"

class fruitBasket:
    def __init__(self, fruits, size):
        self.fruits = fruits
        self.size = size
    def __str__(self):
        fruit_descriptions = [str(fruit.name) for fruit in self.fruits]
        return f"Fruits: {', '.join(fruit_descriptions)}, Size: {self.size}"
    
objFruit = fruit('Apple', 'Red', 5)  
arr = [objFruit]
objBasket = fruitBasket(arr, objFruit.quantity)
