import grpc
from concurrent import futures
from google.protobuf.empty_pb2 import Empty
import restFunction_pb2
import restFunction_pb2_grpc
import threading

shutdown_event = threading.Event()

class RestFunctionServicer(restFunction_pb2_grpc.RestFunctionServicer):
    def GetAndReturnNothing(self, request, context):
        print("Resting...")
        shutdown_event.set()  
        return Empty()

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    restFunction_pb2_grpc.add_RestFunctionServicer_to_server(RestFunctionServicer(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    print("Server started on port 50051.")
    
    shutdown_event.wait()
    
    server.stop(0)
    print("Server stopped.")

if __name__ == '__main__':
    serve()
