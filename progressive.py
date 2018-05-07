import matplotlib.pyplot as plt

class shape:
	def __init__(self, vertices):
		self.vertices = vertices

	def add_offset(self, offset):
		for i in range(len(self.vertices)):
			for j in range(len(self.vertices[i])):
				self.vertices[i][j] += offset[j]

	def drop_vertices():
		return self.vertices

class Projection:
	def __init__(self):
		self.shapes = []

	def draw(self):
		vertices = []
		for i in self.shapes:
			vertices.append(i.drop_vertices)
		x = []
		y = []

		for i in range(len(vertices)):
			x.append(vertices[i][0])
			y.append(vertices[i][1])
		plt.scatter(x,y)
		plt.show()

skin = shape([[0,0],[0,400],[1,400],[1,0]])
stringer = shape([[0,0],[0,15],[2,15],[2,2],[15,2],[15,0]])
stringer.add_offset([1,200])

Projection = Projection()
Projection.shapes.append(skin)
Projection.shapes.append(stringer)
Projection.draw()