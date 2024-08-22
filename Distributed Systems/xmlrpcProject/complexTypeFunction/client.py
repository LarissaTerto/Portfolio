import xmlrpc.client
import time
import fruitClasses

def run():
    server_address = 'http://192.168.0.28:8000'  
    proxy = xmlrpc.client.ServerProxy(server_address)

    fruitBasket = fruitClasses.objBasket
    print("Old Basket: ")
    print(fruitBasket)
    print("\n")
    
    fruit = fruitClasses.fruit('Orange', 'Orange', 10)

    print("Calling FruitCount...")
    start_time = time.time() 
    
    response = proxy.FruitCount(fruit)

    print("New Basket: ")
    print(response)
    print("\n")

    end_time = time.time()  

    time_spent = end_time - start_time
    print(f"Time spent on operation: {time_spent:.6f} seconds")

if __name__ == '__main__':
    run()
