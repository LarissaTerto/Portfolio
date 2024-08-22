import xmlrpc.client
import time

def run():
    server_address = 'http://192.168.0.28:8000'  
    proxy = xmlrpc.client.ServerProxy(server_address)
    entry1 = int(32424)
    entry2 = int(25123)
    entry3 = int(465)
    entry4 = int(9876545)
    entry5 = int(10)
    entry6 = int(1234234)
    entry7 = int(1532)
    entry8 = int(1451)

    print("Calling MultiSoma...")
    start_time = time.time() 
    
    response = proxy.MultiSoma(entry1, entry2, entry3, entry4, entry5, entry6, entry7, entry8)
    print(f"The sum is is {response}")
    end_time = time.time()  

    time_spent = end_time - start_time
    print(f"Time spent on operation: {time_spent:.6f} seconds")

if __name__ == '__main__':
    run()
