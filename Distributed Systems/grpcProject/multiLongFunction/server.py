import grpc
from concurrent import futures
import multiSoma_pb2
import multiSoma_pb2_grpc
import threading

shutdown_event = threading.Event()

class MultiSomaServicer(multiSoma_pb2_grpc.MultiSomaServicer):
    def MultiSoma(self, request, context):
        soma = request.entry1 + request.entry2 + request.entry3 + request.entry4 + request.entry5 + request.entry6 + request.entry7 + request.entry8
        shutdown_event.set()
        return multiSoma_pb2.Sum(soma=soma)

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    multiSoma_pb2_grpc.add_MultiSomaServicer_to_server(MultiSomaServicer(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    print("Server started on port 50051.")
    
    shutdown_event.wait()

    server.stop(0)
    print("Server stopped.")

if __name__ == '__main__':
    serve()
