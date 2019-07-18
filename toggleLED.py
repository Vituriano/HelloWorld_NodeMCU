import requests
req = requests.get("http://192.168.43.79:8070")
dado = req.status_code
while dado == 200:
	valor = raw_input("digite uma mensagem para enviar ao servidor: ")
	if valor == 'l':
		req = requests.get("http://192.168.43.79:8070/?function=led5_on")
	if valor == 'd':
		req = requests.get("http://192.168.43.79:8070/?function=led5_off")
