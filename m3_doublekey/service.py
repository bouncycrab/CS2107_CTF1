import socket
import os
import random
import string
import threading

SECRET_KEY = 'REDACTED'
FLAG = 'REDACTED'

def encrypt(message):
	if len(message) <= 0 or len(message) > 40: 
		return ''
	result = []
	prev = 0
	for i in range(len(message)):
		c = (ord(message[i]) + prev - ord(FLAG[i % len(FLAG)])) 
		c *= ord(SECRET_KEY[i % len(SECRET_KEY)]) 
		c %= 1114111 # limit range of characters to chr()
		result.append(c)
		prev = c
	print(result)
	return ''.join(map(chr, result))


def handle_client(client_socket):
	while True:
		# Send a welcome message and request for encryption or decryption
		client_socket.send(b"Welcome to the Encryption Service!\n")

		while True:
			client_socket.send(b"Enter the message you would like to encrypt:\n")
			message = client_socket.recv(128).decode('utf-8').strip()
			encrypted_message = encrypt(message)
			client_socket.send(f"Encrypted Message: {encrypted_message}\n".encode('utf-8'))

		client_socket.close()


HOST = '0.0.0.0'
PORT = 8080
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen(1)

print(f"Server listening on {HOST}:{PORT}...")

while True:
    client_socket, client_address = server_socket.accept()
    print(f"Connection from {client_address}")
    
    client_thread = threading.Thread(target=handle_client, args=(client_socket,))
    client_thread.daemon = True  # Make the thread a daemon thread so it closes when the main program exits
    client_thread.start()
