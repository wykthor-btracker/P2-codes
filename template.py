#-*- encoding:utf-8 -*-
#imports
# import pdb
# pdb.set_trace()
#imports

#global variables

#global variables

#classes
class node:
	def __init__(self,value=0,next=None,prev=None):
		self.value = value
		if(next == None):
			self.next = list()
		else:
			self.next = next

	def insert(self,newNode):
		newNode.next = self.next
		self.next = [newNode]
		return newNode

	def remove(self):
		if(self.next and self.prev):
			self.next.prev = self.prev
			self.prev.next = self.next
		else:
			self = None

#classes

#functions
def receiveNodes():
	while True:
		nodes = str(raw_input("\nInsira a lista de nós, separado por vírgula, sem repetições. "))
		nodes = nodes.split(",")
		if(len(nodes)!=(len(set(nodes)))):
			print("Lista inválida, tente novamente.")
		else:
			break
	return nodes

def receiveConnections(nodes):
	connections = []
	curr = "-1"
	while(curr!=""):
		invalid = 0
		curr = raw_input("\nInsira a próxima aresta, da forma 'a,b', toda aresta deve referir-se a nós que já existem. Sem espaços.\nQuando terminar, insira uma linha vazia. ")
		if(curr == ""):
			break
		curr = tuple(str(curr).split(","))
		if(len(curr)!=2):
			print("Input inválido, arestas devem ter forma 'a,b'.")
			continue
		for node in curr:
			if(not node in nodes):
				print("Aresta inválida. Nó não encontrado.")
				invalid = 1
				continue
		if(not curr in connections and not invalid):
			connections.append(curr)
	return connections

def isRoot(node,connections):
	for vert in connections:
		if(node in vert.next):
			return 0
	return 1

def isConnected(nodeA,nodeB):
	if(nodeB in nodeA.next and nodeA in nodeB.next):
		return 1
	else:
		return 0

def isComplete(nodes,connections):
	for nodeA in nodes:
		for nodeB in nodes:
			if(nodeA!=nodeB):
				if(not isConnected(nodeA,nodeB,connections)):
					return 0
	return 1 
#functions

def listToGraph(vertices,arestas):
	conv = {vert:node(value=vert) for vert in vertices}
	vertices = [vert for vert in conv.values()]
	for conn in arestas:
		conv[conn[0]].next.append(conv[conn[1]])
	return conv
#main
def main():
	vertices = receiveNodes()
	arestas =  receiveConnections(vertices)
	return None
#main

if __name__ == "__main__":
	main()