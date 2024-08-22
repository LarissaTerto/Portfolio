import grpc
from concurrent import futures
import proxLong_pb2
import proxLong_pb2_grpc
import threading

shutdown_event = threading.Event()

class ProxLongServicer(proxLong_pb2_grpc.ProxLongServicer):
    def ProxLong(self, request, context):
        prox = request.entry + 1
        shutdown_event.set()
        return proxLong_pb2.NextLong(next=prox)

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    proxLong_pb2_grpc.add_ProxLongServicer_to_server(ProxLongServicer(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    print("Server started on port 50051.")
    
    shutdown_event.wait()

    server.stop(0)
    print("Server stopped.")

if __name__ == '__main__':
    serve()
