import math
import sys
import grpc
import time
import stringComparision_pb2
import stringComparision_pb2_grpc

def run(entry):
    server_address = 'localhost:50051'  
    with grpc.insecure_channel(server_address) as channel:
        stub = stringComparision_pb2_grpc.StringComparisionStub(channel)

        print("Calling StringComparision...")
        start_time = time.time() 
        request = stringComparision_pb2.EntryString(string = entry)
        response = stub.StringComparision(request)
        responseSize = len(response.string) 
        exponent = int(math.log2(responseSize))
        print(f"The entry size is greather than or equal to 2^{exponent}")
        end_time = time.time()  

        time_spent = end_time - start_time
        print(f"Time spent on operation: {time_spent:.6f} seconds")

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Requer string de entrada")
        sys.exit(1)
    entry = sys.argv[1]
    run(entry)
