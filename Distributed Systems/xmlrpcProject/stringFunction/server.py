from xmlrpc.server import SimpleXMLRPCServer
from xmlrpc.server import SimpleXMLRPCRequestHandler

class StringComparisionService:
    def StringComparision(self, request):
        stringSet = generate_strings(10)
        entrySize = len(request)
        for elem in stringSet:
            if(entrySize >= len(elem) and entrySize<len(elem)*2):
                response = elem
                break
        return response

class RequestHandler(SimpleXMLRPCRequestHandler):
    rpc_paths = ('/RPC2',)

def generate_strings(max_power):
    result = []
    for i in range(max_power + 1):
        size = 2 ** i
        result.append("a" * size)
    return result

def serve():
    server = SimpleXMLRPCServer(('192.168.0.28', 8000), requestHandler=RequestHandler, allow_none=True)
    server.register_introspection_functions()
    server.register_instance(StringComparisionService())

    try:
        print("XML-RPC Server started on port 8000.")
        server.handle_request()
    finally:
        print("Server is shutting down.")

if __name__ == '__main__':
    serve()
