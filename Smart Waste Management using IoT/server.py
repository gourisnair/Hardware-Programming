import socket               # Import socket module

frequency = 2500
duration = 3000

s = socket.socket()         # Create a socket object
host = "192.168.43.164" # Get local machine name
port = 12345                # Reserve a port for your service.
s.bind((host, port))        # Bind to the port

s.listen(5)                 # Now wait for client connection.
while True:
   c, addr = s.accept()     # Establish connection with client.
   if(c.recv(1024)):
      print("The trash is full! Please empty it")
   c.close()                # Close the connection
