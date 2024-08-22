import sys
import xmlrpc.client
import time

def run(entry):
    server_address = 'http://192.168.0.28:8000'  
    proxy = xmlrpc.client.ServerProxy(server_address)

    print("Calling ProxLong...")
    start_time = time.time() 
    response = proxy.ProxLong(entry)
    print(f"The successor of {entry} is {response}")
    end_time = time.time()  

    time_spent = end_time - start_time
    print(f"Time spent on operation: {time_spent:.6f} seconds")
    
if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Requer valor de entrada")
        sys.exit(1)
    entry = int(sys.argv[1])
    run(entry)
