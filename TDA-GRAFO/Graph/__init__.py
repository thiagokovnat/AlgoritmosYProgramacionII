import heapq
import math

class Vertice():

	def __init__(self, clave):
		self.clave = clave
		self.adyacentes = {}

	def __str__(self):
		return str(self.clave) + ' adyacente: ' + str([x.clave for x in self.adyacentes])

	def agregarAdyacente(self, claveAdyacente, peso = 0):
		self.adyacentes[claveAdyacente] = peso

	def getAdyacentes(self):
		
		return self.adyacentes.keys()

	def getClave(self):
		return self.clave

	def getPeso(self, adyacente):
		print(adyacente)
		print(type(adyacente))
		if adyacente in self.adyacentes.keys():
			return self.adyacentes[adyacente]
		else:
			return float("inf")

	def getMinPeso(self):

		minimo = float('inf')
		minAdyacente = None 

		for adyacente in self.getAdyacentes():
			if self.adyacentes[adyacente] < minimo:
				minimo = self.adyacentes[adyacente]
				minAdyacente = adyacente 

		return minAdyacente 

class Grafo():

	def __init__(self, vertices = {}, cantVertices = 0):
		self.vertices = vertices
		self.cantVertices = cantVertices

	def __iter__(self):
		return iter(self.vertices.values())

	def agregarVertice(self, nuevoVertice):
		self.cantVertices += 1
		verticeAux = Vertice(nuevoVertice)
		self.vertices[nuevoVertice] = verticeAux
		return verticeAux

	def agregarArista(self, desde, hasta, peso = 0):

		if desde not in self.vertices:
			self.agregarVertice(desde)
		if hasta not in self.vertices:
			self.agregarVertice(hasta)

		self.vertices[desde].agregarAdyacente(self.vertices[hasta], peso)
		self.vertices[hasta].agregarAdyacente(self.vertices[desde], peso)

	def getVertices(self):
		return self.vertices.keys()

	def getClave(self, vertice):
		for key, value in self.vertices.items():
			if value == vertice:
				return key

		return None

	def BFS(self, inicio):

		vertice = self.vertices[inicio]
		queue = [vertice]
		visitados = []

		while queue:

			nodo = queue.pop(0)

			if nodo not in visitados:
				visitados.append(nodo)

				for adyacente in nodo.getAdyacentes():
					queue.append(adyacente)

		return visitados

	def DFS(self, inicio):
		visitados = []
		aux = self.vertices[inicio]
		self.DFSUtil(aux, visitados)
		
		return visitados

	def DFSUtil(self, inicio, visitados):
		if inicio not in visitados:
			visitados.append(inicio)
	
		for adyacente in inicio.getAdyacentes():
			if adyacente not in visitados:
				visitados.append(adyacente)
				self.DFSUtil(adyacente, visitados)

	def caminoMinimo(self, origen):
		padre = {}
		distancia = {}
		for vertice in self:
			distancia[vertice] = math.inf

		distancia[origen] = 0
		padre[origen] = None
		heap = []
		heapq.heappush(heap, (0, origen))
		while len(heap) > 0:
			vertice = heapq.heappop(heap)
			for w in self.vertices[vertice[1]].getAdyacentes():
				if distancia[vertice[1]] + self.vertices[vertice[1]].getPeso(w) < distancia[w.getClave()]:
					distancia[w] = distancia[vertice[1]] + self.vertices[vertice[1]].getPeso(w.getClave())
					padre[w] = vertice[1]
					heapq.heappush(heap, (distancia[w.getClave()], w.getClave()))	

		return padre, distancia







   	
