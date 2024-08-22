import threading
import grpc
from concurrent import futures
import fruitCount_pb2
import fruitCount_pb2_grpc
import fruitClasses

shutdown_event = threading.Event()

class FruitCountServicer(fruitCount_pb2_grpc.FruitCountServicer):
    def FruitCount(self, request, context):
        fruit_obj = request.fruit
        old_fruit = fruitClasses.objFruit
        old_fruit_obj = fruitCount_pb2.Object(name = old_fruit.name, color = old_fruit.color, quantity = old_fruit.quantity)

        basket = fruitCount_pb2.Obj(fruits = [fruit_obj, old_fruit_obj], size = fruit_obj.quantity + old_fruit_obj.quantity)

        response = fruitCount_pb2.FruitBasket(basket=basket)

        return response

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    fruitCount_pb2_grpc.add_FruitCountServicer_to_server(FruitCountServicer(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    print("Server started on port 50051.")
    server.wait_for_termination()

if __name__ == '__main__':
    serve()
