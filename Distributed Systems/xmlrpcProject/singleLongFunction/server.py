from xmlrpc.server import SimpleXMLRPCServer
from xmlrpc.server import SimpleXMLRPCRequestHandler

class ProxLongService:
    def ProxLong(self, request):
        prox = request+1
        return prox

class RequestHandler(SimpleXMLRPCRequestHandler):
    rpc_paths = ('/RPC2',)

def serve():
    server = SimpleXMLRPCServer(('192.168.0.28', 8000), requestHandler=RequestHandler, allow_none=True)
    server.register_introspection_functions()
    server.register_instance(ProxLongService())

    try:
        print("XML-RPC Server started on port 8000.")
        server.handle_request()
    finally:
        print("Server is shutting down.")

if __name__ == '__main__':
    serve()
