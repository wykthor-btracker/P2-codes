#-*- encoding:utf-8 -*-
#imports
# import pdb
# pdb.set_trace()
#imports

#global variables

#global variables

#classes
class node:
	def __init__(self,value=0,next=None,prev=None,insta = None,depth = 0):
		self.value = value
		self.insta = insta
		self.depth = depth
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

class tree:
	def __init__(self,root = None):
		self.root = root

	def dfs(self,node,visited,searchFunc,successFunc):
		curr = visited[:]
		curr.append(node)
		if(successFunc(node)):
			return [node]
		elif(node.next):
			for vert in node.next:
				if(searchFunc(vert,node.insta)):
					path = self.dfs(vert,curr,searchFunc,successFunc)
					if path:
						return [node]+path
				else:
					continue

	def pathExists(self,root,node,equals):
		if(equals(root,node)):
			return True
		elif(root.next):
			for path in root.next:
				if(self.nodeExists(path,node,equals)):
					return True
		else:
			return False

class problema:
	def __init__(self,missionarios = 3, canibais = 3,lado = 1):
		self.missionarios = int(missionarios)
		self.canibais = int(canibais)
		self.lado = int(lado)

	def sameState(self,nodeA,nodeB):
		return(nodeA.insta.missionarios == nodeB.insta.missionarios and nodeA.insta.canibais == nodeB.insta.canibais and nodeA.insta.lado == nodeB.insta.lado and nodeA.value == nodeB.value)

	def solved(self,node):
		return(node.insta.canibais == node.insta.missionarios and node.insta.missionarios == 0)

	def selfSolved(self):
		return(self.canibais== self.missionarios and self.missionarios== 0)

	def show(self):
		print("miss = {}\tcanib = {}\tlado = {}".format(self.missionarios,self.canibais,self.lado))

	def validMove(self,node,prob):
		move = node.value
		move = move.split("/")
		move = [int(val) for val in move]
		safeLeft = (prob.missionarios-move[0])>=(prob.canibais-move[1]) or prob.missionarios-move[0] == 0
		safeRight = ((3-prob.missionarios)+move[0])>=((3-prob.canibais)+move[1]) or (3-prob.missionarios)+move[0] == 0
		return(safeLeft and safeRight)#Se ambos os lados do rio tiverem missionarios>=canibais, verdade, senão, falso.

	def move(self,node):
		move = node.value
		move = move.split("/")
		move = [int(val) for val in move]
		nextStep = problema(self.missionarios-move[0],self.canibais-move[1],self.lado*-1)
		return nextStep

	def possibleMoves(self):
		if(self.lado==-1):
			miss = 3-self.missionarios
			canib = 3-self.canibais
		else:
			miss = self.missionarios
			canib = self.canibais
		if(not self.selfSolved()):
			return ["{}/{}".format(x*self.lado,y*self.lado) for x in range(miss+1) for y in range(canib+1) if x+y>=1 and x+y<=2]
		else:
			return []

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
	return vertices

def showPath(graph):
	acc = ""
	while(graph[0]):
		acc+="{} -> ".format(graph[0])
		graph = graph[1:]
def opposite(moveA,moveB):
	moveA = map(int,moveA.split("/"))
	moveB = map(int,moveB.split("/"))
	return(moveA[0]*-1==moveB[0] and moveA[1]*-1==moveB[1])

def populate(root):
	miss,canib = root.value.split("/")
	poss = [node(value=path,insta=root.insta.move(node(value=path)),depth = root.depth+1) for path in root.insta.possibleMoves() if not opposite(root.value,path)]
	# poss = [nodeC for nodeC in poss if not tree().nodeExists(firstRoot,nodeC,problema().sameState)]
	root.next = poss
	return root

def getLeafs(root):
	if(not root.next):
		return [root]
	else:
		leafs = []
		for path in root.next:
			leafs.extend(getLeafs(path))
		return leafs

def generatePaths(root,depth):
	for i in range(depth):
		for path in getLeafs(root):
			populate(path)

def traverse(parent,graph,tab):
	print(tab+"{}, ({},{}), {} {}".format(graph.value,graph.insta.missionarios,graph.insta.canibais,graph.depth,graph.insta.validMove(graph,parent.insta)))
	for i in graph.next:
		traverse(graph,i,tab+"\t")
#main

def main():
	inicio = node(value="0/0",insta=problema())
	generatePaths(inicio,13)
	inicio = tree(inicio)
	# traverse(inicio.root,inicio.root,"") #GIGANTE
	solution = inicio.dfs(inicio.root,[],problema().validMove,problema().solved)
	# for i in range(len(solution)):
	# 	print("\t"*i+"{}, ({},{}), {}".format(solution[i].value,solution[i].insta.missionarios,solution[i].insta.canibais,solution[i].depth))
	for i in solution:
		print("{} missionarios, {} canibais, atravesse.\n Na esquerda ficam {} missionarios, {} canibais.\n Na direita ficam {} missionarios, {} canibais\n".format(i.value.split("/")[0],i.value.split("/")[1],i.insta.missionarios,i.insta.canibais,3-i.insta.missionarios,3-i.insta.canibais))
	return inicio,solution
#main

if __name__ == "__main__":
	main()