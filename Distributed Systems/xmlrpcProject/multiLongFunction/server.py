from xmlrpc.server import SimpleXMLRPCServer
from xmlrpc.server import SimpleXMLRPCRequestHandler

class MultiSomaService:
    def MultiSoma(self, entry1, entry2, entry3, entry4, entry5, entry6, entry7, entry8):
        sum = entry1 + entry2 + entry3 + entry4 + entry5 + entry6 + entry7 + entry8
        return sum

class RequestHandler(SimpleXMLRPCRequestHandler):
    rpc_paths = ('/RPC2',)

def serve():
    server = SimpleXMLRPCServer(('192.168.0.28', 8000), requestHandler=RequestHandler, allow_none=True)
    server.register_introspection_functions()
    server.register_instance(MultiSomaService())

    try:
        print("XML-RPC Server started on port 8000.")
        server.handle_request()
    finally:
        print("Server is shutting down.")

if __name__ == '__main__':
    serve()
