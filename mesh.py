import numpy as np
import scipy


class Element:
	def __init__(self, position, connections):
		self.position = position
		self.connections = connections
		self.deformation = np.empty(3,3)

class Mesh:
	def __init__(self, vertices):
		x = vertices[:][0]
		y = vertices[:][1]
		z = vertices[:][2]

		xmax = max(x)
		xmin = min(x)
		ymax = max(y)
		ymin = min(y)
		zmax = max(z)
		zmin = min(z)