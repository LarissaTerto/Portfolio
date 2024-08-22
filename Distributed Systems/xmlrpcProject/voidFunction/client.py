import xmlrpc.client
import time
import socket

timeout = 20

class TimeoutTransport(xmlrpc.client.Transport):
    def make_connection(self, host):
        conn = super().make_connection(host)
        conn.timeout = timeout
        return conn

def run():
    server_address = 'http://192.168.0.28:8000'
    transport = TimeoutTransport()
    proxy = xmlrpc.client.ServerProxy(server_address, transport=transport)

    print("Calling GetAndReturnNothing...")
    start_time = time.time()

    try:
        proxy.GetAndReturnNothing()
    except socket.timeout:
        print(f"Operation timed out after {timeout} seconds")
    except Exception as e:
        print(f"An error occurred: {e}")

    end_time = time.time()
    time_spent = end_time - start_time

    print("Server is Resting")
    print(f"Time spent on operation: {time_spent:.6f} seconds")

if __name__ == '__main__':
    run()
