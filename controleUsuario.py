import requests
req = requests.get("http://192.168.43.79:8070")
dado = req.status_code
while dado == 200:
	valor = raw_input("controle dos motores: ")
	req = requests.get("http://192.168.43.79:8070/?function=".valor)

