# Script to generate isolineTree specification used to draw tiles

class MapPos:
	def __init__(self, value):
		self.value = value
		self.col = value % 8
		self.row = (value - self.col) / 8

	def isoline_id(self):
		return self.col + self.row

isolines = {}
def add_to_isoline(mappos):
	isoline_id = mappos.isoline_id()
	if not isolines.has_key(isoline_id):
		isolines[isoline_id] = []
	isolines[isoline_id].append(mappos)

for i in range(0, 64):
	add_to_isoline(MapPos(i))

class IsolineLeaf:
	def __init__(self, mappos):
		self.mappos = mappos

	def __str__(self):
		return str(self.mappos.value)

	def leafIndex(self, leftSide):
		return self.mappos.value

	def store_in_list(self, l):
		# No need to store leafs
		return -self.mappos.value

class FlatIsolinePair:
	def __init__(self, lChild, rChild, lrLeaf, rlLeaf):
		self.lChild = lChild
		self.rChild = rChild
		self.lrLeaf = lrLeaf
		self.rlLeaf = rlLeaf

	def __str__(self):
		return 'IsolinePair{ .lChild=%3d, .rChild=%3d, .lrLeaf=%2d, .rlLeaf=%2d }' % (
			self.lChild,
			self.rChild,
			self.lrLeaf,
			self.rlLeaf
		)

class IsolinePair:
	def __init__(self, left, right):
		self.left = left
		self.right = right

	def __str__(self):
		return '(%s, %s)' % (str(self.left), str(self.right))

	def leafIndex(self, leftSide):
		if leftSide:
			return self.left.leafIndex(True)
		else:
			return self.right.leafIndex(False)

	def store_in_list(self, l):
		index_l = self.left.store_in_list(l)
		index_r = self.right.store_in_list(l)
		l.append(
			FlatIsolinePair(
				index_l, index_r,
				self.left.leafIndex(False),
				self.right.leafIndex(True)
			)
		)
		# Return index in new list
		return len(l)

def make_isolinetree(isoline, indexLo, indexHi):
	if indexLo == indexHi:
		return IsolineLeaf(isoline[indexLo])
	else:
		indexMid = (indexLo + indexHi) / 2
		return IsolinePair(
			make_isolinetree(isoline, indexLo, indexMid),
			make_isolinetree(isoline, indexMid + 1, indexHi)
		)

isoline_roots = []
isoline_pairs = []

isoline_ids = list(isolines.keys())
isoline_ids.sort(reverse = True)
for k in isoline_ids:
	s = ','.join(str(mp.value) for mp in isolines[k])
	#print(s)

	root = make_isolinetree(isolines[k], 0, len(isolines[k]) - 1)
	#print(root)

	isoline_roots.append( root.store_in_list(isoline_pairs))

print("roots = %s" % (isoline_roots))
print("pairs = {\n  %s\n}" % (",\n  ".join(str(p) for p in isoline_pairs)))