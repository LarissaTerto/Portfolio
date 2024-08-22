import grpc
import time
import sys
import proxLong_pb2
import proxLong_pb2_grpc

def run(entry):
    server_address = 'localhost:50051'  
    with grpc.insecure_channel(server_address) as channel:
        stub = proxLong_pb2_grpc.ProxLongStub(channel)
        
        print("Calling ProxLong...")
        start_time = time.time() 
        request = proxLong_pb2.EntryLong(entry=entry)
        response = stub.ProxLong(request)
        print(f"The successor of {request.entry} is {response.next}")
        end_time = time.time()  

        time_spent = end_time - start_time
        print(f"Time spent on operation: {time_spent:.6f} seconds")

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Requer valor de entrada")
        sys.exit(1)
    entry = int(sys.argv[1])
    run(entry)
