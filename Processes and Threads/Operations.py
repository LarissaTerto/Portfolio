import threading
from concurrent.futures import ThreadPoolExecutor, as_completed

mutex = threading.Lock()
resultado = 0
num_threads = 3

def processo_soma():
    global resultado
    with mutex:
        resultado += 2

def processo_multiplica():
    global resultado
    with mutex:
        resultado *= 5

def processo_subtrai():
    global resultado
    with mutex:
        resultado -= 3

with ThreadPoolExecutor(max_workers = num_threads) as executor:
    futures = [executor.submit(processo_soma)]
    
    for future in as_completed(futures):
        try:
            future.result()
        except Exception as e:
            print(f"Erro ao executar a thread: {e}")
    futures = [executor.submit(processo_multiplica)]

    for future in as_completed(futures):
        try:
            future.result()
        except Exception as e:
            print(f"Erro ao executar a thread: {e}")

    futures = [executor.submit(processo_subtrai)]

    for future in as_completed(futures):
        try:
            future.result()
        except Exception as e:
            print(f"Erro ao executar a thread: {e}")

print(f"Resultado = {resultado}.")
