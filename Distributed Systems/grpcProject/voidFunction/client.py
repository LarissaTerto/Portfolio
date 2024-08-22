import grpc
import time
from google.protobuf.empty_pb2 import Empty
import restFunction_pb2
import restFunction_pb2_grpc

def run():
    server_address = 'localhost:50051'  
    with grpc.insecure_channel(server_address) as channel:
        stub = restFunction_pb2_grpc.RestFunctionStub(channel)
        
        print("Calling GetAndReturnNothing...")
        start_time = time.time()  
        response = stub.GetAndReturnNothing(Empty())
        end_time = time.time()  
        
        time_spent = end_time - start_time
        if(response): print("Server is Resting")
        print(f"Time spent on operation: {time_spent:.6f} seconds")

if __name__ == '__main__':
    run()
