import grpc
import time
from numpy import int64
import multiSoma_pb2
import multiSoma_pb2_grpc

def run():
    server_address = 'localhost:50051'  
    with grpc.insecure_channel(server_address) as channel:
        stub = multiSoma_pb2_grpc.MultiSomaStub(channel)
        
        entry1 = int64(32424)
        entry2 = int64(2512343)
        entry3 = int64(465)
        entry4 = int64(987654345)
        entry5 = int64(10)
        entry6 = int64(1234234)
        entry7 = int64(1532)
        entry8 = int64(1456789992111111)

        print("Calling MultiSoma...")
        start_time = time.time() 
        request = multiSoma_pb2.EntryLongs(entry1=entry1, entry2=entry2, entry3=entry3, entry4=entry4, entry5=entry5, entry6=entry6, entry7=entry7, entry8=entry8)
        response = stub.MultiSoma(request)
        print(f"The sum is is {response.soma}")
        end_time = time.time()  

        time_spent = end_time - start_time
        print(f"Time spent on operation: {time_spent:.6f} seconds")

if __name__ == '__main__':
    run()
