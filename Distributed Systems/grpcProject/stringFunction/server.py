import grpc
from concurrent import futures
import stringComparision_pb2
import stringComparision_pb2_grpc
import threading

shutdown_event = threading.Event()

def generate_strings(max_power):
    result = []
    for i in range(max_power + 1):
        size = 2 ** i
        result.append("a" * size)
    return result

class StringComparisionServicer(stringComparision_pb2_grpc.StringComparisionServicer):
    def StringComparision(self, request, context):
        stringSet = generate_strings(10)
        entrySize = len(request.string)
        for elem in stringSet:
            if(entrySize >= len(elem) and entrySize<len(elem)*2):
                response = elem
                break
        shutdown_event.set()
        return stringComparision_pb2.ResponseString(string = response)

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    stringComparision_pb2_grpc.add_StringComparisionServicer_to_server(StringComparisionServicer(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    print("Server started on port 50051.")
    
    shutdown_event.wait()

    server.stop(0)
    print("Server stopped.")

if __name__ == '__main__':
    serve()
