from xmlrpc.server import SimpleXMLRPCServer
from xmlrpc.server import SimpleXMLRPCRequestHandler
import fruitClasses

class FruitCountService:
    def FruitCount(self, request):
        fruit = fruitClasses.fruit(name = request.get('name'), color = request.get('color'), quantity = request.get('quantity'))
        basket = fruitClasses.objBasket
        basket.fruits.append(fruit)
        basket.size+=fruit.quantity
        return basket

class RequestHandler(SimpleXMLRPCRequestHandler):
    rpc_paths = ('/RPC2',)

def serve():
    server = SimpleXMLRPCServer(('192.168.0.28', 8000), requestHandler=RequestHandler, allow_none=True)
    server.register_introspection_functions()
    server.register_instance(FruitCountService())

    try:
        print("XML-RPC Server started on port 8000.")
        server.handle_request()
    finally:
        print("Server is shutting down.")

if __name__ == '__main__':
    serve()
