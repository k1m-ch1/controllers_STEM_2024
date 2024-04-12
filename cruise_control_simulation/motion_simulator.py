import time
import threading

start_time = time.time()
t_checkpoint = start_time
v_0 = 0
a = 0
d_0 = 0
user_input = ""

def distance(d_0 , t, v_0, a):
    return d_0 + v_0*t + (a*(t**2))/2

def velocity(t, v_0, a):
    return v_0 + a*t

def print_info():
    global user_input, t_checkpoint, v_0, a, d_0, start_time
    while True:
        print(f"distance: {distance(d_0, time.time() - t_checkpoint, v_0, a):.02f}, acceleration:{a}, distance_0:{float(d_0):.02f}, velocity:{float(v_0):.02f}, time passed:{time.time() - start_time:.02f}")
        # Check if there's user input
        if user_input:
            try: 
                user_input_float = float(user_input)
                d_0 = distance(d_0, time.time() - t_checkpoint, v_0, a)
                v_0 = velocity(time.time() - t_checkpoint, v_0, a)
                a = user_input_float
                t_checkpoint = time.time()
            except ValueError:
                pass
            finally:
                user_input = ""


def listen_input():
    global user_input
    while True:
        user_input = input("enter acceleration: ")

def __main__():
    global user_input
    print_thread = threading.Thread(target=print_info)
    print_thread.start()

    listen_input()

    print_thread.join()

if __name__ == '__main__':
    __main__()