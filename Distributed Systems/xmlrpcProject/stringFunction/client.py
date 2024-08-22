import math
import sys
import xmlrpc.client
import time

def run(entry):
    server_address = 'http://192.168.0.28:8000'  
    proxy = xmlrpc.client.ServerProxy(server_address)

    print("Calling StringComparision...")
    start_time = time.time() 
    response = proxy.StringComparision(entry)
    responseSize = len(response) 
    exponent = int(math.log2(responseSize))
    print(f"The entry size is greather than or equal to 2^{exponent}")
    end_time = time.time()  

    time_spent = end_time - start_time
    print(f"Time spent on operation: {time_spent:.6f} seconds")
    
if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Requer valor de entrada")
        sys.exit(1)
    entry = sys.argv[1]
    run(entry)
