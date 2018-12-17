import numpy as np
import matplotlib.pyplot as plt
import json

"""
"	fonction qui affiche un gradient 2D de la densité nucléaire
"	@param f un descripteur de fichier
"""
def plot(f):
	config = json.loads(f.readline())
	print(config)
	plt.imshow(np.loadtxt(f, dtype=np.float64), interpolation='bilinear', cmap="Blues")
	plt.title("Densité nucléaire (pour une tranche theta=0)");
	plt.xlabel("z (de %d fm à %d fm)" % (config["z"]["min"], config["z"]["max"]))
	plt.ylabel("x (de %d fm à %d fm)" % (config["x"]["min"], config["x"]["max"]))
	plt.show()

# on lit sur l'entree standart
import sys
plot(sys.stdin)
