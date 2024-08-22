import grpc
import fruitCount_pb2
import fruitCount_pb2_grpc
import time
import fruitClasses

def run():
    server_address = 'localhost:50051'
    with grpc.insecure_channel(server_address) as channel:
        stub = fruitCount_pb2_grpc.FruitCountStub(channel)
        
        fruitBasket = fruitClasses.objBasket
        print("Old Basket: ")
        print(fruitBasket)
        print("\n")


        fruit = fruitClasses.fruit('Orange', 'Orange', 10)
        print("Calling FruitCount...")

        fruitObj = fruitCount_pb2.Object(name=fruit.name, color=fruit.color, quantity=fruit.quantity)
        request = fruitCount_pb2.Fruit(fruit=fruitObj)
 
        start_time = time.time()
        response = stub.FruitCount(request)

        newBasket = fruitClasses.fruitBasket(
            [fruitClasses.fruit(f.name, f.color, f.quantity) for f in response.basket.fruits],
            response.basket.size
        )
        print("New Basket: ")
        print(newBasket)
        print("\n")

        end_time = time.time()
        time_spent = end_time - start_time
        print(f"Time spent on operation: {time_spent:.6f} seconds")

if __name__ == '__main__':
    run()
